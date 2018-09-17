#include "GUI/SystemConfigWindow.h"
#include "Driver/DeliverUart.h"
#include "Task/GUITask.h"
#include "GUI/PriceWindow.h"
#include "GUI/ChangePINWindow.h"
#include "Custom/WaresManager.h"
#include "GUI/StatusWindow.h"

#define	ID_WINDOW_SYSTEM			(GUI_ID_USER + 0x05)
#define ID_TEXT_LOCK				(GUI_ID_USER + 0x06)
#define ID_TEXT_PIN					(GUI_ID_USER + 0x07)
#define ID_TEXT_REPLENISH			(GUI_ID_USER + 0x08)
#define ID_TEXT_PRICE				(GUI_ID_USER + 0x09)

SystemConfigWindow::SystemConfigWindow(void) : isShow(false)
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
	
void SystemConfigWindow::show(void)
{
	if (isShow) {
		return;
	}
	TEXT_Handle hText;
	
	mWindow = WINDOW_CreateUser(0, 0, 480, 320, WM_HBKWIN, WM_CF_SHOW, 0, ID_WINDOW_SYSTEM, _aCallback, 4);
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
	
	isShow = true;
}		

void SystemConfigWindow::unLock(void)
{
	DeliverUart::instance().setAction(0x08).append1(0x02).buildAndWrite();
}

void SystemConfigWindow::dismiss(void)
{
	WM_DeleteWindow(mWindow);
	isShow = false; 
}

void SystemConfigWindow::onKeyClick(uint16_t keyValue)
{
	switch (keyValue)
	{
		case ID_KEY_VALUE_CAN:
			dismiss();
			break;
		
		case ID_KEY_VALUE_1:
			unLock();
			break;
		
		case ID_KEY_VALUE_2:
			ChangePINWindow::instance().show(mWindow);
			break;
		
		case ID_KEY_VALUE_4:
			PriceWindow::instance().show(mWindow);
			break;
		
		case ID_KEY_VALUE_5:
			StatusWindow::instance().show(mWindow);
			break;
	}
}

bool SystemConfigWindow::isShowing(void)
{
	return isShow;
}


