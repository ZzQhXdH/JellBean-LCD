#include "Driver/Lcd.h"
#include "GUI.h"
#include "GUI_Private.h"
#include "GUIDRV_Lin.h"

extern const GUI_DEVICE_API GUIDRV_Template_API;

/**
 * Left_Top (310, 320)
 * Right Bottom (3710, 3640)
 */

void LCD_X_Config(void) 
{
	// Set display driver and color conversion for 1st layer
	//
	GUI_DEVICE_CreateAndLink(&GUIDRV_Template_API, GUICC_565, 0, 0);
	
	//
	// Set size of 1st layer
	//
	LCD_SetSizeEx (0, LCD_WIDTH, LCD_HEIGHT);
	LCD_SetVSizeEx(0, LCD_WIDTH, LCD_HEIGHT);
	
	//GUI_TOUCH_SetOrientation(GUI_MIRROR_X); 
	//GUI_TOUCH_Calibrate(GUI_COORD_X, 0, LCD_WIDTH - 1, 310, 3710);
	//GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, LCD_HEIGHT - 1, 320, 3640);
}

/*
*********************************************************************************************************
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*********************************************************************************************************
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) 
{
	return 0;
}

void GUI_TOUCH_X_ActivateX(void)
{}

void GUI_TOUCH_X_ActivateY(void)
{}

int GUI_TOUCH_X_MeasureX(void)
{
	return 0;
}

int GUI_TOUCH_X_MeasureY(void)
{
	return 0;
}



