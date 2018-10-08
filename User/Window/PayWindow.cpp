#include "Window/PayWindow.h"
#include "Resource/StringResources.h"
#include "Task/GUITask.h"
#include "Driver/LogUart.h"
#include "Custom/WaresManager.h"
#include "Task/GUITask.h"
#include "Custom/MDBManager.h"
#include <stdio.h>

/**
 * @brief 支付界面窗口
 * 等待消费者进行刷卡或者投币(纸币和银币)
 * 提示消费者所需要支付的金额
 * 支付成功 => 开始出货
 * 支付失败 => 退钱
 * 等待超时时间 => 60s
 */

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

void PayWindow::onTimerEvent(void)
{
	GUITask::instance().sendMessage(MSG_PAY_TIME_OUT);
}

PayWindow::PayWindow(void) : Timer("Timer", osTimerOnce)
{
}

void PayWindow::showWithPrice(WM_HWIN parent, uint32_t price)
{
	BaseWindow::show(parent);
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
	
	sprintf(mTextBuffer, "Please pay $%.2f", price / 100.0f);
	TEXT_SetText(mTextTitle, mTextBuffer);
	
	sprintf(mTextBuffer, "We have received $%.2f", 0.0f);
	TEXT_SetText(mTextMessage, mTextBuffer);
	
	MDBManager::instance().onPayStart(price);
	startTimer(60 * 1000);
}

void PayWindow::onHandleMessage(MessageId msgId)
{
	switch (msgId)
	{
		case MSG_CHECKED_CASH: onCashUpdate(); break; // 收到现金支付消息
		case MSG_CHECKED_VPOS: onVposUpdate(); break; // 收到VPOS刷卡消息
		case MSG_BUTTON_CANCEL: dismiss(); break; // 收到按下了取消按钮的消息
		case MSG_PAY_TIME_OUT: dismiss();  break; // 支付超时
	}
}

void PayWindow::onCashUpdate(void)
{
	sprintf(mTextBuffer, "Received cash:$%.2f", MDBManager::instance().getAlreadyMoney() / 100.0f);
	TEXT_SetText(mTextMessage, mTextBuffer);
	if (MDBManager::instance().isPaySuccessing())
	{
		GUI_Delay(500);
		BackgroundWindow::instance().deliver();
		dismiss();
		DeliverWindow::instance().showWithTimeOut(WM_HBKWIN, 100);
	}
}

void PayWindow::onVposUpdate(void)
{
	sprintf(mTextBuffer, "Vpos PaySuccess");
	TEXT_SetText(mTextMessage, mTextBuffer);
	if (MDBManager::instance().isPaySuccessing())
	{
		GUI_Delay(500);
		BackgroundWindow::instance().deliver();
		dismiss();
		DeliverWindow::instance().showWithTimeOut(WM_HBKWIN, 100);
	}
}

void PayWindow::dismiss(void)
{
	BaseWindow::dismiss();
	WM_DeleteWindow(mWindow);
	stopTimer();
	BackgroundWindow::instance().clearAllCount();
	MDBManager::instance().onPayStop();
}



