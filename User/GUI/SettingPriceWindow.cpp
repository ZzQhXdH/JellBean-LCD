#include "GUI/SettingPriceWindow.h"
#include "Task/GUITask.h"
#include "Resource/StringResources.h"
#include "Custom/WaresManager.h"

#define ID_TEXT_MESSAGE			(GUI_ID_USER + 0x122)
#define ID_WINDOW_SETTING		(GUI_ID_USER + 0x123)
#define ID_TEXT_ORIGINAL		(GUI_ID_USER + 0x124)
#define ID_TEXT_NOW				(GUI_ID_USER + 0x125)
#define ID_EDIT_ORIGINAL		(GUI_ID_USER + 0x126)
#define ID_EDIT_NOW				(GUI_ID_USER + 0x127)

SettingPriceWindow::SettingPriceWindow(void) : hStatus(300, 100, 100, 100)
{
	
}

static void _aCallback(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			SettingPriceWindow *hWindow;
			WINDOW_GetUserData(pMsg->hWin, &hWindow, 4);
			hWindow->draw();
			break;
	}
}

void SettingPriceWindow::show(WM_HWIN parent, uint32_t id)
{
	isShow = true;
	mId = id;
	nInputIndex = 0;
	
	mWindow = WINDOW_CreateUser(0, 0, 480, 320, parent, WM_CF_SHOW, 0, ID_WINDOW_SETTING, _aCallback, 4);
	WINDOW_SetUserData(mWindow, &this, 4);
	
	TEXT_Handle hText;
	
	hText = TEXT_CreateEx(20, 100, 100, 40, mWindow, WM_CF_SHOW, 0, ID_TEXT_ORIGINAL, "Original");
	TEXT_SetFont(hText, GUI_FONT_24_1);
	TEXT_SetTextAlign(hText, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	
	hText = TEXT_CreateEx(20, 160, 100, 40, mWindow, WM_CF_SHOW, 0, ID_TEXT_NOW, "Now");
	TEXT_SetFont(hText, GUI_FONT_24_1);
	TEXT_SetTextAlign(hText, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	
	mTextMessage = TEXT_CreateEx(140, 240, 200, 50, mWindow, WM_CF_SHOW, 0, ID_TEXT_MESSAGE, "");
	TEXT_SetFont(mTextMessage, GUI_FONT_24_1);
	TEXT_SetTextAlign(mTextMessage, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	
	mEditOriginal = EDIT_CreateEx(130, 100, 100, 40, mWindow, WM_CF_SHOW, 0, ID_EDIT_ORIGINAL, 10);
	EDIT_SetFont(mEditOriginal, GUI_FONT_24_1);
	EDIT_SetTextAlign(mEditOriginal, EDIT_CF_HCENTER | EDIT_CF_VCENTER);
	
	uint32_t price = WaresManager::instance().getPrice(mId);
	sprintf(mTextBuffer, "$:%.2f", price / 100.0f);
	EDIT_SetText(mEditOriginal, mTextBuffer);
	
	mEditNow = EDIT_CreateEx(130, 160, 100, 40, mWindow, WM_CF_SHOW, 0, ID_EDIT_NOW, 10);
	EDIT_SetFont(mEditNow, GUI_FONT_24_1);
	EDIT_SetTextAlign(mEditNow, EDIT_CF_HCENTER | EDIT_CF_VCENTER);
	EDIT_SetBkColor(mEditNow, EDIT_CI_ENABLED, GUI_RED);
	EDIT_SetTextColor(mEditNow, EDIT_CI_ENABELD, GUI_WHITE);
	
	hStatus.show(mWindow);
}

void SettingPriceWindow::dismiss(void)
{
	isShow = false;
	WM_DeleteWindow(mWindow);
}

void SettingPriceWindow::draw(void)
{
	GUI_SetColor(0xFF22AD38);
	GUI_FillCircle(240, 50, 30);
	
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetTextAlign(GUI_TA_VCENTER);
	GUI_SetFont(GUI_FONT_32_1);
	GUI_DispStringHCenterAt( Strings[mId], 240, 50 );
}

void SettingPriceWindow::onKeyClick(uint16_t keyValue)
{
	switch (keyValue)
	{
		case ID_KEY_VALUE_CAN:
			dismiss();
			break;
		
		case ID_KEY_VALUE_ENT:
			savePrice();
			break;
		
		case ID_KEY_VALUE_0:
		case ID_KEY_VALUE_1:
		case ID_KEY_VALUE_2:
		case ID_KEY_VALUE_3:
		case ID_KEY_VALUE_4:
		case ID_KEY_VALUE_5:
		case ID_KEY_VALUE_6:
		case ID_KEY_VALUE_7:
		case ID_KEY_VALUE_8:
		case ID_KEY_VALUE_9:
			appendText( keyValue - ID_KEY_VALUE_0 + '0' );
			break;
	}
}

void SettingPriceWindow::savePrice(void)
{
	uint32_t price;
	sscanf(mTextBuffer, "%d", &price);
	WaresManager::instance().setPrice(mId, price);
	hStatus.setStatus(UiStatus::Ok);
	TEXT_SetText(mTextMessage, "Success");
}

void SettingPriceWindow::appendText(char c)
{
	if (nInputIndex > 10) {
		nInputIndex = 0;
	}
	mTextBuffer[nInputIndex ++] = c;
	mTextBuffer[nInputIndex] = '\0';
	EDIT_SetText(mEditNow, mTextBuffer);
}


bool SettingPriceWindow::isShowing(void)
{
	return isShow;
}

