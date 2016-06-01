#ifndef CCCLIENT_H_
#define CCCLIENT_H_

//******************************************************************************
// EDROOM Service Library

#define _EDROOM_IS_EMBEDDED_

#include <public/edroomsl_iface_v1.h>

/**
 * \class   CCClient
 *
 */
class CCClient: public CEDROOMComponent {

public:

	/**
	 * \enum EDROOMCCClientSignal
	 * \brief Component Signal Enum Type
	 *
	 */
	 enum EDROOMCCClientSignal { EDROOMSignalTimeout, 
							EDROOMSignalDestroy, 
							SResAck, 
							SResNack, 
							SResReq, 
							SFreeRes };

	/**
	 * \class CCClient::CEDROOMMemory
	 * \brief Component Memory
	 *
	 */
	class CEDROOMMemory: public CEDROOMComponentMemory{

		private:

			//!Array of Message Queue Heads, one for each priority
			CEDROOMQueue::CQueueHead QueueHeads[EDROOMprioMINIMUM+1];

			//************ Component Timing Service Memory************

			//!Component Timing Service Timer Info Memory
			CEDROOMTimerInfo TimerInf[5];
			//!Component Timing Service Timer Info Marks Memory
			TEDROOMBool TimerInfMarks[5];
			//!Component Timing Service TimeOut Messages Memory
			CEDROOMTimeOutMessage TimeOutMsgs[5];
			//!Component Timing Service TimeOut Messages Marks Memory
			TEDROOMBool TimeOutMsgsMarks[5];

		public: 

			//!Component Timing Service Memory Object
			CEDROOMTimingMemory TimingMemory;

	// ********************************************************************
	// ******************* Component Message Data Pools *******************
	// ********************************************************************

			//! TEDROOMUInt8 Data Pool Memory
			TEDROOMUInt8	poolTEDROOMUInt8[10+1];
			//! TEDROOMUInt8 Data Pool Marks Memory
			TEDROOMBool	poolMarkTEDROOMUInt8[10];


			/** \brief This function is used for setting the Component Memory
			 * 
			 * \param numberOfMsgs number of messages that the component can store
			 * \param msgsMemory memory for the messages that the component can store
			 * \param msgsMemoryMarks memory marks for the messages that the component can store
			 * \param numberOfNodes number of nodes that the component needs
			 * \param queueNodesMemory memory for the component message queues 
			 * \param queueNodesMemoryMarks memory marks for the component message queues 
			 */
			void SetMemory(TEDROOMUInt32 numberOfMsgs
						, CEDROOMMessage * msgsMemory
						, TEDROOMBool * msgsMemoryMarks
						, TEDROOMUInt32 numberOfNodes
						, CEDROOMQueue::CQueueNode * queueNodesMemory
						, TEDROOMBool * queueNodesMemoryMarks);

	};


	// ********************************************************************
	//******************  Component Communication Ports *******************
	// ********************************************************************

	//! pServReq Component Port
	CEDROOMInterface	pServReq;


	// ********************************************************************
	// ********************  Timing Service Interface *********************
	// ********************************************************************

	//! Timing Service Access Point. It is common to all timing ports.
	CEDROOMTimingSAP	 EDROOMtimingSAP;


	//! ResConfigTimer Timing Port
	CEDROOMTimingInterface	ResConfigTimer;
	//! Timer Timing Port
	CEDROOMTimingInterface	Timer;




	// *************************************************************************
	// **************************** Frame Service Methods	********************
	// *************************************************************************



	//! Constructor
	CCClient(TEDROOMComponentID id, TEDROOMUInt32 roomNumMaxMens, TEDROOMPriority roomtaskPrio, TEDROOMStackSizeType roomStack, CEDROOMMemory * pActorMemory );




	//! Component Configuration 
	 int EDROOMConfig();


	//! Component Start 
	 int EDROOMStart();




	#ifdef _EDROOM_SYSTEM_CLOSE

	//! Method that returns true if component is finished 
	TEDROOMBool EDROOMIsComponentFinished();


	#endif

protected:



	//! Component behaviour 
	virtual void EDROOMBehaviour();




public:

	// *****************************	Behaviour  *************************

	// ***********************************************************************

	// class EDROOMTopContext

	// ***********************************************************************



	class EDROOMTopContext {

	protected:

	enum EDROOMCCClientSignal { EDROOMSignalTimeout, EDROOMSignalDestroy, SResAck, SResNack, SResReq, SFreeRes };


		friend class CCClient;

		CCClient &EDROOMcomponent;

		CEDROOMMessage * &Msg;

		CEDROOMMessage * &MsgBack;

		//Ports

		CEDROOMInterface & pServReq;
		CEDROOMTimingInterface & ResConfigTimer;
		CEDROOMTimingInterface & Timer;

			enum edroomStateId{I, Wait, Idle, Working};

			enum IdTrans{Transicion0, TryAgain, TryAgain_Ack, TryAgain_Nack, ResReq, ResReq_Ack, ResReq_Nack, FreeRes,  EDROOMMEMORIA };

		//Constants



		//Variables

		TEDROOMUInt8 &VresId;


		// Pools

		class CEDROOMPOOLTEDROOMUInt8:public CEDROOMProtectedMemoryPool {
			public:
			CEDROOMPOOLTEDROOMUInt8(TEDROOMUInt32 elemCount,TEDROOMUInt8 *pMem, TEDROOMBool *pMarks);
			TEDROOMUInt8	* AllocData();
		};
		CEDROOMPOOLTEDROOMUInt8	& EDROOMPoolTEDROOMUInt8;


		// CONSTRUCTORS

		EDROOMTopContext (CCClient &act, TEDROOMUInt8 & EDROOMpVarVresId, CEDROOMPOOLTEDROOMUInt8 & EDROOMpPoolTEDROOMUInt8 );

		EDROOMTopContext ( EDROOMTopContext &contex );

	public:

		/**
		 * \brief Search Context transition 
		 * \param edroomCurrentTrans returns the context transition 

		 * \return true if context transition is found 

		 */
		TEDROOMBool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

		//! \brief Get new message from the Queue

		void EDROOMNewMessage () { EDROOMcomponent.EDROOMNewMsg(); }

		/**
		 * \brief Get and Clear the Error Flags 
		 * \return the error flags  

		 */
		 TEDROOMUInt32 GetAndClearErrorFlags(){ return EDROOMcomponent.GetAndClearErrorFlags();}

		// User Defined Functions

		/**
		 * \brief  
		 */
		void	FFreeRes();

		/**
		 * \brief  
		 */
		void	FGetResId();

		/**
		 * \brief  
		 */
		void	FProgRequest();

		/**
		 * \brief  
		 */
		void	FProgWait();

		/**
		 * \brief  
		 */
		void	FProgWorking();

		/**
		 * \brief  
		 */
		void	FResRequest();

		/**
		 * \brief  
		 */
		TEDROOMBool	GIsAck();

	};

	// ***********************************************************************

	// class EDROOM_CTX_Working_3

	// ***********************************************************************



	class EDROOM_CTX_Working_3 : public EDROOMTopContext {

	protected:
			enum edroomStateId{ResConfig, DoWork};

			enum IdTrans{ToResConfig, TryResConfig, TryResConfig_ResConfigOK, TryResConfig_ResConfigError, ToResConfig2,  EDROOMMEMORIA };

		//Constants



		//Variables

		TEDROOMUInt8 &VresAttempts;


		// CONSTRUCTORS

		EDROOM_CTX_Working_3( EDROOMTopContext &contex, TEDROOMUInt8 & EDROOMpVarVresAttempts );

		EDROOM_CTX_Working_3( EDROOM_CTX_Working_3 &contex );

	public:
		TEDROOMBool EDROOMSearchContextTrans(TEDROOMTransId &edroomCurrentTrans);

		// User Defined Functions

		/**
		 * \brief  
		 */
		void	FProgResConfig();

		/**
		 * \brief  
		 */
		void	FResConfigFail();

		/**
		 * \brief  
		 */
		void	FResConfigOK();

		/**
		 * \brief  
		 */
		void	FTryResConfig();

		/**
		 * \brief  
		 */
		TEDROOMBool	GResConfigOK();

	};

	// ***********************************************************************

	// class EDROOM_SUB_Working_3

	// ***********************************************************************



	class EDROOM_SUB_Working_3:public EDROOM_CTX_Working_3{ 

	protected:



		EDROOM_CTX_Working_3::edroomStateId edroomCurrentState;

		EDROOM_CTX_Working_3::edroomStateId edroomNextState;

		//Variables

		TEDROOMUInt8 VresAttempts;
	public:

		EDROOMTopContext::edroomStateId idEstado;

		// CONSTRUCTOR*************************************************

		EDROOM_SUB_Working_3(EDROOMTopContext::edroomStateId idEst, EDROOMTopContext &contex );

		// llegada*************************************************

		TEDROOMTransId llegada(EDROOMTopContext::IdTrans );

		// Inicio**********************************************

		void EDROOMInit();

		// ***********************************************************************

		// Leaf SubState ResConfig

		// ***********************************************************************



		TEDROOMTransId EDROOMResConfigllegada();

		// ***********************************************************************

		// Leaf SubState DoWork

		// ***********************************************************************



		TEDROOMTransId EDROOMDoWorkllegada();

	};

	// ***********************************************************************

	// class EDROOMTopState

	// ***********************************************************************



	class EDROOMTopState : public EDROOMTopContext {

	protected:

		EDROOM_SUB_Working_3 EDROOMWorking;


		EDROOMTopContext::edroomStateId edroomCurrentState;

		EDROOMTopContext::edroomStateId edroomNextState;

		//Variables

		TEDROOMUInt8 VresId;


		// Pools

		CEDROOMPOOLTEDROOMUInt8	EDROOMPoolTEDROOMUInt8;


	public:

		// CONSTRUCTOR

		EDROOMTopState (CCClient &act, CEDROOMMemory *pEDROOMMemory  );


		//***************************** EDROOMBehaviour ********************************

		void EDROOMBehaviour();

		// Inicio**********************************************

		void EDROOMInit();

		// ***********************************************************************

		// SubEstado Inicial 

		// ***********************************************************************



		TEDROOMTransId EDROOMIllegada();

		// ***********************************************************************

		// Leaf SubState Wait

		// ***********************************************************************



		TEDROOMTransId EDROOMWaitllegada();

		// ***********************************************************************

		// Leaf SubState Idle

		// ***********************************************************************



		TEDROOMTransId EDROOMIdlellegada();

	};

protected:

	// ********************************  Top State  ****************************

	EDROOMTopState edroomTopState;



};
#endif
