

#include <public/prac6_2_iface_v1.h>





	// ******************* CONSTRUCTOR ************************************



Prac6_2::Prac6_2(TEDROOMComponentID id,TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory *pActorMemory ) : 

		CEDROOMComponent(id,EDROOMprioMINIMUM+1,roomNumMaxMens,roomtaskPrio,roomStack, pActorMemory )



		// ***************	Top State  *****************

		,edroomTopState(*this)


{


}


	//***************	PUBLIC METHODS  ********************************



		//**********           Configuration               ************


int Prac6_2::EDROOMConfig() {




 return 0; }



		//**********           START               ************


int Prac6_2::EDROOMStart() {



		//****************** Component Start **********************

	CEDROOMComponent::EDROOMStart(); 	// Call to EDROOMStart method of CEDROOMComponent

return 0;}


	// ***************	PROTECTED METHODS *******************************



		//***************** Behaviour ******************



void Prac6_2::EDROOMBehaviour() {

	edroomTopState.EDROOMInit();
	edroomTopState.EDROOMBehaviour();

}




		//**********        ComponentIsFinished           ************


	#ifdef _EDROOM_SYSTEM_CLOSE

TEDROOMBool Prac6_2::EDROOMIsComponentFinished() {


	return ( Client1.EDROOMIsComponentFinished() && Client2.EDROOMIsComponentFinished() && Client3.EDROOMIsComponentFinished() && Client4.EDROOMIsComponentFinished() && SuperServer.EDROOMIsComponentFinished() && Client5.EDROOMIsComponentFinished() && Client6.EDROOMIsComponentFinished() && Client7.EDROOMIsComponentFinished() && Client8.EDROOMIsComponentFinished() && CEDROOMComponent::EDROOMIsComponentFinished());

}


	#endif

	// ***************	EDROOM Memory ******************************

void Prac6_2::CEDROOMMemory::SetMemory(TEDROOMUInt32 numMessages_ 
		, CEDROOMMessage * MessagesMem_
		, TEDROOMBool * MessagesMemMarks_
		, TEDROOMUInt32 numberOfNodes_
		, CEDROOMQueue::CQueueNode * QueueNodesMem_
		, TEDROOMBool * QueueNodesMemMarks_){

		CEDROOMComponentMemory::SetMemory( numMessages_,MessagesMem_, MessagesMemMarks_
			,numberOfNodes_,QueueNodesMem_, QueueNodesMemMarks_, QueueHeads);


}

