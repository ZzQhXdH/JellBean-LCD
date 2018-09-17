#ifndef		__SYSTEM_CONFIG_WINDOW_H
#define		__SYSTEM_CONFIG_WINDOW_H

#include "GUI/BaseWindow.h"

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
		void show(void);
	
		void dismiss(void);
		
		void unLock(void);
			
		void draw(void);
		
		virtual bool isShowing(void);
		virtual void onKeyClick(uint16_t keyValue);
		
	private:
		WM_HWIN mWindow;
		BUTTON_Handle mButtonLock;
		BUTTON_Handle mButtonChangePIN;
		BUTTON_Handle mButtonReplenish;
		BUTTON_Handle mButtonChangePrice;
		bool isShow;
};




#endif
