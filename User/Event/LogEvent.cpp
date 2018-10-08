#include "Event/LogEvent.h"
#include "Task/GUITask.h"
#include "Window/PayWindow.h"
#include "Driver/LogUart.h"
#include "Custom/WaresManager.h"
#include "Custom/MDBManager.h"

void LogEvent::exec(void)
{
	if (!isCorrect())
	{
		return;
	}
	
	switch (type())
	{
		case 0x50: // 收到一个5角钱的硬币
			if (!PayWindow::instance().isShowing()) {
				MDBManager::instance().giveChange(50);
				return;
			}
			MDBManager::instance().onCashChecked(50);	
			GUITask::instance().sendMessage(MSG_CHECKED_CASH);
			return;
		
		case 0x51: // 收到一个1元硬币
			if (!PayWindow::instance().isShowing()) {
				MDBManager::instance().giveChange(100);
				return;
			}
			MDBManager::instance().onCashChecked(100);
			GUITask::instance().sendMessage(MSG_CHECKED_CASH);
			return;
		
		case 0x80: // 收到一个1元纸币
			if (!PayWindow::instance().isShowing()) {
				MDBManager::instance().giveChange(100);
				return;
			}
			MDBManager::instance().onCashChecked(100);
			GUITask::instance().sendMessage(MSG_CHECKED_CASH);
			return;
		
		case 0x81: // 收到5元纸币
			if (!PayWindow::instance().isShowing()) {
				MDBManager::instance().giveChange(500);
				return;
			}
			MDBManager::instance().onCashChecked(500);
			GUITask::instance().sendMessage(MSG_CHECKED_CASH);
			return;
		
		case 0x82: // 收到10元纸币
			if (!PayWindow::instance().isShowing()) {
				MDBManager::instance().giveChange(1000);
				return;
			}
			MDBManager::instance().onCashChecked(1000);
			GUITask::instance().sendMessage(MSG_CHECKED_CASH);
			return;
		
		case 0x83: // 收到20元纸币
			if (!PayWindow::instance().isShowing()) {
				MDBManager::instance().giveChange(2000);
				return;
			}
			MDBManager::instance().onCashChecked(2000);
			GUITask::instance().sendMessage(MSG_CHECKED_CASH);
			return;
		
		case 0x0D: // 收到纸币,保存在暂存区
			if (PayWindow::instance().isShowing()) { // 如果处于收钱状态
				LogUart::instance()
					.setAction(0x08) // 收进来
					.buildAndWrite();
			} else {
				LogUart::instance()
					.setAction(0x09) // 退出去
					.buildAndWrite();
			}
			return;
			
		case 0x05: // VPOS扣款成功
			if (PayWindow::instance().isShowing())
			{
				MDBManager::instance().onVposChecked();
				GUITask::instance().sendMessage(MSG_CHECKED_VPOS);
			}
			else
			{
				LogUart::instance()
					.setAction(0x13)
					.append1(0x01)
					.buildAndWrite();
				LogUart::instance()
					.setAction(0x13)
					.append1(0x04)
					.buildAndWrite();
			}
			break;
			
		case 0x06: // VPOS钱不够
			LogUart::instance().setAction(0x13).append1(0x04).buildAndWrite();
			
			break;
	}
}








