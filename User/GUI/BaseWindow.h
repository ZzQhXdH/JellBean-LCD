#ifndef		__BASE_WINDOW_H
#define		__BASE_WINDOW_H

#include "GUI.h"
#include "Dialog.h"
#include <stdint.h>

class BaseWindow
{
	public:
		virtual void onKeyClick(uint16_t keyValue);
	
		virtual bool isShowing(void);
};




#endif
