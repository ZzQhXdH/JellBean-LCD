#include "Task/GUITask.h"
#include <stdio.h>
#include "Custom/WaresManager.h"
#include "Driver/DeliverUart.h"
#include "GUI/UiPolygon.h"
#include "GUI/PriceWindow.h"
#include "GUI/StatusWindow.h"
#include "GUI/SettingPriceWindow.h"
#include "Driver/LogUart.h"
#include "GUI/PayWindow.h"

GUITask::GUITask(void) : 
	Task("GUI", mStack, sizeof (mStack)), 
	Receiver("GUI", mMqMem, GUI_OBJ_NUMBER, GUI_OBJ_SIZE),
	Timer("GUI", osTimerOnce)
{
	KeyQueue::instance().setListener(this);
}

void GUITask::vKeyValueClick(KeyValue value)
{
	uint16_t id;
	
	switch (value)
	{
		case KeyCan:
			id = ID_KEY_VALUE_CAN;
			break;
		
		case KeyEnt:
			id = ID_KEY_VALUE_ENT;
			break;
		
		case Key0: id = ID_KEY_VALUE_0;
			break;
		
		case Key1: id = ID_KEY_VALUE_1;
			break;
		
		case Key2: id = ID_KEY_VALUE_2;
			break;
		
		case Key3: id = ID_KEY_VALUE_3;
			break;
		
		case Key4: id = ID_KEY_VALUE_4;
			break;
		
		case Key5: id = ID_KEY_VALUE_5;
			break;
		
		case Key6: id = ID_KEY_VALUE_6;
			break;
		
		case Key7: id = ID_KEY_VALUE_7;
			break;
		
		case Key8: id = ID_KEY_VALUE_8;
			break;
		
		case Key9: id = ID_KEY_VALUE_9;
			break;
		
		default: return;
	}
	put(&id);
}

void GUITask::vKeyClick(uint16_t key)
{
	if ((!PasswordWindow::instance().isShowing()) &&
		(!SystemConfigWindow::instance().isShowing()) )
	{
		KeyQueue::instance().push(key);
	}
}

void GUITask::vDeliverResult(DeliverEvent &env)
{
	uint8_t action = env.type();
	uint16_t msgId;
	switch (action)
	{
		case 0x89:
			msgId = (env.arg(1) == 0x00) ? ID_MSG_DELIVER_OK : ID_MSG_DELIVER_ERROR;
			put(&msgId);
			break;
		
		case 0x8A:
			mStatusByte1 = env.arg(1);
			mStatusByte2 = env.arg(2);
			mStatusByte3 = env.arg(3);
			msgId = ID_MSG_STATUS_UPDATE;
			put(&msgId);
			break;
	}
}

void GUITask::onDisplayPasswordWindow(void)
{
	uint16_t key = ID_SHOW_PASSWORD_WINDOW;
	
	put(&key);
}

void GUITask::onTimerEvent(void)
{
	uint16_t id = ID_TIMER_EVENT;
	
	if (PasswordWindow::instance().isShowing())
	{
		put(&id);
	}
}

void GUITask::run(void)
{
	GUI_Init();
	
	mWindowArray[0] = &PayWindow::instance(); // 付款
	mWindowArray[1] = &SettingPriceWindow::instance(); // 设置价格
	mWindowArray[2] = &PriceWindow::instance(); // 全部价格
	mWindowArray[3] = &ChangePINWindow::instance(); // 修改密码
	mWindowArray[4] = &StatusWindow::instance(); // 状态查看
	mWindowArray[5] = &SystemConfigWindow::instance(); // 选项
	mWindowArray[6] = &PasswordWindow::instance(); // 密码输入
	mWindowArray[7] = &BackgroundWindow::instance();
	
	BackgroundWindow::instance();
	uint16_t recvId;
	osStatus_t status;
	
	while (true)
	{
		GUI_Exec();
		
		status = recv(&recvId, 100);
		
		if (status != osOK) { continue; }
		
		for (uint16_t i = 0; i < GUI_COUNTOF(mWindowArray); i ++)
		{
			if (mWindowArray[i]->isShowing())
			{
				mWindowArray[i]->onKeyClick(recvId);
				break;
			}
		}
	}
}
















