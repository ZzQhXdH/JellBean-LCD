#include "Widget/UiStatus.h"
#include "Widget/UiPolygon.h"

#define ID_WINDOW_STATUS		(GUI_ID_USER + 0x132)



UiStatus::UiStatus(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height) :
	mX0(x0), mY0(y0), mWidth(width), mHeight(height)
{
	mDiameter = (mWidth < mHeight ? mWidth : mHeight);
}

static void _aCallback(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			UiStatus *hStatus;
			WINDOW_GetUserData(pMsg->hWin, &hStatus, 4);
			hStatus->draw();
			break;
	}
}

void UiStatus::draw(void)
{
	switch (mStatus)
	{
		case Error:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			GUI_SetColor(GUI_RED);
	
		UiPolygon::instance().begin()
			.append(mDiameter / 8.0f, mDiameter)
			.append(mDiameter, mDiameter / 8.0f)
			.append(mDiameter * 7 / 8.0f, 0)
			.append(0, mDiameter * 7 / 8.0f)
			.fill(0, 0);
		
		UiPolygon::instance().begin()
			.append(mDiameter * 7 / 8.0f, mDiameter)
			.append(mDiameter, mDiameter * 7 / 8.0f)
			.append(mDiameter / 8.0f, 0)
			.append(0, mDiameter / 8.0f)
			.fill(0, 0);
			break;
		
		case Ok:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
			GUI_SetColor(GUI_GREEN);
			UiPolygon::instance().begin()
			.append(18, 100 - 44)
			.append(37, 100 - 25)
			.append(82, 100 - 70)
			.append(75, 100 - 77)
			.append(37, 100 - 39)
			.append(25, 100 - 51)
			.fill(0, 0);
			break;
		
		case Gone:
			GUI_SetBkColor(GUI_WHITE);
			GUI_Clear();
		
			break;
	}

}

void UiStatus::setStatus(Status s)
{
	mStatus = s;
	WM_InvalidateWindow(mWindow);
}

void UiStatus::show(WM_HWIN parent)
{
	mStatus = Gone;
	mWindow = WINDOW_CreateUser(mX0, mY0, mWidth, mHeight, parent, WM_CF_SHOW, 0, ID_WINDOW_STATUS, _aCallback, 4);
	WINDOW_SetUserData(mWindow, &this, 4);
}

void UiStatus::dismiss(void)
{
	WM_DeleteWindow(mWindow);
}







