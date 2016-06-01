#include <public/ccclient_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCClient::EDROOMTopContext::EDROOMTopContext (CCClient &act
	, TEDROOMUInt8 & EDROOMpVarVresId
	, CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pServReq(EDROOMcomponent.pServReq)
	,ResConfigTimer(EDROOMcomponent.ResConfigTimer)
	,Timer(EDROOMcomponent.Timer)
	, VresId ( EDROOMpVarVresId )
	, EDROOMPoolTEDROOMUInt8 ( EDROOMpPoolTEDROOMUInt8 )
 {

}

CCClient::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,pServReq(contex.pServReq)
	,ResConfigTimer(contex.ResConfigTimer)
	,Timer(contex.Timer)
	, VresId ( contex.VresId )
	, EDROOMPoolTEDROOMUInt8 ( contex.EDROOMPoolTEDROOMUInt8 )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CCClient::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

	TEDROOMBool edroomValidMsg=false; 

	 switch(Msg->signal){

		 case ( EDROOMSignalDestroy ): 

			 edroomValidMsg=true;
			 edroomCurrentTrans.distanceToContext = 0 ;
			 edroomCurrentTrans.localId = -1 ;
			 break;

	}

	return(edroomValidMsg);

}

	// User Defined Functions   ****************************

void	CCClient::EDROOMTopContext::FProgRequest()

{
   //Define interval
  Pr_Time interval;
interval =Pr_Time(3,0);
printf("%s is sleeping\n", EDROOMcomponent.EDROOMName);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CCClient::EDROOMTopContext::FProgWait()

{
   //Define interval
  Pr_Time interval;
interval=Pr_Time(1,0);
printf("%s is waiting\n", EDROOMcomponent.EDROOMName);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CCClient::EDROOMTopContext::FProgWorking()

{
   //Define interval
  Pr_Time interval;
interval =Pr_Time(2,0);
printf("%s is working\n", EDROOMcomponent.EDROOMName);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



void	CCClient::EDROOMTopContext::FResRequest()

{

   //Invoke synchronous communication 
   MsgBack=pServReq.invoke(SResReq); 
}



TEDROOMBool	CCClient::EDROOMTopContext::GIsAck()

{

return (MsgBack->signal==SResAck);

}



void	CCClient::EDROOMTopContext::FGetResId()

{
   //Handle MsgBack->data
  TEDROOMUInt8 & varSResAck = 
                                                 *(TEDROOMUInt8 *)MsgBack->data;
VresId = varSResAck;
printf("%s Get ResId %i\n", EDROOMcomponent.EDROOMName, VresId);
 
}



void	CCClient::EDROOMTopContext::FFreeRes()

{
   //Allocate data from pool
  TEDROOMUInt8 * pSFreeRes_Data = 
                                             EDROOMPoolTEDROOMUInt8.AllocData();
	
		// Complete Data 
	
	*pSFreeRes_Data=VresId;
   //Send message 
   pServReq.send(SFreeRes, pSFreeRes_Data, &EDROOMPoolTEDROOMUInt8); 
}



// ***********************************************************************

// class EDROOM_CTX_Working_3

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCClient::EDROOM_CTX_Working_3::EDROOM_CTX_Working_3( EDROOMTopContext &contex, TEDROOMUInt8 & EDROOMpVarVresAttempts ):

	EDROOMTopContext(contex)
	, VresAttempts ( EDROOMpVarVresAttempts )
{

}

CCClient::EDROOM_CTX_Working_3::EDROOM_CTX_Working_3( EDROOM_CTX_Working_3 &contex ):

	EDROOMTopContext(contex)
	, VresAttempts ( contex.VresAttempts )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CCClient::EDROOM_CTX_Working_3::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

	TEDROOMBool edroomValidMsg=false; 

	 switch(Msg->signal){

		// Check trigger for signal EDROOMSignalTimeout

		 case (EDROOMSignalTimeout): 

				if ( *Msg->GetPInterface() == Timer) {

					 edroomValidMsg=true;
					edroomCurrentTrans.localId = EDROOMTopContext::FreeRes;
					edroomCurrentTrans.distanceToContext = 1 ;
				 }

			 break;

	}

	if (!edroomValidMsg) {

		 edroomValidMsg = EDROOMTopContext::EDROOMSearchContextTrans(edroomCurrentTrans);
		 if (edroomValidMsg) edroomCurrentTrans.distanceToContext++;
	}

	return(edroomValidMsg);

}

	// User Defined Functions   ****************************

void	CCClient::EDROOM_CTX_Working_3::FProgResConfig()

{
   //Define interval
  Pr_Time interval;
interval=Pr_Time(0, 100000); //100 ms
   //Program relative timer 
   ResConfigTimer.InformIn( interval ); 
}



void	CCClient::EDROOM_CTX_Working_3::FTryResConfig()

{

VresAttempts++;

}



TEDROOMBool	CCClient::EDROOM_CTX_Working_3::GResConfigOK()

{

return (VresAttempts>2);

}



void	CCClient::EDROOM_CTX_Working_3::FResConfigFail()

{

printf ("%s Res %i Config Fail\n", EDROOMcomponent.EDROOMName, (int) VresId);

}



void	CCClient::EDROOM_CTX_Working_3::FResConfigOK()

{

printf ("%s Res %i Config OK\n", EDROOMcomponent.EDROOMName, (int) VresId);
VresAttempts=0;

}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMUInt8

CCClient::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(TEDROOMUInt32 elemCount, TEDROOMUInt8* pMem, TEDROOMBool * pMemMarks):CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks, sizeof (TEDROOMUInt8)){;}

TEDROOMUInt8 *	CCClient::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::AllocData(){
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCClient::EDROOMTopState::EDROOMTopState (CCClient &act, CEDROOMMemory *pEDROOMMemory  ):
	  EDROOMTopContext( act 
		, VresId
		, EDROOMPoolTEDROOMUInt8 )
	, EDROOMWorking( Working , *this )
	, EDROOMPoolTEDROOMUInt8 ( 10, pEDROOMMemory->poolTEDROOMUInt8, pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCClient::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIllegada();

	do{

		//Take next transition

		switch(edroomCurrentTrans.localId){

			//Next Transition is Transicion0
			case(Transicion0):
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//To Choice Point BranchTryAgain
			case(TryAgain):
				//Invoke Synchronous Message 
				FResRequest();
				//Evaluate Branch Ack
				if( GIsAck() ){
					//Msg->Data Handling 
					FGetResId();

				//Next Transition is TryAgain
					edroomCurrentTrans.localId = TryAgain_Ack;

				//Next State is Working
					edroomNextState = Working;
				 } 
				//Evaluate Branch Nack
				else{

				//Next Transition is TryAgain
					edroomCurrentTrans.localId = TryAgain_Nack;

				//Next State is Wait
					edroomNextState = Wait;
				 } 
				break;
			//To Choice Point BranchResReq
			case(ResReq):
				//Invoke Synchronous Message 
				FResRequest();
				//Evaluate Branch Ack
				if( GIsAck() ){
					//Msg->Data Handling 
					FGetResId();

				//Next Transition is ResReq
					edroomCurrentTrans.localId = ResReq_Ack;

				//Next State is Working
					edroomNextState = Working;
				 } 
				//Evaluate Branch Nack
				else{

				//Next Transition is ResReq
					edroomCurrentTrans.localId = ResReq_Nack;

				//Next State is Wait
					edroomNextState = Wait;
				 } 
				break;
			//Next Transition is FreeRes
			case(FreeRes):
				//Send Asynchronous Message 
				FFreeRes();
				//Next State is Idle
				edroomNextState = Idle;
				break;
		}

		//Entry into the Next State 
		switch(edroomNextState){

				//Go to the state I
			case(I):
				//Entry into the State I
				edroomCurrentTrans=EDROOMIllegada();
				break;

				//Go to the state Wait
			case(Wait):
				//Execute Entry Action 
				FProgWait();
				//Entry into the State Wait
				edroomCurrentTrans=EDROOMWaitllegada();
				break;

				//Go to the state Idle
			case(Idle):
				//Execute Entry Action 
				FProgRequest();
				//Entry into the State Idle
				edroomCurrentTrans=EDROOMIdlellegada();
				break;

				//Go to the state Working
			case(Working):
				//Execute Entry Action 
				FProgWorking();
				//Entry into the State Working
				edroomCurrentTrans=EDROOMWorking.llegada((IdTrans)edroomCurrentTrans.localId);
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CCClient::EDROOMTopState::EDROOMInit(){

EDROOMWorking.EDROOMInit();
edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCClient::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Transicion0
	edroomCurrentTrans.localId = Transicion0;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Wait

	// ***********************************************************************



TEDROOMTransId CCClient::EDROOMTopState::EDROOMWaitllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  TryAgain
					edroomCurrentTrans.localId = TryAgain;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CCClient::EDROOMTopState::EDROOMIdlellegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  ResReq
					edroomCurrentTrans.localId = ResReq;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



// ***********************************************************************

// class EDROOM_SUB_Working_3

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCClient::EDROOM_SUB_Working_3::EDROOM_SUB_Working_3(EDROOMTopContext::edroomStateId idEst, EDROOMTopContext &contex ):
	  EDROOM_CTX_Working_3( contex , VresAttempts )
	, VresAttempts ( 0 )
{ idEstado =idEst; }

	// llegada**********************************************

TEDROOMTransId CCClient::EDROOM_SUB_Working_3::llegada(EDROOMTopContext::IdTrans transLlegada){

	TEDROOMTransId edroomCurrentTrans;

	int salirContexto=0;

	//Transition at Context Entry
	switch (transLlegada){

		//From entry point ResReq_Ack
		case(EDROOMTopContext::ResReq_Ack):
			edroomCurrentTrans.localId= ToResConfig2;
			edroomNextState = ResConfig;
			break;
		//From entry point TryAgain_Ack
		case(EDROOMTopContext::TryAgain_Ack):
			edroomCurrentTrans.localId= ToResConfig;
			edroomNextState = ResConfig;
			break;
		case(EDROOMTopContext::EDROOMMEMORIA):
			//Memory Entry added
			edroomCurrentTrans.localId = EDROOMMEMORIA ;
			edroomNextState = edroomCurrentState;
			break;
		default:
			//Default is memory entry
			edroomCurrentTrans.localId = EDROOMMEMORIA ;
			edroomNextState = edroomCurrentState;
			break;
	}

	do{

		//Entry into the Next State 
		switch(edroomNextState){

				//Go to the state ResConfig
			case(ResConfig):
				//Execute Entry Action 
				FProgResConfig();
				//Entry into the State ResConfig
				edroomCurrentTrans=EDROOMResConfigllegada();
				break;

				//Go to the state DoWork
			case(DoWork):
				//Entry into the State DoWork
				edroomCurrentTrans=EDROOMDoWorkllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

		if (edroomCurrentTrans.distanceToContext == 0){

			switch (edroomCurrentTrans.localId){

				//To Choice Point BranchTryResConfig
				case(TryResConfig):
					//Execute Action 
					FTryResConfig();
					//Evaluate Branch ResConfigOK
					if( GResConfigOK() ){
						//Execute Action 
						FResConfigOK();

					//Next Transition is TryResConfig
						edroomCurrentTrans.localId = TryResConfig_ResConfigOK;

					//Next State is DoWork
						edroomNextState = DoWork;
						salirContexto=0;
					 } 
					//Evaluate Branch ResConfigError
					else{
						//Execute Action 
						FResConfigFail();

					//Next Transition is TryResConfig
						edroomCurrentTrans.localId = TryResConfig_ResConfigError;

					//Next State is ResConfig
						edroomNextState = ResConfig;
						salirContexto=0;
					 } 
					break;
			}

		}else salirContexto=1;

	}while(!salirContexto);

	edroomCurrentTrans.distanceToContext--;

	return(edroomCurrentTrans);

}



	// Inicio**********************************************

void CCClient::EDROOM_SUB_Working_3::EDROOMInit(){

}



	// ***********************************************************************

	// Leaf SubState  ResConfig

	// ***********************************************************************



TEDROOMTransId CCClient::EDROOM_SUB_Working_3::EDROOMResConfigllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == ResConfigTimer) {

					//Next transition is  TryResConfig
					edroomCurrentTrans.localId = TryResConfig;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  DoWork

	// ***********************************************************************



TEDROOMTransId CCClient::EDROOM_SUB_Working_3::EDROOMDoWorkllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



