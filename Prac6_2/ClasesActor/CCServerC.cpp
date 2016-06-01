#include <public/ccserver_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCServer::EDROOMTopContext::EDROOMTopContext (CCServer &act
	, TEDROOMBool * EDROOMpVarVresFree
	, TEDROOMUInt8 & EDROOMpVarVresFreeNumber
	, CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pService4(EDROOMcomponent.pService4)
	,pService3(EDROOMcomponent.pService3)
	,pService2(EDROOMcomponent.pService2)
	,pService1(EDROOMcomponent.pService1)
	, VresNumber ( 2 )
	, VresFree ( EDROOMpVarVresFree )
	, VresFreeNumber ( EDROOMpVarVresFreeNumber )
	, EDROOMPoolTEDROOMUInt8 ( EDROOMpPoolTEDROOMUInt8 )
 {

}

CCServer::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,pService4(contex.pService4)
	,pService3(contex.pService3)
	,pService2(contex.pService2)
	,pService1(contex.pService1)
	, VresNumber ( 2 )
	, VresFree ( contex.VresFree )
	, VresFreeNumber ( contex.VresFreeNumber )
	, EDROOMPoolTEDROOMUInt8 ( contex.EDROOMPoolTEDROOMUInt8 )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CCServer::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

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

void	CCServer::EDROOMTopContext::FAck()

{
   //Allocate data from pool
  TEDROOMUInt8 * pSResAck_Data = 
                                             EDROOMPoolTEDROOMUInt8.AllocData();
TEDROOMUInt8 resId=0;
VresFreeNumber--;
 
while((!VresFree[resId]) && (resId < (VresNumber -1)))
	resId++;
 
VresFree[resId]=false;
*pSResAck_Data=resId;
   //Reply synchronous communication
   Msg->reply(SResAck, pSResAck_Data, &EDROOMPoolTEDROOMUInt8); 
}



void	CCServer::EDROOMTopContext::FFreeResource()

{

VresFreeNumber++;

}



void	CCServer::EDROOMTopContext::FInit()

{

for(TEDROOMUInt8 i=0; i<VresNumber; i++){
	VresFree[i]=true;
}

}



void	CCServer::EDROOMTopContext::FMarkResource()

{
   //Handle Msg->data
  TEDROOMUInt8 & varSFreeRes = 
                                                     *(TEDROOMUInt8 *)Msg->data;
if(varSFreeRes<VresNumber){
	VresFree[varSFreeRes]=true;
	printf("%s Free ResId %i\n", EDROOMcomponent.EDROOMName, (int)varSFreeRes);
}

}



void	CCServer::EDROOMTopContext::FNack()

{

 
   //Reply synchronous communication
   Msg->reply(SResNack); 
}



	//********************************** Pools *************************************

	//CEDROOMPOOLTEDROOMUInt8

CCServer::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::CEDROOMPOOLTEDROOMUInt8(TEDROOMUInt32 elemCount, TEDROOMUInt8* pMem, TEDROOMBool * pMemMarks):CEDROOMProtectedMemoryPool(elemCount, pMem, pMemMarks, sizeof (TEDROOMUInt8)){;}

TEDROOMUInt8 *	CCServer::EDROOMTopContext::CEDROOMPOOLTEDROOMUInt8::AllocData(){
	return(TEDROOMUInt8*)CEDROOMProtectedMemoryPool::AllocData();
}



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCServer::EDROOMTopState::EDROOMTopState (CCServer &act, CEDROOMMemory *pEDROOMMemory  ):
	  EDROOMTopContext( act 
		, VresFree
		, VresFreeNumber
		, EDROOMPoolTEDROOMUInt8 )
	, VresFreeNumber ( 2 )
	, EDROOMPoolTEDROOMUInt8 ( 10, pEDROOMMemory->poolTEDROOMUInt8, pEDROOMMemory->poolMarkTEDROOMUInt8)
{

}

	//***************************** EDROOMBehaviour ********************************

void CCServer::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIllegada();

	do{

		//Take next transition

		switch(edroomCurrentTrans.localId){

			//Next Transition is Init
			case(Init):
				//Execute Action 
				FInit();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is FreeResource
			case(FreeResource):
				//Msg->Data Handling 
				FMarkResource();
				//Execute Action 
				FFreeResource();
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//To Choice Point BranchResRequest
			case(ResRequest):
				//Evaluate Branch Ack
				if( VresFreeNumber ){
					//Invoke Synchronous Message 
					FAck();

				//Next Transition is ResRequest
					edroomCurrentTrans.localId = ResRequest_Ack;

				//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Evaluate Branch Nack
				else{
					//Invoke Synchronous Message 
					FNack();

				//Next Transition is ResRequest
					edroomCurrentTrans.localId = ResRequest_Nack;

				//Next State is Ready
					edroomNextState = Ready;
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

				//Go to the state Ready
			case(Ready):
				//Entry into the State Ready
				edroomCurrentTrans=EDROOMReadyllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CCServer::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCServer::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCServer::EDROOMTopState::EDROOMReadyllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (SFreeRes): 

				 {
					edroomCurrentTrans.localId= FreeResource;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (SResReq): 

				 {
					//Next transition is  ResRequest
					edroomCurrentTrans.localId = ResRequest;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



