#ifndef		__WINDOW_MANAGER_H
#define		__WINDOW_MANAGER_H

#include "Window/BaseWindow.h"
#include "Task/GUITask.h"
#include <stdint.h>

class WindowManager
{
	public:
		static WindowManager &instance(void)
		{
			static WindowManager manager;
			return manager;
		}
	
	public:
		inline void setActive(BaseWindow *window) {
			pActiveWindow = window;
		}
		
		inline void clrActive(void) {
			pActiveWindow = nullptr;
		}
		
		bool onMessageReceiver(MessageId msgId);
	
	private:
		BaseWindow *pActiveWindow;
	
		WindowManager(void);
};

#endif
