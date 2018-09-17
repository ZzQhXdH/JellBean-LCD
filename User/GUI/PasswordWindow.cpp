#include "GUI/PasswordWindow.h"
#include "Driver/LogUart.h"
#include "Task/GUITask.h"
#include "GUI/BackgroundWindow.h"
#include "Custom/WaresManager.h"

#define ID_WINDOW		GUI_ID_USER + 0x0A
#define ID_EDIT			GUI_ID_USER + 0x0B
#define ID_BUTTON0		GUI_ID_USER + 0x0D
#define ID_BUTTON1		GUI_ID_USER + 0x0E


PasswordWindow::PasswordWindow(void) : isShow(false)
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

void PasswordWindow::show(void)
{
	mWindow = WINDOW_CreateUser(0, 0, 480, 320, WM_HBKWIN, WM_CF_SHOW, 0, ID_WINDOW, _aCallback, 4);
	WINDOW_SetUserData(mWindow, &this, 4);
	
	mEdit = EDIT_CreateEx(20, 80, 420, 80, mWindow, WM_CF_SHOW, 0, ID_EDIT, 10);

	EDIT_SetTextAlign(mEdit, GUI_TA_VCENTER | GUI_TA_HCENTER);
	EDIT_SetFont(mEdit, GUI_FONT_D48);
	EDIT_SetText(mEdit, "");

	isShow = true;
	mTextLength = 0;
	mText[0] = '\0';
	GUITask::instance().startTimer(10 * 1000);
}

void PasswordWindow::dismiss(void)
{
	GUITask::instance().stop();
	isShow = false;
	BackgroundWindow::instance().clearAllCount();
	WM_DeleteWindow(mWindow);
	mTextLength = 0;
}

void PasswordWindow::dismissAtOnce(void)
{
	GUITask::instance().stop();
	isShow = false;
	BackgroundWindow::instance().clearAllCount();
	WM_DeleteWindow(mWindow);
	mTextLength = 0;
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

void PasswordWindow::onKeyClick(uint16_t keyValue)
{
	switch (keyValue)
	{
		case ID_KEY_VALUE_ENT:
			if (isChecked()) 
			{
				dismissAtOnce();
				SystemConfigWindow::instance().show();
			}
			break;
		
		case ID_TIMER_EVENT:
			dismissAtOnce();
			break;
		
		case ID_KEY_VALUE_CAN:
			dismiss();
			break;
		
		default:
			append(keyValue - ID_KEY_VALUE_0 + '0');
	}
	
}

bool PasswordWindow::isShowing(void)
{
	return isShow;
}

