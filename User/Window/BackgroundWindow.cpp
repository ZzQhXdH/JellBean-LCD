#include "Window/BackgroundWindow.h"
#include "Widget/UiPolygon.h"
#include "Driver/LogUart.h"
#include "Driver/DeliverUart.h"
#include "Window/PasswordWindow.h"
#include "Task/GUITask.h"
#include "Window/PayWindow.h"
#include "Custom/MDBManager.h"
#include "Custom/WaresManager.h"

void displayTrapezoid1(uint32_t color);
void displayTrapezoid2(uint32_t color);
void displayTrapezoid3(uint32_t color);
void displayTrapezoid4(uint32_t color);
void displayTrapezoid5(uint32_t color);

uint32_t ColorArray[] = { COLOR5, COLOR4, COLOR3, COLOR2, COLOR1 };

void (*DrawArrayFuncation[])(uint32_t) = { displayTrapezoid5, displayTrapezoid4, displayTrapezoid3, displayTrapezoid2, displayTrapezoid1 };

const char *NumberTextArray[] = {"0", "1", "2", "3", "4", "5"};

static void aBackgroundWindowCallback(WM_MESSAGE* pMsg)
{
	BackgroundWindow::instance().onCallback(pMsg);
}

void BackgroundWindow::onCallback(WM_MESSAGE *pMsg)
{
	switch (pMsg->MsgId)
	{
		case WM_PAINT:
			BackgroundWindow::instance().draw();
			break;
		
		default:
			WM_DefaultProc(pMsg);
			break;
	}
}

void BackgroundWindow::deliver(void)
{
	DeliverUart::instance()
		.setAction(0x09)
		.append1(mCountArray[0])
		.append1(mCountArray[1])
		.append1(mCountArray[2])
		.append1(mCountArray[3])
		.append1(mCountArray[4])
		.buildAndWrite();
}

BackgroundWindow::BackgroundWindow(void)
{
	WM_SetCallback(WM_HBKWIN, aBackgroundWindowCallback);
	clearAllCount();
}

void BackgroundWindow::show(WM_HWIN parent)
{
}

void BackgroundWindow::onHandleMessage(MessageId msgId)
{	
	switch (msgId)
	{
		case MSG_BUTTON_1:
		case MSG_BUTTON_2:
		case MSG_BUTTON_3:
		case MSG_BUTTON_4:
		case MSG_BUTTON_5: 
			{
				uint16_t v = msgId - MSG_BUTTON_1;
				if (getAllCount() < 5) {
					mCountArray[ v ] ++;
				} else {
					clearAllCount();
				}
				invaliate();
			};
			break;
		
		case MSG_SHOW_PASSWORD_WINDOW:
			PasswordWindow::instance().show(WM_HBKWIN);
			break;
		
		case MSG_BUTTON_ENTER:
			if (getAllCount() <= 0) {
				break;
			}
			WaresManager::instance().setSelectNumber(mCountArray);
			PayWindow::instance().showWithPrice(WM_HBKWIN, getAllPrice());
			break;
				
		case MSG_BUTTON_CANCEL:
			clearAllCount();
			invaliate();
			break;
	}
}

void BackgroundWindow::drawForAndTo(uint16_t from, uint16_t to, uint32_t color)
{
	for (uint16_t i = from; i < to; i ++)
	{
		DrawArrayFuncation[i](color);
	}
}

void BackgroundWindow::draw(void)
{	
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	
	GUI_SetColor(COLORT);
	
	GUI_FillRect(140, 44, 340, 52);
	
	UiPolygon::instance()
		.begin()
		.append(322, 52)
		.append(327, 52)
		.append(300, 272)
		.append(180, 272)
		.append(153, 52)
		.append(158, 52)
		.append(185, 267)
		.append(296, 267)
		.append(322, 52)
		.fill(0, 0);
	
	GUI_SetPenSize(3);
	
	GUI_SetColor(COLOR1);
	GUI_DrawArc( CIRCLE1_X, CIRCLE1_Y, CIRCLE_R, CIRCLE_R, 0, 360 );
	
	GUI_SetColor(COLOR2);
	GUI_DrawArc(CIRCLE2_X, CIRCLE2_Y, CIRCLE_R, CIRCLE_R, 0, 360);
	
	GUI_SetColor(COLOR3);
	GUI_DrawArc(CIRCLE3_X, CIRCLE3_Y, CIRCLE_R, CIRCLE_R, 0, 360);
	
	GUI_SetColor(COLOR4);
	GUI_DrawArc(CIRCLE4_X, CIRCLE4_Y, CIRCLE_R, CIRCLE_R, 0, 360);
	
	GUI_SetColor(COLOR5);
	GUI_DrawArc(CIRCLE5_X, CIRCLE5_Y, CIRCLE_R, CIRCLE_R, 0, 360);
	
	GUI_SetTextAlign(GUI_TA_VCENTER);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(GUI_FONT_32B_1);
	
	GUI_SetColor(COLOR5);
	GUI_DispStringHCenterAt(NumberTextArray[mCountArray[0]], CIRCLE5_X, CIRCLE5_Y);
	
	GUI_SetColor(COLOR4);
	GUI_DispStringHCenterAt(NumberTextArray[mCountArray[1]], CIRCLE4_X, CIRCLE4_Y);
	
	GUI_SetColor(COLOR3);
	GUI_DispStringHCenterAt(NumberTextArray[mCountArray[2]], CIRCLE3_X, CIRCLE3_Y);
	
	GUI_SetColor(COLOR2);
	GUI_DispStringHCenterAt(NumberTextArray[mCountArray[3]], CIRCLE2_X, CIRCLE2_Y);
	
	GUI_SetColor(COLOR1);
	GUI_DispStringHCenterAt(NumberTextArray[mCountArray[4]], CIRCLE1_X, CIRCLE1_Y);
	
	uint16_t s = getAllCount();
	uint32_t priceAll = getAllPrice();
	if ((s > 5) || (s == 0)) 
	{
		drawForAndTo(0, 5, GUI_WHITE);
	}
	else
	{
		uint16_t index = 0;
		uint16_t to = 0;
		
		to += mCountArray[0];
		drawForAndTo(index, to, ColorArray[0]);
		
		index = to;
		to += mCountArray[1];
		drawForAndTo(index, to, ColorArray[1]);
		
		index = to;
		to += mCountArray[2];
		drawForAndTo(index, to, ColorArray[2]);
		
		index = to;
		to += mCountArray[3];
		drawForAndTo(index, to, ColorArray[3]);
		
		index = to;
		to += mCountArray[4];
		drawForAndTo(index, to, ColorArray[4]);
	}
	
	GUI_SetFont(GUI_FONT_32_1);
	GUI_SetColor(GUI_RED);
	GUI_FillRect(336, 248, 460, 300);
	GUI_SetColor(GUI_WHITE);
	sprintf(mTextBuffer, "$:%2d.%02d", priceAll / 100, priceAll % 100);
	GUI_DispStringHCenterAt(mTextBuffer, 398, 274);
}


uint32_t BackgroundWindow::getAllPrice(void)
{
	uint32_t price = 0;
	for (uint16_t i = 0; i < 5; i ++)
	{
		price += mCountArray[i] * WaresManager::instance().getPrice(i + 1);
	}
	return price;
}

void displayTrapezoid1(uint32_t color)
{
	GUI_SetColor(color);
	
	UiPolygon::instance()
		.begin()
		.append(TRAP1_LTX, TRAP1_LTY)
		.append(TRAP1_RTX, TRAP1_RTY)
		.append(TRAP1_RBX, TRAP1_RBY)
		.append(TRAP1_LBX, TRAP1_RBY)
		.fill(0, 0);
}

void displayTrapezoid2(uint32_t color)
{
	GUI_SetColor(color);

	UiPolygon::instance()
		.begin()
		.append(TRAP2_LTX, TRAP2_LTY)
		.append(TRAP2_RTX, TRAP2_RTY)
		.append(TRAP2_RBX, TRAP2_RBY)
		.append(TRAP2_LBX, TRAP2_RBY)
		.fill(0, 0);
}

void displayTrapezoid3(uint32_t color)
{
	GUI_SetColor(color);

	UiPolygon::instance()
		.begin()
		.append(TRAP3_LTX, TRAP3_LTY)
		.append(TRAP3_RTX, TRAP3_RTY)
		.append(TRAP3_RBX, TRAP3_RBY)
		.append(TRAP3_LBX, TRAP3_RBY)
		.fill(0, 0);	
}

void displayTrapezoid4(uint32_t color)
{
	GUI_SetColor(color);
	
	UiPolygon::instance()
		.begin()
		.append(TRAP4_LTX, TRAP4_LTY)
		.append(TRAP4_RTX, TRAP4_RTY)
		.append(TRAP4_RBX, TRAP4_RBY)
		.append(TRAP4_LBX, TRAP4_RBY)
		.fill(0, 0);	
}

void displayTrapezoid5(uint32_t color)
{
	GUI_SetColor(color);

	UiPolygon::instance()
		.begin()
		.append(TRAP5_LTX, TRAP5_LTY)
		.append(TRAP5_RTX, TRAP5_RTY)
		.append(TRAP5_RBX, TRAP5_RBY)
		.append(TRAP5_LBX, TRAP5_RBY)
		.fill(0, 0);	
}




