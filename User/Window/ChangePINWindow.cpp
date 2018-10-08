#include "Window/ChangePINWindow.h"
#include "Task/GUITask.h"
#include "Custom/WaresManager.h"

#define ID_WINDOW			(GUI_ID_USER + 0x20)
#define ID_EDIT_RAW_PIN		(GUI_ID_USER + 0x21)
#define ID_EDIT_NOW_PIN		(GUI_ID_USER + 0x22)
#define ID_TEXT_RAW			(GUI_ID_USER + 0x23)
#define ID_TEXT_NEW			(GUI_ID_USER + 0x24)


ChangePINWindow::ChangePINWindow(void) : hStatus(320, 100, 100, 100)
{}
	
static void _aCallback(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			ChangePINWindow *hWindow;
			WINDOW_GetUserData(pMsg->hWin, &hWindow, 4);
			hWindow->draw();
			break;
	}
}

void ChangePINWindow::draw(void)
{
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	
	GUI_SetColor(GUI_RED);
	GUI_SetFont(GUI_FONT_24_1);
	GUI_FillCircle(80, 240, 40);
	
	GUI_SetColor(GUI_GREEN);
	GUI_FillCircle(220, 240, 40);
	
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextAlign(GUI_TA_VCENTER);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_DispStringHCenterAt("CAN", 80, 240);
	GUI_DispStringHCenterAt("ENT", 220, 240);
}

void ChangePINWindow::show(WM_HWIN parent)
{
	BaseWindow::show(parent);
	mWindow = WINDOW_CreateUser(0, 0, 480, 320, parent, WM_CF_SHOW, 0, ID_WINDOW, _aCallback, 4);
	WINDOW_SetUserData(mWindow, &this, 4);
	
	mEditRawPIN = EDIT_CreateEx(130, 50, 130, 40, mWindow, WM_CF_SHOW, 0, ID_EDIT_RAW_PIN, 10);
	mEditNowPin = EDIT_CreateEx(130, 110, 130, 40, mWindow, WM_CF_SHOW, 0, ID_EDIT_NOW_PIN, 10);
	EDIT_SetTextAlign(mEditNowPin, EDIT_CF_HCENTER | EDIT_CF_VCENTER);
	EDIT_SetTextAlign(mEditRawPIN, EDIT_CF_HCENTER | EDIT_CF_VCENTER);
	EDIT_SetFont(mEditNowPin, GUI_FONT_32_1);
	EDIT_SetFont(mEditRawPIN, GUI_FONT_32_1);
	
	TEXT_Handle hText;
	hText = TEXT_CreateEx(15, 50, 100, 40, mWindow, WM_CF_SHOW, 0, ID_TEXT_NEW, "Original");
	TEXT_SetFont(hText, GUI_FONT_24_1);
	TEXT_SetTextAlign(hText, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	
	hText = TEXT_CreateEx(15, 110, 100, 40, mWindow, WM_CF_SHOW, 0, ID_TEXT_NEW, "New");
	TEXT_SetFont(hText, GUI_FONT_24_1);
	TEXT_SetTextAlign(hText, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	
	hStatus.show(mWindow);
	
	EDIT_SetBkColor(mEditRawPIN, EDIT_CI_ENABLED, GUI_ORANGE);
	EDIT_SetBkColor(mEditNowPin, EDIT_CI_ENABLED, GUI_WHITE);
	isEnter = false;
	nIndex = 0;
	mTextBuffer[0] = '\0';
}

void ChangePINWindow::dismiss(void)
{
	BaseWindow::dismiss();
	hStatus.dismiss();
	WM_DeleteWindow(mWindow);
}

void ChangePINWindow::enter(void)
{
	if (isEnter)
	{
		if (nIndex == 0) {
			hStatus.setStatus(UiStatus::Error);			
		} else {
			WaresManager::instance().setPassword(mTextBuffer);
			hStatus.setStatus(UiStatus::Ok);
		}
		GUI_Delay(1000);
		dismiss();
		return;
	}

	bool ret = WaresManager::instance().isPasswordEquals(mTextBuffer);
	if (ret) 
	{
		isEnter = true;
		nIndex = 0;
		EDIT_SetBkColor(mEditRawPIN, EDIT_CI_ENABLED, GUI_WHITE);
		EDIT_SetBkColor(mEditNowPin, EDIT_CI_ENABLED, GUI_ORANGE);
		hStatus.setStatus(UiStatus::Ok);
		return;
	}
	
	ret = WaresManager::instance().isPasswordDefaultEquals(mTextBuffer);
	if (ret) 
	{
		isEnter = true;
		nIndex = 0;
		EDIT_SetBkColor(mEditRawPIN, EDIT_CI_ENABLED, GUI_WHITE);
		EDIT_SetBkColor(mEditNowPin, EDIT_CI_ENABLED, GUI_ORANGE);
		hStatus.setStatus(UiStatus::Ok);
		return;
	}
	
	hStatus.setStatus(UiStatus::Error);
}

void ChangePINWindow::onHandleMessage(MessageId msgId)
{
	switch (msgId)
	{
		case MSG_BUTTON_ENTER:
			enter();
			break;
		
		case MSG_BUTTON_CANCEL:
			dismiss();
			break;
		
		case MSG_BUTTON_0:
		case MSG_BUTTON_1:
		case MSG_BUTTON_2:
		case MSG_BUTTON_3:
		case MSG_BUTTON_4:
		case MSG_BUTTON_5:
		case MSG_BUTTON_6:
		case MSG_BUTTON_7:
		case MSG_BUTTON_8:
		case MSG_BUTTON_9:
			appendText(msgId - MSG_BUTTON_0 + '0');
			break;
	}
}

void ChangePINWindow::appendText(char c)
{
	mTextBuffer[nIndex ++] = c;
	if (nIndex >= sizeof (mTextBuffer)) {
		nIndex = 0;
	}
	mTextBuffer[nIndex] = '\0';
	
	if (isEnter)
	{
		EDIT_SetText(mEditNowPin, mTextBuffer);
		return;
	}
	EDIT_SetText(mEditRawPIN, mTextBuffer);
}





