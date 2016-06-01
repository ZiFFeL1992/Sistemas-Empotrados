#include <public/ccclient_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCClient::EDROOMTopContext::EDROOMTopContext (CCClient &act ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pServReq(EDROOMcomponent.pServReq)
	,Timer(EDROOMcomponent.Timer)
 {

}

CCClient::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,pServReq(contex.pServReq)
	,Timer(contex.Timer)
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

void	CCClient::EDROOMTopContext::FFreeRes()

{

   //Invoke synchronous communication 
   MsgBack=pServReq.invoke(SResReq); 
}



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



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCClient::EDROOMTopState::EDROOMTopState (CCClient &act ):
	  EDROOMTopContext( act  )
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
			//Next Transition is FreeRes
			case(FreeRes):
				//Invoke Synchronous Message 
				FFreeRes();
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//To Choice Point BranchTryAgain
			case(TryAgain):
				//Invoke Synchronous Message 
				FResRequest();
				//Evaluate Branch Ack
				if( GIsAck() ){

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
				edroomCurrentTrans=EDROOMWorkingllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CCClient::EDROOMTopState::EDROOMInit(){

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

	// Leaf SubState  Working

	// ***********************************************************************



TEDROOMTransId CCClient::EDROOMTopState::EDROOMWorkingllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					edroomCurrentTrans.localId= FreeRes;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



