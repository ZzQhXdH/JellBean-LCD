#include "Window/PasswordWindow.h"
#include "Driver/LogUart.h"
#include "Task/GUITask.h"
#include "Window/BackgroundWindow.h"
#include "Custom/WaresManager.h"

#define ID_WINDOW		GUI_ID_USER + 0x0A
#define ID_EDIT			GUI_ID_USER + 0x0B
#define ID_BUTTON0		GUI_ID_USER + 0x0D
#define ID_BUTTON1		GUI_ID_USER + 0x0E


PasswordWindow::PasswordWindow(void)
{
}

static void _aCallback(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			PasswordWindow *hWindow;
			WINDOW_GetUserData(pMsg->hWin, &hWindow, 4);
			hWindow->draw();
			break;
	}
}

void PasswordWindow::draw(void)
{
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	
	GUI_SetColor(GUI_RED);
	GUI_FillCircle(140, 220, 40);
	
	GUI_SetColor(GUI_BLUE);
	GUI_FillCircle(340, 220, 40);
	
	GUI_SetColor(GUI_WHITE);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(GUI_FONT_24_1);
	GUI_SetTextAlign(GUI_TA_VCENTER);
	GUI_DispStringHCenterAt("CAN", 140, 220);
	GUI_DispStringHCenterAt("ENT", 340, 220);
	
	GUI_SetColor(GUI_RED);
	GUI_SetFont(GUI_FONT_16_1);
	GUI_DispStringHCenterAt("enter your PIN", 240, 30);
}

void PasswordWindow::show(WM_HWIN parent)
{
	BaseWindow::show(parent);
	mWindow = WINDOW_CreateUser(0, 0, 480, 320, parent, WM_CF_SHOW, 0, ID_WINDOW, _aCallback, 4);
	WINDOW_SetUserData(mWindow, &this, 4);
	
	mEdit = EDIT_CreateEx(20, 80, 420, 80, mWindow, WM_CF_SHOW, 0, ID_EDIT, 10);

	EDIT_SetTextAlign(mEdit, GUI_TA_VCENTER | GUI_TA_HCENTER);
	EDIT_SetFont(mEdit, GUI_FONT_D48);
	EDIT_SetText(mEdit, "");

	mTextLength = 0;
	mText[0] = '\0';
}

void PasswordWindow::dismiss(void)
{
	BaseWindow::dismiss();
	WM_DeleteWindow(mWindow);
}

void PasswordWindow::append(char c)
{
	mText[mTextLength] = c;
	mTextLength ++;
	if (mTextLength >= 10) {
		return;
	}
	mText[mTextLength] = '\0';
	EDIT_SetText(mEdit, mText);
}

void PasswordWindow::clear(void)
{
	mTextLength = 0;
	EDIT_SetText(mEdit, "");
}

bool PasswordWindow::isChecked(void)
{
	bool ret = WaresManager::instance().isPasswordEquals(mText);
	
	if (ret) {
		return true;
	}
	
	ret = WaresManager::instance().isPasswordDefaultEquals(mText);
	if (ret) {
		return true;
	}
	
	return false;
}

void PasswordWindow::onHandleMessage(MessageId msgId)
{
	switch (msgId)
	{
		case MSG_BUTTON_ENTER:
			dismiss();
			if (isChecked()) {
				SystemConfigWindow::instance().show(WM_HBKWIN);
			}
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
			append(msgId - MSG_BUTTON_0 + '0');
			break;
	}
	
}

