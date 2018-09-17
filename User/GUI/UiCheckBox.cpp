#include "GUI/UiCheckBox.h"

#define ID_CHECK_BOX_CUSTOM		(GUI_ID_USER + 0x222)

static void _aCallback(WM_MESSAGE *pMsg)
{
	UiCheckBox *hCheckBox;
	WINDOW_GetUserData(pMsg->hWin, &hCheckBox, 4);
	
	switch (pMsg->MsgId)
	{
		case WM_PAINT: hCheckBox->draw(); break;
	
	}
}

UiCheckBox::UiCheckBox(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height) :
	mX0(x0), mY0(y0), mWidth(width), mHeight(height)
{
	
}

void UiCheckBox::show(WM_HWIN parent)
{
	mWindow = WINDOW_CreateUser(mX0, mY0, mWidth, mHeight, parent, WM_CF_SHOW, 0, ID_CHECK_BOX_CUSTOM, _aCallback, 4);
	WINDOW_SetUserData(mWindow, &this, 4);
	WM_EnableMemdev(mWindow);
}

void UiCheckBox::draw(void)
{
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	GUI_SetPenSize(10);
	GUI_SetColor(GUI_BLUE);
	//GUI_DrawArc(mX0, mY0, )
}

void UiCheckBox::dismiss(void)
{
	WM_DeleteWindow(mWindow);
}

