#include "Event/KeyEvent.h"
#include "Custom/KeyQueue.h"
#include "Task/GUITask.h"

KeyEvent::KeyEvent(void) : mValue(KeyKnown) {}

KeyEvent::KeyEvent(KeyValue v) : mValue(v) {}	

void KeyEvent::exec(void)
{
	uint16_t v = 100;
	MessageId msgId;
	
	switch (mValue)
	{
		case Key0: 
			v = 0;
			msgId = MSG_BUTTON_0;
			break;
		
		case Key1:
			v = 1;
			msgId = MSG_BUTTON_1;
			break;
		
		case Key2:
			v = 2;
			msgId = MSG_BUTTON_2;
			break;
		
		case Key3:
			v = 3;
			msgId = MSG_BUTTON_3;
			break;
		
		case Key4:
			v = 4;
			msgId = MSG_BUTTON_4;
			break;
		
		case Key5:
			v = 5;
			msgId = MSG_BUTTON_5;	
			break;
		
		case Key6:
			v = 6;
			msgId = MSG_BUTTON_6;
			break;
		
		case Key7:
			v = 7;
			msgId = MSG_BUTTON_7;
			break;
		
		case Key8:
			v = 8;
			msgId = MSG_BUTTON_8;
			break;
		
		case Key9:
			v = 9;
			msgId = MSG_BUTTON_9;
			break;
		
		case KeyCan:
			msgId = MSG_BUTTON_CANCEL;
			break;
		
		case KeyEnt:
			msgId = MSG_BUTTON_ENTER;
			break;
	}
	GUITask::instance().sendMessage(msgId);
	if (v <= 9) 
	{
		bool ret = KeyQueue::instance().pushAndCheck(v);
		if (ret) 
		{
			GUITask::instance().sendMessage(MSG_SHOW_PASSWORD_WINDOW);
		}
	}
}



