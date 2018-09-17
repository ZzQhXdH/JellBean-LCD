#ifndef		__GUI_TASK_H
#define		__GUI_TASK_H

#include "GUI/BackgroundWindow.h"
#include "GUI/PasswordWindow.h"
#include "GUI/SystemConfigWindow.h"
#include "GUI/ChangePINWindow.h"

#include "Task/Task.h"
#include "Driver/KeyUart.h"
#include "Custom/KeyQueue.h"
#include "Event/Receiver.h"
#include "Event/Timer.h"
#include "Driver/DeliverUart.h"

#define GUI_OBJ_NUMBER		100
#define GUI_OBJ_SIZE		sizeof (uint16_t)
#define GUI_SIZE			osRtxMessageQueueMemSize( GUI_OBJ_NUMBER, GUI_OBJ_SIZE )

class GUITask : public Task, public KeyListener, public Receiver, public Timer
{
	public:
		static inline GUITask &instance(void) 
		{
			static GUITask task;
			return task;
		}
		
		void vKeyClick(uint16_t key); // 非GUI线程
		 
		void vKeyValueClick(KeyValue value); // 非GUI线程
		
		void vDeliverResult(DeliverEvent &env); // 非GUI线程
		
		virtual void onDisplayPasswordWindow(void); // 非GUI线程
		
		virtual void onTimerEvent(void); // 非GUI线程
		
		inline bool isPowerBox1Checked(void) {
			return (mStatusByte1 & 0x01) != 0x00;
		}
		
		inline bool isPowerBox2Checked(void) {
			return (mStatusByte1 & 0x02) != 0x00;
		}
		
		inline bool isPowerBox3Checked(void) {
			return (mStatusByte1 & 0x04) != 0x00;
		}
		
		inline bool isPowerBox4Checked(void) {
			return (mStatusByte1 & 0x08) != 0x00;
		}
		
		inline bool isPowerBox5Checked(void) {
			return (mStatusByte1 & 0x10) != 0x00;
		}
		
		inline bool isDoorCloseChecked(void) {
			return (mStatusByte2 & 0x01) != 0x00;
		}
		
		inline bool isRotationOpenChecked(void) {
			return (mStatusByte2 & 0x02) != 0x00;
		}
		
		inline bool isPushBackChecked(void) {
			return (mStatusByte2 & 0x04) != 0x00;
		}
		
		inline bool isPushFrontChecked(void) {
			return (mStatusByte2 & 0x08) != 0x00;
		}
		
		inline bool isPushChecked(void) {
			return (mStatusByte2 & 0x10) != 0x00;
		}
		
		inline bool isDropOutChecked(void) {
			return (mStatusByte2 & 0x20) != 0x00;
		}
		
		inline bool isYAxisUpChecked(void) {
			return (mStatusByte3 & 0x01) != 0x00;
		}
		
		inline bool isYAxisDownChecked(void) {
			return (mStatusByte3 & 0x02) != 0x00;
		}
		
		inline bool isStepFault(void) {
			return (mStatusByte3 & 0x04) != 0x00;
		}
		
		inline bool isStepOriginChecked(void) {
			return (mStatusByte3 & 0x08) != 0x00;
		}
		
	protected:
		virtual void run(void); // GUI线程
	
	private:
		uint64_t mStack[10240 / 8];
		uint64_t mMqMem[ (GUI_SIZE + 7) / 8 ];
		BaseWindow *mWindowArray[8];
		uint8_t mStatusByte1, mStatusByte2, mStatusByte3;
	
	private:
		GUITask(void);
};

#define ID_SHOW_PASSWORD_WINDOW			0x00
#define ID_TIMER_EVENT					0xA0

#define ID_KEY_VALUE_CAN				0x01
#define ID_KEY_VALUE_ENT				0x02

#define ID_KEY_VALUE_0					0x80
#define ID_KEY_VALUE_1					0x81
#define ID_KEY_VALUE_2					0x82
#define ID_KEY_VALUE_3					0x83
#define ID_KEY_VALUE_4					0x84
#define ID_KEY_VALUE_5					0x85
#define ID_KEY_VALUE_6					0x86
#define ID_KEY_VALUE_7					0x87
#define ID_KEY_VALUE_8					0x88
#define ID_KEY_VALUE_9					0x89

#define ID_MSG_DELIVER_ERROR			0x90
#define ID_MSG_DELIVER_OK				0x91

#define ID_STATUS_5C					0x92
#define ID_STATUS_10C					0x93
#define ID_STATUS_5S					0x94
#define ID_STATUS_10S					0x95
#define ID_STATUS_20S					0x96

#define ID_MSG_START_DELIVER			0x97
#define ID_MSG_PAY_TIME_OUT				0x98
#define ID_MSG_STATUS_UPDATE			0x99

#define ID_MSG_PAY_VPOS					0x9A

#endif
