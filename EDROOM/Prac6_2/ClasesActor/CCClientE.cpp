

#include <public/ccclient_iface_v1.h>





	// ******************* CONSTRUCTOR ************************************



CCClient::CCClient(TEDROOMComponentID id,TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,roomtaskPrio,roomStack, pActorMemory )

		// *********** Timing service access point *********

		,EDROOMtimingSAP(this, 5,&pActorMemory->TimingMemory)


		// *******************  Timers  ********************

		,ResConfigTimer(&EDROOMtimingSAP, 2 )
		,Timer(&EDROOMtimingSAP, 2 )




		// ***************	Top State  *****************

		,edroomTopState(*this,pActorMemory)


{


}


	//***************	PUBLIC METHODS  ********************************



		//**********           Configuration               ************


int CCClient::EDROOMConfig() {




 return 0; }



		//**********           START               ************


int CCClient::EDROOMStart() {



		//****************** Timing Task Start**********************

	EDROOMtimingSAP.Start();

		//****************** Component Start **********************

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

return 0;}


	// ***************	PROTECTED METHODS *******************************



		//***************** Behaviour ******************



void CCClient::EDROOMBehaviour() {

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();

}




		//**********        ComponentIsFinished           ************


	#ifdef _EDROOM_SYSTEM_CLOSE

TEDROOMBool CCClient::EDROOMIsComponentFinished() {


	return ( CEDROOMComponent::EDROOMIsComponentFinished());

}


	#endif

	// ***************	EDROOM Memory ******************************

void CCClient::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ 
		, CEDROOMMessage * MessagesMem_
		, TEDROOMBool * MessagesMemMarks_
		, TEDROOMUInt32 numberOfNodes_
		, CEDROOMQueue::CQueueNode * QueueNodesMem_
		, TEDROOMBool * QueueNodesMemMarks_){

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_
			,numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);

		TimingMemory.SetMemory(5,TimerInf,&TimerInfMarks[0],TimeOutMsgs,&TimeOutMsgsMarks[0]);


}

