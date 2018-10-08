#ifndef		__UI_STATUS_H
#define		__UI_STATUS_H

#include "GUI.h"
#include "Dialog.h"
#include <stdint.h>

class UiStatus
{
	public:
		enum Status {
			Error = 0x00,
			Ok = 0x01,
			Gone = 0x02,
		};
	
	public:
		UiStatus(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height);
		
		void show(WM_HWIN parent);
	
		void dismiss(void);
	
		void draw(void);
	
		void setStatus(Status s);
	
	private:
		uint16_t mX0;
		uint16_t mY0;
		uint16_t mWidth;
		uint16_t mHeight;
		uint16_t mDiameter;
		WM_HWIN mWindow;
		Status mStatus;
};



#endif
