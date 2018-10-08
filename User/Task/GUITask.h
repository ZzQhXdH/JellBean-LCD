#ifndef		__GUI_TASK_H
#define		__GUI_TASK_H

#include "Window/BackgroundWindow.h"
#include "Window/PasswordWindow.h"
#include "Window/SystemConfigWindow.h"
#include "Window/ChangePINWindow.h"

#include "Task/Task.h"
#include "Driver/KeyUart.h"
#include "Custom/KeyQueue.h"
#include "Event/Receiver.h"
#include "Event/Timer.h"
#include "Driver/DeliverUart.h"


#define GUI_OBJ_NUMBER		100
#define GUI_OBJ_SIZE		sizeof (MessageId)
#define GUI_SIZE			osRtxMessageQueueMemSize( GUI_OBJ_NUMBER, GUI_OBJ_SIZE )

class GUITask : public Task, public Receiver
{
	public:
		static inline GUITask &instance(void) 
		{
			static GUITask task;
			return task;
		}
		
		inline void sendMessage(MessageId msgId) { put(&msgId);}
		
		inline osStatus_t acquireMessage(MessageId *pMsg, uint32_t timeOut) { return recv(pMsg, timeOut);}
		
	protected:
		virtual void run(void); // GUI线程
	
	private:
		uint64_t mStack[10240 / 8];
		uint64_t mMqMem[ (GUI_SIZE + 7) / 8 ];
		
	private:
		GUITask(void);
};

#endif
