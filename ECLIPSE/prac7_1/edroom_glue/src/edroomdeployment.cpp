//##############################################################################
//###############     This file has been generated by EDROOM     ###############
//##############################################################################
 
 
#include <edroom_glue/edroomdeployment.h>
 
//*****************************************************************************
//Main Wait
 
void MainWait(Vehicle   &comp1,
					CAPathPlanner   &comp2,
					CAPathTracker   &comp3,
					CCAvoidObstacles   &comp4){
 
	Pr_Time waitTime(3, 0);
 
#ifdef _EDROOM_SYSTEM_CLOSE
	while(!comp1.EDROOMIsComponentFinished()
				||!comp2.EDROOMIsComponentFinished()
				||!comp3.EDROOMIsComponentFinished()
				||!comp4.EDROOMIsComponentFinished())
#else
	while(true)
#endif

 
		Pr_DelayIn(waitTime);
}
 
//*****************************************************************************
//SetMemory
 
void CEDROOMSystemMemory::SetMemory(){
 
	comp1Memory.SetMemory(10, comp1Messages, &comp1MessagesMarks[0]
					,16,comp1QueueNodes, &comp1QueueNodesMarks[0]);
	comp2Memory.SetMemory(10, comp2Messages, &comp2MessagesMarks[0]
					,13,comp2QueueNodes, &comp2QueueNodesMarks[0]);
	comp3Memory.SetMemory(10, comp3Messages, &comp3MessagesMarks[0]
					,13,comp3QueueNodes, &comp3QueueNodesMarks[0]);
	comp4Memory.SetMemory(10, comp4Messages, &comp4MessagesMarks[0]
					,13,comp4QueueNodes, &comp4QueueNodesMarks[0]);
}
 
//*****************************************************************************
//SetComponents
 
void CEDROOMSystemCommSAP::SetComponents(Vehicle   *p_comp1,
										CAPathPlanner   *p_comp2,
										CAPathTracker   *p_comp3,
										CCAvoidObstacles   *p_comp4){
	mp_comp1=p_comp1;
	mp_comp2=p_comp2;
	mp_comp3=p_comp3;
	mp_comp4=p_comp4;
}
 
 
//*****************************************************************************
//*****************************************************************************
//Signal Translation Functions
//*****************************************************************************
//*****************************************************************************
 
 
TEDROOMSignal CEDROOMSystemCommSAP::C4AvoidObstacles_PAvoidObstaclesSysCtrl__C1MainActor_PAvoidObstaclesSysCtrl(TEDROOMSignal signalOut){
 
	TEDROOMSignal signalIn;
 
	switch(signalOut){
 
		case( CCAvoidObstacles::SObstacleDetected):	 signalIn=Vehicle::SObstacleDetected; break;
 
		case( CCAvoidObstacles::SConfigError):	 signalIn=Vehicle::SConfigError; break;
 
		case( CCAvoidObstacles::SConfigOK):	 signalIn=Vehicle::SConfigOK; break;
 
		default: signalIn=(TEDROOMSignal)(-1); break;
 
	}
	return signalIn;
 
}
 
TEDROOMSignal CEDROOMSystemCommSAP::C1MainActor_PAvoidObstaclesSysCtrl__C4AvoidObstacles_PAvoidObstaclesSysCtrl(TEDROOMSignal signalOut){
 
	TEDROOMSignal signalIn;
 
	switch(signalOut){
 
		case( Vehicle::SConfigAO):	 signalIn=CCAvoidObstacles::SConfigAO; break;
 
		case( Vehicle::SStart):	 signalIn=CCAvoidObstacles::SStart; break;
 
		default: signalIn=(TEDROOMSignal)(-1); break;
 
	}
	return signalIn;
 
}
 
TEDROOMSignal CEDROOMSystemCommSAP::C2PathPlanner_PTrackPath__C3PathTracker_PTrackPath(TEDROOMSignal signalOut){
 
	TEDROOMSignal signalIn;
 
	switch(signalOut){
 
		case( CAPathPlanner::STrackPath):	 signalIn=CAPathTracker::STrackPath; break;
 
		default: signalIn=(TEDROOMSignal)(-1); break;
 
	}
	return signalIn;
 
}
 
TEDROOMSignal CEDROOMSystemCommSAP::C3PathTracker_PTrackPath__C2PathPlanner_PTrackPath(TEDROOMSignal signalOut){
 
	TEDROOMSignal signalIn;
 
	switch(signalOut){
 
		case( CAPathTracker::SPathRequest):	 signalIn=CAPathPlanner::SPathRequest; break;
 
		default: signalIn=(TEDROOMSignal)(-1); break;
 
	}
	return signalIn;
 
}
 
TEDROOMSignal CEDROOMSystemCommSAP::C1MainActor_PPathTrackerCtrl__C3PathTracker_PPathTrackerCtrl(TEDROOMSignal signalOut){
 
	TEDROOMSignal signalIn;
 
	switch(signalOut){
 
		case( Vehicle::SConfigPathTracker):	 signalIn=CAPathTracker::SConfigPathTracker; break;
 
		case( Vehicle::SStopTracking):	 signalIn=CAPathTracker::SStopTracking; break;
 
		case( Vehicle::SStartTracking):	 signalIn=CAPathTracker::SStartTracking; break;
 
		default: signalIn=(TEDROOMSignal)(-1); break;
 
	}
	return signalIn;
 
}
 
TEDROOMSignal CEDROOMSystemCommSAP::C3PathTracker_PPathTrackerCtrl__C1MainActor_PPathTrackerCtrl(TEDROOMSignal signalOut){
 
	TEDROOMSignal signalIn;
 
	switch(signalOut){
 
		case( CAPathTracker::SConfigError):	 signalIn=Vehicle::SConfigError; break;
 
		case( CAPathTracker::SConfigOK):	 signalIn=Vehicle::SConfigOK; break;
 
		default: signalIn=(TEDROOMSignal)(-1); break;
 
	}
	return signalIn;
 
}
 
TEDROOMSignal CEDROOMSystemCommSAP::C1MainActor_PPathPlannerCtrl__C2PathPlanner_PPathPlannerCtrl(TEDROOMSignal signalOut){
 
	TEDROOMSignal signalIn;
 
	switch(signalOut){
 
		case( Vehicle::SConfigPathPlanner):	 signalIn=CAPathPlanner::SConfigPathPlanner; break;
 
		case( Vehicle::SMarkObstacle):	 signalIn=CAPathPlanner::SMarkObstacle; break;
 
		case( Vehicle::SNewTargetLocation):	 signalIn=CAPathPlanner::SNewTargetLocation; break;
 
		case( Vehicle::SStartPlanning):	 signalIn=CAPathPlanner::SStartPlanning; break;
 
		default: signalIn=(TEDROOMSignal)(-1); break;
 
	}
	return signalIn;
 
}
 
TEDROOMSignal CEDROOMSystemCommSAP::C2PathPlanner_PPathPlannerCtrl__C1MainActor_PPathPlannerCtrl(TEDROOMSignal signalOut){
 
	TEDROOMSignal signalIn;
 
	switch(signalOut){
 
		case( CAPathPlanner::SConfigError):	 signalIn=Vehicle::SConfigError; break;
 
		case( CAPathPlanner::SConfigOK):	 signalIn=Vehicle::SConfigOK; break;
 
		default: signalIn=(TEDROOMSignal)(-1); break;
 
	}
	return signalIn;
 
}
 
 
 
//*****************************************************************************
//RegisterInterfaces
 
void CEDROOMSystemCommSAP::RegisterInterfaces(){
 
	// Register Interface for Component 1
	m_localCommSAP.RegisterInterface(1, mp_comp1->Timer, mp_comp1);
	m_localCommSAP.RegisterInterface(2, mp_comp1->PathPlannerCtrl, mp_comp1);
	m_localCommSAP.RegisterInterface(3, mp_comp1->PathTrackerCtrl, mp_comp1);
	m_localCommSAP.RegisterInterface(4, mp_comp1->AvoidObstaclesSysCtrl, mp_comp1);
 
	// Register Interface for Component 2
	m_localCommSAP.RegisterInterface(1, mp_comp2->Timer, mp_comp2);
	m_localCommSAP.RegisterInterface(2, mp_comp2->TrackPath, mp_comp2);
	m_localCommSAP.RegisterInterface(3, mp_comp2->PathPlannerCtrl, mp_comp2);
 
	// Register Interface for Component 3
	m_localCommSAP.RegisterInterface(1, mp_comp3->Timer, mp_comp3);
	m_localCommSAP.RegisterInterface(2, mp_comp3->TrackPath, mp_comp3);
	m_localCommSAP.RegisterInterface(3, mp_comp3->PathTrackerCtrl, mp_comp3);
 
	// Register Interface for Component 4
	m_localCommSAP.RegisterInterface(1, mp_comp4->Timer, mp_comp4);
	m_localCommSAP.RegisterInterface(2, mp_comp4->AvoidObstaclesSysCtrl, mp_comp4);
 
}
 
 
//*****************************************************************************
////SetLocalConnections
 
void CEDROOMSystemCommSAP::SetLocalConnections(){
 
	m_localCommSAP.Connect(mp_comp4->AvoidObstaclesSysCtrl, mp_comp1->AvoidObstaclesSysCtrl, connections[0], 
					C4AvoidObstacles_PAvoidObstaclesSysCtrl__C1MainActor_PAvoidObstaclesSysCtrl, 
					C1MainActor_PAvoidObstaclesSysCtrl__C4AvoidObstacles_PAvoidObstaclesSysCtrl);
 
	m_localCommSAP.Connect(mp_comp2->TrackPath, mp_comp3->TrackPath, connections[1], 
					C2PathPlanner_PTrackPath__C3PathTracker_PTrackPath, 
					C3PathTracker_PTrackPath__C2PathPlanner_PTrackPath);
 
	m_localCommSAP.Connect(mp_comp1->PathTrackerCtrl, mp_comp3->PathTrackerCtrl, connections[2], 
					C1MainActor_PPathTrackerCtrl__C3PathTracker_PPathTrackerCtrl, 
					C3PathTracker_PPathTrackerCtrl__C1MainActor_PPathTrackerCtrl);
 
	m_localCommSAP.Connect(mp_comp1->PathPlannerCtrl, mp_comp2->PathPlannerCtrl, connections[3], 
					C1MainActor_PPathPlannerCtrl__C2PathPlanner_PPathPlannerCtrl, 
					C2PathPlanner_PPathPlannerCtrl__C1MainActor_PPathPlannerCtrl);
 
}
 
 
//*****************************************************************************
////SetRemoteConnections
 
void CEDROOMSystemCommSAP::SetRemoteConnections(){
 
}
 
//*****************************************************************************
////SetConnections
 
void CEDROOMSystemCommSAP::SetConnections(){
 
	SetLocalConnections();
	SetRemoteConnections();
 
}
 
//*****************************************************************************
////CEDROOMSystemDeployment Constructor
 
CEDROOMSystemDeployment::CEDROOMSystemDeployment(){
 
#ifdef CONFIG_EDROOMSL_ADD_TRACE
#endif
	systemMemory.SetMemory();
 
}
 
//*****************************************************************************
////Config
 
void CEDROOMSystemDeployment::Config(Vehicle   *p_comp1,
											CAPathPlanner   *p_comp2,
											CAPathTracker   *p_comp3,
											CCAvoidObstacles   *p_comp4){
 
	mp_comp1=p_comp1;
	mp_comp2=p_comp2;
	mp_comp3=p_comp3;
	mp_comp4=p_comp4;
 
	systemCommSAP.SetComponents(	p_comp1,
									p_comp2,
									p_comp3,
									p_comp4);
 
	systemCommSAP.RegisterInterfaces();
	systemCommSAP.SetConnections();
 
}
 
//*****************************************************************************
////StartComponents
 
void CEDROOMSystemDeployment::StartComponents(){
	mp_comp1->EDROOMStart();
	mp_comp2->EDROOMStart();
	mp_comp3->EDROOMStart();
	mp_comp4->EDROOMStart();
 
}
 
//*****************************************************************************
////Start
 
void CEDROOMSystemDeployment::Start(){
 
#ifdef CONFIG_EDROOMBP_DEPLOYMENT_NEED_TASK
 
	Pr_Task MainTask(CEDROOMSystemDeployment::main_task,EDROOMprioMINIMUM,1024*16);
 
	kernel.Start();
 
#else
 
StartComponents();
 
	kernel.Start();
 
	MainWait(*mp_comp1,
				*mp_comp2,
				*mp_comp3,
				*mp_comp4);
 
 
#endif
 
}
 
#ifdef CONFIG_EDROOMBP_DEPLOYMENT_NEED_TASK
 
	extern CEDROOMSystemDeployment systemDeployment;
 
 
//*****************************************************************************
////main_task
 
 
Pr_TaskRV_t CEDROOMSystemDeployment::main_task(Pr_TaskP_t){
 
	systemDeployment.StartComponents();
	MainWait(*systemDeployment.mp_comp1,
				*systemDeployment.mp_comp2,
				*systemDeployment.mp_comp3,
				*systemDeployment.mp_comp4);
 
}
#endif
