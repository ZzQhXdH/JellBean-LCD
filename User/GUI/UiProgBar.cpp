#include "GUI/UiProgBar.h"
#include "Resource/StringResources.h"
#include "Driver/LogUart.h"
#include "Custom/WaresManager.h"
#include "Custom/MDBManager.h"
#include <arm_math.h>

#define ID_PROGBAR			(GUI_ID_USER + 0x47)
#define ID_WINDOW			(GUI_ID_USER + 0x48)
#define ID_CHECK_BOX		(GUI_ID_USER + 0x49)
#define ID_TEXT				(GUI_ID_USER + 0x4A)

#define WIDTH				480
#define HEIGHT				320

#define CHECK_BOX_X0		280
#define CHECK_BOX_Y0		60
#define CHECK_BOX_WIDTH		100
#define CHECK_BOX_HEIGHT	100

#define TEXT_X0				240
#define TEXT_Y0				220
#define TEXT_WIDTH			200
#define TEXT_HEIGHT			50

static uint16_t ProgBarMaxValue;
static uint16_t ProgBarCurrentValue;


UiProgBar::UiProgBar(void) : hStatus(CHECK_BOX_X0, CHECK_BOX_Y0, CHECK_BOX_WIDTH, CHECK_BOX_HEIGHT)
{
}

inline static uint16_t progBarGetEnd(void)
{
	return 90 + ProgBarCurrentValue * 360 / ProgBarMaxValue;
}

static void _aWindowCallback(WM_MESSAGE *pMsg)
{
	if (pMsg->MsgId == WM_PAINT)
	{
		GUI_SetBkColor(GUI_WHITE);
		GUI_Clear();
	}
}

static void _aProgBarCallback(WM_MESSAGE *pMsg)
{
	if (pMsg->MsgId != WM_PAINT) {
		return;
	}
	GUI_SetBkColor(GUI_WHITE);
	GUI_SetPenSize(30);
	GUI_Clear();
	
	GUI_SetColor(GUI_GRAY);
	GUI_AA_DrawArc(80, 80, 65, 65, 0, 360);
	
	GUI_SetColor(GUI_ORANGE);
	GUI_AA_DrawArc(80, 80, 65, 65, 90, progBarGetEnd());
	GUI_AA_FillCircle(80, 15, 15);
	float s, c;
	arm_sin_cos_f32(progBarGetEnd(), &s, &c);
	GUI_AA_FillCircle(80 + 65 * c, 80 - 65 * s, 15);
	
	GUI_SetFont(GUI_FONT_32B_1);
	GUI_DispStringHCenterAt( Strings[ProgBarCurrentValue], 80, 80 - 16 );
}
// 40 80 160 160
void UiProgBar::draw(void)
{
}

void UiProgBar::show(UiProgBarTimeOutListener *listen, uint16_t max)
{
	isShow = true;
	ProgBarCurrentValue = 0;
	ProgBarMaxValue = max;
	timeOutListen = listen;
	
	mWindow = WINDOW_CreateEx(0, 0, WIDTH, HEIGHT, WM_HBKWIN, WM_CF_SHOW, 0, ID_WINDOW, _aWindowCallback);
	
	hStatus.show(mWindow);
	
	mText = TEXT_CreateEx(TEXT_X0, TEXT_Y0, TEXT_WIDTH, TEXT_HEIGHT, mWindow, WM_CF_SHOW, 0, ID_TEXT, "Please Wait ...");
	TEXT_SetFont(mText, GUI_FONT_32B_ASCII);
	TEXT_SetTextColor(mText, GUI_ORANGE);
	TEXT_SetTextAlign(mText, TEXT_CF_HCENTER);
	
	mProgBar = WINDOW_CreateEx(40, 80, 160, 160, mWindow, WM_CF_SHOW, 0, ID_PROGBAR, _aProgBarCallback);
	
	WM_EnableMemdev(mProgBar);
}

void UiProgBar::success(void)
{
	hStatus.setStatus(UiStatus::Ok);
	TEXT_SetText(mText, "Success");
	MDBManager::instance().success();
	GUI_Delay(5000);
	dismiss();
}

void UiProgBar::error(void)
{
	hStatus.setStatus(UiStatus::Error);
	TEXT_SetText(mText, "Error");
	MDBManager::instance().error(); 
	GUI_Delay(5000);
	dismiss();
}

void UiProgBar::dismiss(void)
{
	isShow = false;
	hStatus.dismiss();
	MDBManager::instance().error(); 
	WM_DeleteWindow(mWindow);
}

void UiProgBar::update(void)
{
	ProgBarCurrentValue ++;
	if (ProgBarCurrentValue > ProgBarMaxValue)
	{
		timeOutListen->onProgBarTimeOut();
		return;
	}
	WM_InvalidateWindow(mProgBar);
}

bool UiProgBar::isShowing(void)
{
	return isShow;
}

