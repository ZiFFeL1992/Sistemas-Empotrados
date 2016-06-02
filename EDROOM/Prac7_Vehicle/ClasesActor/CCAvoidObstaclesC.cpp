#include <public/ccavoidobstacles_iface_v1.h>

// ***********************************************************************

// class EDROOMTopContext

// ***********************************************************************



	// CONSTRUCTORS***********************************************

CCAvoidObstacles::EDROOMTopContext::EDROOMTopContext (CCAvoidObstacles &act
	, TEDROOMBool & EDROOMpVarVObsDetected ):

	EDROOMcomponent(act)
	,Msg(EDROOMcomponent.Msg)
	,MsgBack(EDROOMcomponent.MsgBack)
	,AvoidObstaclesSysCtrl(EDROOMcomponent.AvoidObstaclesSysCtrl)
	,Timer(EDROOMcomponent.Timer)
	, VObsDetected ( EDROOMpVarVObsDetected )
 {

}

CCAvoidObstacles::EDROOMTopContext::EDROOMTopContext ( EDROOMTopContext &contex ):

	EDROOMcomponent(contex.EDROOMcomponent),
	Msg(contex.Msg),
	MsgBack(contex.MsgBack)
	,AvoidObstaclesSysCtrl(contex.AvoidObstaclesSysCtrl)
	,Timer(contex.Timer)
	, VObsDetected ( contex.VObsDetected )
 {

}

	// EDROOMSearchContextTrans********************************************

TEDROOMBool CCAvoidObstacles::EDROOMTopContext::EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans){

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

void	CCAvoidObstacles::EDROOMTopContext::FCheckObstacles()

{

print_char('.');
VObsDetected=sensors_check_obstacles();

}



void	CCAvoidObstacles::EDROOMTopContext::FConfigOK()

{

   //Reply synchronous communication
   Msg->reply(SConfigOK); 
}



void	CCAvoidObstacles::EDROOMTopContext::FHandleObstacle()

{

print_char('\n');
print_char('\r');
print_string("\tOBST");
actuators_halt();
   //Send message 
   AvoidObstaclesSysCtrl.send(SObstacleDetected); 
}



void	CCAvoidObstacles::EDROOMTopContext::FProgNextDetection()

{
   //Define interval
  Pr_Time interval;
interval=Pr_Time(0,500000);
   //Program relative timer 
   Timer.InformIn( interval ); 
}



	//********************************** Pools *************************************



// ***********************************************************************

// class EDROOMTopState

// ***********************************************************************



	// CONSTRUCTOR*************************************************

CCAvoidObstacles::EDROOMTopState::EDROOMTopState (CCAvoidObstacles &act ):
	  EDROOMTopContext( act 
		, VObsDetected )
{

}

	//***************************** EDROOMBehaviour ********************************

void CCAvoidObstacles::EDROOMTopState::EDROOMBehaviour(){

	TEDROOMTransId edroomCurrentTrans;

	//Behaviour starts from Init State

	edroomCurrentTrans = EDROOMIllegada();

	do{

		//Take next transition

		switch(edroomCurrentTrans.localId){

			//Next Transition is Init
			case(Init):
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//Next Transition is Config
			case(Config):
				//Invoke Synchronous Message 
				FConfigOK();
				//Next State is Idle
				edroomNextState = Idle;
				break;
			//Next Transition is Start
			case(Start):
				//Next State is Ready
				edroomNextState = Ready;
				break;
			//To Choice Point BranchCheckObstacles
			case(CheckObstacles):
				//Execute Action 
				FCheckObstacles();
				//Evaluate Branch ObstDetected
				if( VObsDetected ){
					//Send Asynchronous Message 
					FHandleObstacle();

				//Next Transition is CheckObstacles
					edroomCurrentTrans.localId = CheckObstacles_ObstDetected;

				//Next State is Ready
					edroomNextState = Ready;
				 } 
				//Evaluate Branch NoObstacle
				else{

				//Next Transition is CheckObstacles
					edroomCurrentTrans.localId = CheckObstacles_NoObstacle;

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

				//Go to the state Idle
			case(Idle):
				//Entry into the State Idle
				edroomCurrentTrans=EDROOMIdlellegada();
				break;

				//Go to the state Ready
			case(Ready):
				//Execute Entry Action 
				FProgNextDetection();
				//Entry into the State Ready
				edroomCurrentTrans=EDROOMReadyllegada();
				break;

		}

		edroomCurrentState=edroomNextState;

	}while(Msg->signal != EDROOMSignalDestroy);

}



	// Inicio**********************************************

void CCAvoidObstacles::EDROOMTopState::EDROOMInit(){

edroomCurrentState=I;

}



//	 ***********************************************************************

//	 SubState I

//	 ***********************************************************************



TEDROOMTransId CCAvoidObstacles::EDROOMTopState::EDROOMIllegada(){

	TEDROOMTransId edroomCurrentTrans;

	//Next transition is  Init
	edroomCurrentTrans.localId = Init;
	edroomCurrentTrans.distanceToContext = 0;
	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Idle

	// ***********************************************************************



TEDROOMTransId CCAvoidObstacles::EDROOMTopState::EDROOMIdlellegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (SConfigAO): 

				 if ( *Msg->GetPInterface() == AvoidObstaclesSysCtrl) {

					edroomCurrentTrans.localId= Config;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

			case (SStart): 

				 if ( *Msg->GetPInterface() == AvoidObstaclesSysCtrl) {

					edroomCurrentTrans.localId= Start;
					edroomCurrentTrans.distanceToContext = 0;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



	// ***********************************************************************

	// Leaf SubState  Ready

	// ***********************************************************************



TEDROOMTransId CCAvoidObstacles::EDROOMTopState::EDROOMReadyllegada(){

	TEDROOMTransId edroomCurrentTrans;

	int edroomValidMsg=false;

	do{

		EDROOMNewMessage ();

		switch(Msg->signal){

			case (EDROOMSignalTimeout): 

				 if ( *Msg->GetPInterface() == Timer) {

					//Next transition is  CheckObstacles
					edroomCurrentTrans.localId = CheckObstacles;
					edroomCurrentTrans.distanceToContext = 0 ;
					edroomValidMsg=true;
				 }

				break;

		};

		if (!edroomValidMsg) edroomValidMsg = EDROOMSearchContextTrans(edroomCurrentTrans);

	} while (!edroomValidMsg);

	return(edroomCurrentTrans);

}



