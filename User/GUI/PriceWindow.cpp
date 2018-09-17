#include "GUI/PriceWindow.h"
#include "Task/GUITask.h"
#include "GUI/SettingPriceWindow.h"
#include <stdio.h>
#include "Custom/WaresManager.h"

#define ID_WINDOW_MAIN		(GUI_ID_USER + 0x212)
#define ID_EDIT_1			(GUI_ID_USER + 0x213)
#define ID_EDIT_2			(GUI_ID_USER + 0x214)
#define ID_EDIT_3			(GUI_ID_USER + 0x215)
#define ID_EDIT_4			(GUI_ID_USER + 0x216)
#define ID_EDIT_5			(GUI_ID_USER + 0x217)

PriceWindow::PriceWindow(void)
{
	
}

static void _aCallback(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_PAINT: 
			PriceWindow *hWinodw;
			WINDOW_GetUserData(pMsg->hWin, &hWinodw, 4);
			hWinodw->draw();
			break;
	}
}

void PriceWindow::draw(void)
{
	GUI_SetColor(0xFF22AD36);
	GUI_FillCircle(126, 46, 26);
	
	GUI_SetColor(0xFFFE0000);
	GUI_FillCircle(126, 103, 26);
	
	GUI_SetColor(0xFFF39801);
	GUI_FillCircle(126, 160, 26);
	
	GUI_SetColor(0xFFFF00FF);
	GUI_FillCircle(126, 217, 26);
	
	GUI_SetColor(0xFF0100FA);
	GUI_FillCircle(126, 274, 26);
	
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(GUI_FONT_32_1);
	GUI_SetTextAlign(GUI_TA_VCENTER);
	GUI_DispStringHCenterAt("1", 126, 46);
	GUI_DispStringHCenterAt("2", 126, 103);
	GUI_DispStringHCenterAt("3", 126, 160);
	GUI_DispStringHCenterAt("4", 126, 217);
	GUI_DispStringHCenterAt("5", 126, 274);
	
	uint32_t price = WaresManager::instance().getPrice(1);
	sprintf(mTextBuffer, "$:%.2f", price / 100.0f);
	EDIT_SetText(mEditPrice1, mTextBuffer);
	
	price = WaresManager::instance().getPrice(2);
	sprintf(mTextBuffer, "$:%.2f", price / 100.0f);
	EDIT_SetText(mEditPrice2, mTextBuffer);
	
	price = WaresManager::instance().getPrice(3);
	sprintf(mTextBuffer, "$:%.2f", price / 100.0f);
	EDIT_SetText(mEditPrice3, mTextBuffer);
	
	price = WaresManager::instance().getPrice(4);
	sprintf(mTextBuffer, "$:%.2f", price / 100.0f);
	EDIT_SetText(mEditPrice4, mTextBuffer);
	
	price = WaresManager::instance().getPrice(5);
	sprintf(mTextBuffer, "$:%.2f", price / 100.0f);
	EDIT_SetText(mEditPrice5, mTextBuffer);
}

void PriceWindow::show(WM_HWIN parent)
{
	mWindow = WINDOW_CreateUser(0, 0, 480, 320, parent, WM_CF_SHOW, 0, ID_WINDOW_MAIN, _aCallback, 4);
	WINDOW_SetUserData(mWindow, &this, 4);
	
	mEditPrice1 = EDIT_CreateEx(200, 20, 200, 52, mWindow, WM_CF_SHOW, 0, ID_EDIT_1, 10);
	mEditPrice2 = EDIT_CreateEx(200, 77, 200, 52, mWindow, WM_CF_SHOW, 0, ID_EDIT_2, 10);
	mEditPrice3 = EDIT_CreateEx(200, 134, 200, 52, mWindow, WM_CF_SHOW, 0, ID_EDIT_3, 10);
	mEditPrice4 = EDIT_CreateEx(200, 191, 200, 52, mWindow, WM_CF_SHOW, 0, ID_EDIT_4, 10);
	mEditPrice5 = EDIT_CreateEx(200, 248, 200, 52, mWindow, WM_CF_SHOW, 0, ID_EDIT_5, 10);
	
	EDIT_SetTextAlign(mEditPrice1, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(mEditPrice1, GUI_FONT_32_1);
	
	EDIT_SetTextAlign(mEditPrice2, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(mEditPrice2, GUI_FONT_32_1);
	
	EDIT_SetTextAlign(mEditPrice3, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(mEditPrice3, GUI_FONT_32_1);
	
	EDIT_SetTextAlign(mEditPrice4, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(mEditPrice4, GUI_FONT_32_1);
	
	EDIT_SetTextAlign(mEditPrice5, GUI_TA_HCENTER | GUI_TA_VCENTER);
	EDIT_SetFont(mEditPrice5, GUI_FONT_32_1);
	
	uint32_t price = WaresManager::instance().getPrice(1);
	sprintf(mTextBuffer, "$:%2d.%02d", price / 100, price % 100);
	EDIT_SetText(mEditPrice1, mTextBuffer);
	
	price = WaresManager::instance().getPrice(2);
	sprintf(mTextBuffer, "$:%2d.%02d", price / 100, price % 100);
	EDIT_SetText(mEditPrice2, mTextBuffer);
	
	price = WaresManager::instance().getPrice(3);
	sprintf(mTextBuffer, "$:%2d.%02d", price / 100, price % 100);
	EDIT_SetText(mEditPrice3, mTextBuffer);
	
	price = WaresManager::instance().getPrice(4);
	sprintf(mTextBuffer, "$:%2d.%02d", price / 100, price % 100);
	EDIT_SetText(mEditPrice4, mTextBuffer);
	
	price = WaresManager::instance().getPrice(5);
	sprintf(mTextBuffer, "$:%2d.%02d", price / 100, price % 100);
	EDIT_SetText(mEditPrice5, mTextBuffer);
	
	isShow = true;
}

void PriceWindow::dismiss(void)
{
	isShow = false;
	WM_DeleteWindow(mWindow);
}

void PriceWindow::onKeyClick(uint16_t keyValue)
{
	switch (keyValue)
	{
		case ID_KEY_VALUE_CAN: dismiss(); break;
		case ID_KEY_VALUE_1: setState(1); SettingPriceWindow::instance().show(mWindow, 1); break;
		case ID_KEY_VALUE_2: setState(2); SettingPriceWindow::instance().show(mWindow, 2); break;
		case ID_KEY_VALUE_3: setState(3); SettingPriceWindow::instance().show(mWindow, 3); break;
		case ID_KEY_VALUE_4: setState(4); SettingPriceWindow::instance().show(mWindow, 4); break;
		case ID_KEY_VALUE_5: setState(5); SettingPriceWindow::instance().show(mWindow, 5); break;
	}
}

bool PriceWindow::isShowing(void)
{
	return isShow;
}

void PriceWindow::setState(uint32_t id)
{
	switch (id)
	{
		case 1:
			EDIT_SetBkColor(mEditPrice1, EDIT_CI_ENABLED, 0xFFFE0000);
			GUI_Delay(100);
			EDIT_SetBkColor(mEditPrice1, EDIT_CI_ENABLED, GUI_WHITE);
			break;
	
		case 2:
			EDIT_SetBkColor(mEditPrice2, EDIT_CI_ENABLED, 0xFFFE0000);
			GUI_Delay(100);
			EDIT_SetBkColor(mEditPrice2, EDIT_CI_ENABLED, GUI_WHITE);
			break;
		
		case 3:
			EDIT_SetBkColor(mEditPrice3, EDIT_CI_ENABLED, 0xFFFE0000);
			GUI_Delay(100);
			EDIT_SetBkColor(mEditPrice3, EDIT_CI_ENABLED, GUI_WHITE);
			break;
		
		case 4:
			EDIT_SetBkColor(mEditPrice4, EDIT_CI_ENABLED, 0xFFFE0000);
			GUI_Delay(100);
			EDIT_SetBkColor(mEditPrice4, EDIT_CI_ENABLED, GUI_WHITE);
			break;
		
		case 5:
			EDIT_SetBkColor(mEditPrice5, EDIT_CI_ENABLED, 0xFFFE0000);
			GUI_Delay(100);
			EDIT_SetBkColor(mEditPrice5, EDIT_CI_ENABLED, GUI_WHITE);
			break;
	}
}

