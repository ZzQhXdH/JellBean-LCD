#ifndef		__SYSTEM_CONFIG_WINDOW_H
#define		__SYSTEM_CONFIG_WINDOW_H

#include "Window/BaseWindow.h"

class SystemConfigWindow : public BaseWindow
{
	public:
		static SystemConfigWindow &instance(void)
		{
			static SystemConfigWindow win;
			return win;
		}
	
	private:
		SystemConfigWindow(void);
	
	public:
		virtual void show(WM_HWIN parent);
	
		virtual void dismiss(void);
		
		virtual void onHandleMessage(MessageId msgId);
		
		void unLock(void);
			
		void draw(void);
	
	private:
		WM_HWIN mWindow;
		BUTTON_Handle mButtonLock;
		BUTTON_Handle mButtonChangePIN;
		BUTTON_Handle mButtonReplenish;
		BUTTON_Handle mButtonChangePrice;
};




#endif
