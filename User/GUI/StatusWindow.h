#ifndef		__STATUS_WINDOW_H
#define		__STATUS_WINDOW_H


#include "GUI/BaseWindow.h"

class StatusWindow : public BaseWindow
{
	public:
		static StatusWindow &instance(void)
		{
			static StatusWindow INSTANCE;
			return INSTANCE;
		}
		
		void show(WM_HWIN parent);
		
		virtual void onKeyClick(uint16_t keyValue);
	
		virtual bool isShowing(void);
		
		void update(void);
		
		void dismiss(void);
		
	private:
		StatusWindow(void);
		
	private:
		WM_HWIN mWindow;
	
		CHECKBOX_Handle mCheckBoxPowerBox1;
		CHECKBOX_Handle mCheckBoxPowerBox2;
		CHECKBOX_Handle mCheckBoxPowerBox3;
		CHECKBOX_Handle mCheckBoxPowerBox4;
		CHECKBOX_Handle mCheckBoxPowerBox5;
	
		CHECKBOX_Handle mCheckBoxDoor;
		CHECKBOX_Handle mCheckBoxRotationOpen;
		CHECKBOX_Handle mCheckBoxPushBack;
		CHECKBOX_Handle mCheckBoxPushFront;
		CHECKBOX_Handle mCheckBoxPushCheck;
		CHECKBOX_Handle mCheckBoxDropOut;
		
		CHECKBOX_Handle mCheckBoxYAxisUp;
		CHECKBOX_Handle mCheckBoxYAxisDown;
		CHECKBOX_Handle mCheckBoxStepFault;
		CHECKBOX_Handle mCheckBoxStepOrigin;
		
		bool isShow;
};




#endif
