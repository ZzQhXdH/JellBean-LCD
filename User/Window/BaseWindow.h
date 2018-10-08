#ifndef		__BASE_WINDOW_H
#define		__BASE_WINDOW_H

#include "GUI.h"
#include "Dialog.h"
#include <stdint.h>
#include <stdio.h>


enum MessageId 
{
	MSG_SHOW_PASSWORD_WINDOW = 0x00, 
	MSG_BUTTON_CANCEL = 0x01, 
	MSG_BUTTON_ENTER = 0x02,
	MSG_BUTTON_0 = 0x10,
	MSG_BUTTON_1 = 0x11, 
	MSG_BUTTON_2 = 0x12,
	MSG_BUTTON_3 = 0x13,
	MSG_BUTTON_4 = 0x14,
	MSG_BUTTON_5 = 0x15,
	MSG_BUTTON_6 = 0x16,
	MSG_BUTTON_7 = 0x17,
	MSG_BUTTON_8 = 0x18,
	MSG_BUTTON_9 = 0x19,
	MSG_DELIVER_ERROR = 0x21,
	MSG_DELIVER_SUCCESS = 0x22,
	MSG_DELIVER_TICK = 0x23,
	MSG_PAY_TIME_OUT = 0x24,
	MSG_STATUS_UPDATE = 0x25,
	MSG_CHECKED_CASH = 0x26,
	MSG_CHECKED_VPOS = 0x27,
};

class BaseWindow
{
	public:
		virtual void show(WM_HWIN hParentWindow);
		
		virtual void dismiss(void);
	
		virtual void onHandleMessage(MessageId msgId) = 0;
	
		inline bool isShowing(void) { return mActiveFlag; }
	
	private:
		bool mActiveFlag;
};




#endif
