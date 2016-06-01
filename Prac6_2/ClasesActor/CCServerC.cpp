#include <public/ccserver_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCServer::EDROOMTopContext::EDROOMTopContext (CCServer &act
	, TEDROOMUInt8 & EDROOMpVarVresFreeNumber ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,pService4(EDROOMcomponent.pService4)
	,pService3(EDROOMcomponent.pService3)
	,pService2(EDROOMcomponent.pService2)
	,pService1(EDROOMcomponent.pService1)
	, VresFreeNumber ( EDROOMpVarVresFreeNumber )
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
	, VresFreeNumber ( contex.VresFreeNumber )
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

VresFreeNumber--;
   //Reply synchronous communication
   Msg->reply(SResAck); 
}



void	CCServer::EDROOMTopContext::FFreeResource()

{

VresFreeNumber++;

}



void	CCServer::EDROOMTopContext::FNack()

{

 
   //Reply synchronous communication
   Msg->reply(SResNack); 
}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCServer::EDROOMTopState::EDROOMTopState (CCServer &act ):
	  EDROOMTopContext( act 
		, VresFreeNumber )
	, VresFreeNumber ( 2 )
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
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//Next Transition is FreeResource
			case(FreeResource):
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



