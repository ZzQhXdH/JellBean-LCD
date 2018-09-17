#include "Event/LogEvent.h"
#include "Task/GUITask.h"
#include "GUI/PayWindow.h"
#include "Driver/LogUart.h"
#include "Custom/WaresManager.h"
#include "Custom/MDBManager.h"

void LogEvent::exec(void)
{
	if (!isCorrect())
	{
		return;
	}
	
	uint16_t msg;
	
	switch (type())
	{
		case 0x50:
			msg = ID_STATUS_5C;
			GUITask::instance().put(&msg);
			return;
		
		case 0x51:
			msg = ID_STATUS_10C;
			GUITask::instance().put(&msg);
			return;
		
		case 0x80:
			msg = ID_STATUS_10C;
			GUITask::instance().put(&msg);
			return;
		
		case 0x81:
			msg = ID_STATUS_5S;
			GUITask::instance().put(&msg);
			return;
		
		case 0x82:
			msg = ID_STATUS_10S;
			GUITask::instance().put(&msg);
			return;
		
		case 0x83:
			msg = ID_STATUS_20S;
			GUITask::instance().put(&msg);
			return;
		
		case 0x0D: // 收到纸币,保存在暂存区
			if (PayWindow::instance().isShowing()) {
				MDBManager::instance().gatherPaper();
			} else {
				MDBManager::instance().returnPaper();
			}
			return;
			
		case 0x03: // VPOS检测到刷卡
			if (PayWindow::instance().isShowing())
			{
				MDBManager::instance().setPos();
			}
			else 
			{
				LogUart::instance().setAction(0x13).append1(0x04).buildAndWrite();
			}
			break;
			
		case 0x05: // VPOS扣款成功
			if (PayWindow::instance().isShowing())
			{
				msg = ID_MSG_PAY_VPOS;
				GUITask::instance().put(&msg);
			}
			break;
			
		case 0x06: // VPOS钱不够
			LogUart::instance().setAction(0x13).append1(0x04).buildAndWrite();
			
			break;
	}
}








