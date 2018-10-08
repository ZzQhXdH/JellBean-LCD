#include "Window/SystemConfigWindow.h"
#include "Driver/DeliverUart.h"
#include "Task/GUITask.h"
#include "Window/PriceWindow.h"
#include "Window/ChangePINWindow.h"
#include "Custom/WaresManager.h"
#include "Window/StatusWindow.h"

#define	ID_WINDOW_SYSTEM			(GUI_ID_USER + 0x05)
#define ID_TEXT_LOCK				(GUI_ID_USER + 0x06)
#define ID_TEXT_PIN					(GUI_ID_USER + 0x07)
#define ID_TEXT_REPLENISH			(GUI_ID_USER + 0x08)
#define ID_TEXT_PRICE				(GUI_ID_USER + 0x09)

SystemConfigWindow::SystemConfigWindow(void)
{}

static void _aCallback(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			SystemConfigWindow *hWindow;
			WINDOW_GetUserData(pMsg->hWin, &hWindow, 4);
			hWindow->draw();
			break;
	}
}

void SystemConfigWindow::draw(void)
{
	GUI_SetColor(0xFF0296FA);
	GUI_FillCircle(75, 49, 25);
	
	GUI_SetColor(0xFFFD0100);
	GUI_FillCircle(75, 123, 25);
	
	GUI_SetColor(0xFF00FD02);
	GUI_FillCircle(75, 197, 25);
	
	GUI_SetColor(0xFFFF00FE);
	GUI_FillCircle(75, 271, 25);
	
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(GUI_FONT_32_1);
	GUI_SetTextAlign(GUI_TA_VCENTER);
	GUI_DispStringHCenterAt("1", 75, 49);
	GUI_DispStringHCenterAt("2", 75, 123);
	GUI_DispStringHCenterAt("3", 75, 197);
	GUI_DispStringHCenterAt("4", 75, 271);
}
	
void SystemConfigWindow::show(WM_HWIN parent)
{
	BaseWindow::show(parent);
	TEXT_Handle hText;
	
	mWindow = WINDOW_CreateUser(0, 0, 480, 320, parent, WM_CF_SHOW, 0, ID_WINDOW_SYSTEM, _aCallback, 4);
	WINDOW_SetUserData(mWindow, &this, 4);
	
	hText = TEXT_CreateEx(150, 24, 200, 50, mWindow, WM_CF_SHOW, 0, ID_TEXT_LOCK, "Unlock");
	TEXT_SetFont(hText, GUI_FONT_32_1);
	TEXT_SetTextAlign(hText, GUI_TA_LEFT | GUI_TA_VCENTER);
	TEXT_SetTextColor(hText, GUI_MAKE_COLOR(0x00404080));
	
	hText = TEXT_CreateEx(150, 98, 200, 50, mWindow, WM_CF_SHOW, 0, ID_TEXT_PIN, "Change pin");
	TEXT_SetFont(hText, GUI_FONT_32_1);
	TEXT_SetTextAlign(hText, GUI_TA_LEFT | GUI_TA_VCENTER);
	TEXT_SetTextColor(hText, GUI_MAKE_COLOR(0x00404080));
	
	hText = TEXT_CreateEx(150, 172, 200, 50, mWindow, WM_CF_SHOW, 0, ID_TEXT_REPLENISH, "Replenish");
	TEXT_SetFont(hText, GUI_FONT_32_1);
	TEXT_SetTextAlign(hText, GUI_TA_LEFT | GUI_TA_VCENTER);
	TEXT_SetTextColor(hText, GUI_MAKE_COLOR(0x00404080));
	
	hText = TEXT_CreateEx(150, 246, 200, 50, mWindow, WM_CF_SHOW, 0, ID_TEXT_PRICE, "Change price");
	TEXT_SetFont(hText, GUI_FONT_32_1);
	TEXT_SetTextAlign(hText, GUI_TA_LEFT | GUI_TA_VCENTER);
	TEXT_SetTextColor(hText, GUI_MAKE_COLOR(0x00404080));
}		

void SystemConfigWindow::unLock(void)
{
	DeliverUart::instance().setAction(0x08).append1(0x02).buildAndWrite();
}

void SystemConfigWindow::dismiss(void)
{
	BaseWindow::dismiss();
	WM_DeleteWindow(mWindow);
}

void SystemConfigWindow::onHandleMessage(MessageId msgId)
{
	switch (msgId)
	{
		case MSG_BUTTON_CANCEL:
			dismiss();
			break;
		
		case MSG_BUTTON_1:
			unLock();
			dismiss();
			break;
		
		case MSG_BUTTON_2:
			dismiss();
			ChangePINWindow::instance().show(WM_HBKWIN);
			break;
		
		case MSG_BUTTON_4:
			dismiss();
			PriceWindow::instance().show(WM_HBKWIN);
			break;
		
		case MSG_BUTTON_5:
			dismiss();
			StatusWindow::instance().show(WM_HBKWIN);
			break;
	}
}


