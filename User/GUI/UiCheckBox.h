#ifndef		__UI_CHECKBOX_H
#define		__UI_CHECKBOX_H

#include "GUI.h"
#include "Dialog.h"
#include <stdint.h>

class UiCheckBox
{
	public:
		UiCheckBox(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height);
		
		void show(WM_HWIN parent);
	
		void dismiss(void);
		
		void draw(void);
	
	private:
		WM_HWIN mWindow;
		uint16_t mX0;
		uint16_t mY0;
		uint16_t mWidth;
		uint16_t mHeight;
};




#endif
