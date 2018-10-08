#include "Task/GUITask.h"
#include <stdio.h>
#include "Custom/WindowManager.h"
#include "Custom/WaresManager.h"
#include "Driver/DeliverUart.h"
#include "Widget/UiPolygon.h"
#include "Window/PriceWindow.h"
#include "Window/StatusWindow.h"
#include "Window/SettingPriceWindow.h"
#include "Driver/LogUart.h"
#include "Window/PayWindow.h"

GUITask::GUITask(void) : 
	Task("GUI", mStack, sizeof (mStack)), 
	Receiver("GUI", mMqMem, GUI_OBJ_NUMBER, GUI_OBJ_SIZE)
{
	
}

void GUITask::run(void)
{
	GUI_Init();
	BackgroundWindow::instance();
	
	MessageId msgId;
	osStatus_t status;
	
	while (true)
	{
		GUI_Exec();
		
		status = acquireMessage(&msgId, 20);
		
		if (status != osOK) { continue; }
		
		if (!WindowManager::instance().onMessageReceiver(msgId))
		{
			BackgroundWindow::instance().onHandleMessage(msgId);
		}
	}
}
















