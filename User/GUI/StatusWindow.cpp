#include "GUI/StatusWindow.h"
#include "Task/GUITask.h"

#define ID_MAIN_WINDOW				(GUI_ID_USER + 0x765)

#define ID_CHECKBOX_1				(GUI_ID_USER + 0x766)
#define ID_CHECKBOX_2				(GUI_ID_USER + 0x767)
#define ID_CHECKBOX_3				(GUI_ID_USER + 0x768)
#define ID_CHECKBOX_4				(GUI_ID_USER + 0x769)
#define ID_CHECKBOX_5				(GUI_ID_USER + 0x76A)

#define ID_CHECKBOX_6				(GUI_ID_USER + 0x76B)
#define ID_CHECKBOX_7				(GUI_ID_USER + 0x76C)
#define ID_CHECKBOX_8				(GUI_ID_USER + 0x76D)
#define ID_CHECKBOX_9				(GUI_ID_USER + 0x76E)
#define ID_CHECKBOX_A				(GUI_ID_USER + 0x76F)

#define ID_CHECKBOX_B				(GUI_ID_USER + 0x770)
#define ID_CHECKBOX_C				(GUI_ID_USER + 0x771)
#define ID_CHECKBOX_D				(GUI_ID_USER + 0x772)
#define ID_CHECKBOX_E				(GUI_ID_USER + 0x773)
#define ID_CHECKBOX_F				(GUI_ID_USER + 0x774)


StatusWindow::StatusWindow(void)
{
	isShow = false;
}

bool StatusWindow::isShowing(void)
{
	return isShow;
}

void StatusWindow::onKeyClick(uint16_t keyValue)
{
	switch (keyValue)
	{
		case ID_KEY_VALUE_CAN:
			dismiss(); 
			break;
		
		case ID_MSG_STATUS_UPDATE:
			update();
			break;
	}
}

void StatusWindow::update(void)
{
	GUITask &manager = GUITask::instance();
	
	CHECKBOX_SetState(mCheckBoxPowerBox1, (unsigned int) manager.isPowerBox1Checked());
	CHECKBOX_SetState(mCheckBoxPowerBox2, (unsigned int) manager.isPowerBox2Checked());
	CHECKBOX_SetState(mCheckBoxPowerBox3, (unsigned int) manager.isPowerBox3Checked());
	CHECKBOX_SetState(mCheckBoxPowerBox4, (unsigned int) manager.isPowerBox4Checked());
	
	CHECKBOX_SetState(mCheckBoxDoor, (unsigned int) manager.isDoorCloseChecked());
	CHECKBOX_SetState(mCheckBoxRotationOpen, (unsigned int) manager.isRotationOpenChecked());
	CHECKBOX_SetState(mCheckBoxPushBack, (unsigned int) manager.isPushBackChecked());
	CHECKBOX_SetState(mCheckBoxPushFront, (unsigned int) manager.isPushFrontChecked());
	CHECKBOX_SetState(mCheckBoxPushCheck, (unsigned int) manager.isPushChecked());
	
	CHECKBOX_SetState(mCheckBoxDropOut, (unsigned int) manager.isDropOutChecked());
	CHECKBOX_SetState(mCheckBoxYAxisUp, (unsigned int) manager.isYAxisUpChecked());
	CHECKBOX_SetState(mCheckBoxYAxisDown, (unsigned int) manager.isYAxisDownChecked());
	CHECKBOX_SetState(mCheckBoxStepFault, (unsigned int) manager.isStepFault());
	
	CHECKBOX_SetState(mCheckBoxStepOrigin, (unsigned int) manager.isStepOriginChecked());
}

void StatusWindow::dismiss(void)
{
	isShow = false;
	WM_DeleteWindow(mWindow);
}

void StatusWindow::show(WM_HWIN parent)
{
	mWindow = WINDOW_CreateEx(0, 0, 480, 320, parent, WM_CF_SHOW, 0, ID_MAIN_WINDOW, NULL);
	
	mCheckBoxPowerBox1 = CHECKBOX_CreateEx(50, 40, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_1);
	CHECKBOX_SetFont(mCheckBoxPowerBox1, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxPowerBox1, "Box1");
	
	mCheckBoxPowerBox2 = CHECKBOX_CreateEx(50, 90, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_2);
	CHECKBOX_SetFont(mCheckBoxPowerBox2, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxPowerBox2, "Box2");
	
	mCheckBoxPowerBox3 = CHECKBOX_CreateEx(50, 140, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_3);
	CHECKBOX_SetFont(mCheckBoxPowerBox3, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxPowerBox3, "Box3");
	
	mCheckBoxPowerBox4 = CHECKBOX_CreateEx(50, 190, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_4);
	CHECKBOX_SetFont(mCheckBoxPowerBox4, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxPowerBox4, "Box4");
	
	mCheckBoxPowerBox5 = CHECKBOX_CreateEx(50, 240, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_5);
	CHECKBOX_SetFont(mCheckBoxPowerBox5, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxPowerBox5, "Box5");
	
	mCheckBoxDoor = CHECKBOX_CreateEx(200, 40, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_6);
	CHECKBOX_SetFont(mCheckBoxDoor, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxDoor, "Door");	
	
	mCheckBoxRotationOpen = CHECKBOX_CreateEx(200, 90, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_7);
	CHECKBOX_SetFont(mCheckBoxRotationOpen, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxRotationOpen, "Aggie");			
	
	mCheckBoxPushBack = CHECKBOX_CreateEx(200, 140, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_8);
	CHECKBOX_SetFont(mCheckBoxPushBack, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxPushBack, "PushBack");
	
	mCheckBoxPushFront = CHECKBOX_CreateEx(200, 190, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_9);
	CHECKBOX_SetFont(mCheckBoxPushFront, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxPushFront, "PushFront");	
	
	mCheckBoxPushCheck = CHECKBOX_CreateEx(200, 240, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_A);
	CHECKBOX_SetFont(mCheckBoxPushCheck, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxPushCheck, "PushCheck");
	
	mCheckBoxDropOut = CHECKBOX_CreateEx(330, 40, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_B);
	CHECKBOX_SetFont(mCheckBoxDropOut, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxDropOut, "DropOut");	
	
	mCheckBoxYAxisUp = CHECKBOX_CreateEx(330, 90, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_C);
	CHECKBOX_SetFont(mCheckBoxYAxisUp, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxYAxisUp, "YAxisUp");		
	
	mCheckBoxYAxisDown = CHECKBOX_CreateEx(330, 140, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_D);
	CHECKBOX_SetFont(mCheckBoxYAxisUp, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxYAxisUp, "YAxisUp");		
	
	mCheckBoxStepFault = CHECKBOX_CreateEx(330, 190, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_E);
	CHECKBOX_SetFont(mCheckBoxStepFault, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxStepFault, "StepFault");		
	
	mCheckBoxStepOrigin = CHECKBOX_CreateEx(330, 240, 100, 40, mWindow, WM_CF_SHOW, 0, ID_CHECKBOX_F);
	CHECKBOX_SetFont(mCheckBoxStepOrigin, GUI_FONT_16_ASCII);
	CHECKBOX_SetText(mCheckBoxStepOrigin, "Origin");		
}








