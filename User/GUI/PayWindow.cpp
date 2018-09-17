#include "GUI/PayWindow.h"
#include "Resource/StringResources.h"
#include "Task/GUITask.h"
#include "Driver/LogUart.h"
#include "Custom/WaresManager.h"
#include "Task/GUITask.h"
#include "Custom/MDBManager.h"
#include <stdio.h>

#define ID_WINDOW_PAY		(GUI_ID_USER + 0x32)
#define ID_TEXT_1			(GUI_ID_USER + 0x33)
#define ID_TEXT_2			(GUI_ID_USER + 0x34)
#define ID_TEXT_3			(GUI_ID_USER + 0x31)
#define ID_TEXT_4			(GUI_ID_USER + 0x35)
#define ID_TEXT_5			(GUI_ID_USER + 0x36)

#define ID_TEXT_5C			(GUI_ID_USER + 0x37)
#define ID_TEXT_10C			(GUI_ID_USER + 0x38)
#define ID_TEXT_5S			(GUI_ID_USER + 0x39)
#define ID_TEXT_10S			(GUI_ID_USER + 0x3A)
#define	ID_TEXT_20S			(GUI_ID_USER + 0x3B)
#define ID_TEXT_ALL			(GUI_ID_USER + 0x3C)

#define ID_TEXT_TITLE		(GUI_ID_USER + 0x3D)
#define ID_TEXT_MESSAGE		(GUI_ID_USER + 0x3E)
#define ID_TEXT_REFUND		(GUI_ID_USER + 0x3F)


static void _aCallback(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_PAINT: 
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			break;
	}
}


PayWindow::PayWindow(void) : Timer("Timer", osTimerOnce)
{
	isShow = false;
}


void PayWindow::show(WM_HWIN parent, uint32_t price)
{
	mNeed = price;
	
	mWindow = WINDOW_CreateUser(0, 0, 480, 320, parent, WM_CF_SHOW, 0, ID_WINDOW_PAY, _aCallback, 4);
	
	mTextTitle = TEXT_CreateEx(0, 0, 480, 90, mWindow, WM_CF_SHOW, 0, ID_TEXT_TITLE, "");
	TEXT_SetFont(mTextTitle, GUI_FONT_32_ASCII);
	TEXT_SetTextColor(mTextTitle, 0xFF0080);
	TEXT_SetTextAlign(mTextTitle, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	
	mTextMessage = TEXT_CreateEx(0, 130, 480, 60, mWindow, WM_CF_SHOW, 0, ID_TEXT_MESSAGE, "");
	TEXT_SetFont(mTextMessage, GUI_FONT_24_ASCII);
	TEXT_SetTextColor(mTextMessage, GUI_ORANGE);
	TEXT_SetTextAlign(mTextMessage, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	
	mTextRefund = TEXT_CreateEx(0, 240, 480, 60, mWindow, WM_CF_SHOW, 0, ID_TEXT_REFUND, "");
	TEXT_SetFont(mTextRefund, GUI_FONT_24_ASCII);
	TEXT_SetTextColor(mTextRefund, GUI_RED);
	TEXT_SetTextAlign(mTextRefund, TEXT_CF_HCENTER | TEXT_CF_VCENTER);
	
	sprintf(mTextBuffer, "Please pay $%.2f", mNeed / 100.0f);
	TEXT_SetText(mTextTitle, mTextBuffer);
	
	sprintf(mTextBuffer, "We have received $%.2f", 0.0f);
	TEXT_SetText(mTextMessage, mTextBuffer);
	
	mCounter5c = 0;
	mCounter10c = 0;
	mCounter5s = 0;
	mCounter10s = 0;
	mCounter20s = 0;
	
	MDBManager::instance().payStart(price);
	isShow = true;
	startTimer(60 * 1000);
}

void PayWindow::onKeyClick(uint16_t keyValue)
{
	switch (keyValue)
	{
		case ID_STATUS_5C: recv5c(); break;
		case ID_STATUS_10C: recv10c(); break;
		case ID_STATUS_5S: recv5s(); break;
		case ID_STATUS_10S: recv10s(); break;
		case ID_STATUS_20S: recv20s(); break;
		case ID_KEY_VALUE_CAN: dismiss(); break;
		case ID_MSG_PAY_TIME_OUT: timeOut();  break;
		case ID_MSG_PAY_VPOS: statOfVpos(); break;
	}
}

bool PayWindow::isShowing(void)
{
	return isShow;
}

void PayWindow::timeOut(void)
{
	BackgroundWindow::instance().clearAllCount();
	dismiss();
}

void PayWindow::dismiss(void)
{
	WM_DeleteWindow(mWindow);
	stopTimer();
	isShow = false;
	MDBManager::instance().payStop();
}

void PayWindow::statOfVpos(void)
{
	sprintf(mTextBuffer, "We have received VPOS $%.2f", mNeed / 100.0f);
	TEXT_SetText(mTextMessage, mTextBuffer);
	MDBManager::instance().isPaySuccess = true;
	GUI_Delay(1000);
	uint16_t msgId = ID_MSG_START_DELIVER;
	GUITask::instance().put(&msgId);
	dismiss();
}

void PayWindow::recv5c(void)
{
	mCounter5c ++;
	stat();
}

void PayWindow::recv10c(void)
{
	mCounter10c ++;
	stat();
}

void PayWindow::recv5s(void)
{
	mCounter5s ++;
	stat();
}

void PayWindow::recv10s(void)
{
	mCounter10s ++;
	stat();
}

void PayWindow::recv20s(void)
{
	mCounter20s ++;
	stat();
}

void PayWindow::onTimerEvent(void)
{
	uint16_t msgId= ID_MSG_PAY_TIME_OUT;
	GUITask::instance().put(&msgId);
}


void PayWindow::stat(void)
{
	uint32_t s = mCounter5c * 50 + mCounter10c * 100 +
				mCounter5s * 500 + mCounter10s * 1000 + mCounter20s * 2000; // ∑÷
	MDBManager::instance().isCashPay = true;
	MDBManager::instance().MoneyAlready = s;
	sprintf(mTextBuffer, "We have received $%.2f", s / 100.0f);
	TEXT_SetText(mTextMessage, mTextBuffer);
	
	if (s > mNeed)
	{
		uint16_t count = (s - mNeed) / 50;
		sprintf(mTextBuffer, "Change:$%.2f", (s - mNeed) / 100.0f);
		TEXT_SetText(mTextRefund, mTextBuffer);
		MDBManager::instance().giveChange(count); // ’“«Æ
		GUI_Delay(1000);
		MDBManager::instance().isPaySuccess = true;
		MDBManager::instance().MoneyAlready = mNeed;
		uint16_t msgId = ID_MSG_START_DELIVER;
		GUITask::instance().put(&msgId);
		dismiss();
	}
	else if (s == mNeed)
	{
		MDBManager::instance().isPaySuccess = true;
		MDBManager::instance().MoneyAlready = mNeed;
		uint16_t msgId = ID_MSG_START_DELIVER;
		GUITask::instance().put(&msgId);
		dismiss();
	}
}


