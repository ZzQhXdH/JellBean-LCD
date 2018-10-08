#ifndef		__STATUS_WINDOW_H
#define		__STATUS_WINDOW_H


#include "Window/BaseWindow.h"

class StatusWindow : public BaseWindow
{
	public:
		static StatusWindow &instance(void)
		{
			static StatusWindow INSTANCE;
			return INSTANCE;
		}
		
		virtual void show(WM_HWIN parent);
		
		virtual void onHandleMessage(MessageId msgId);
		
		virtual void dismiss(void);
		
		void update(void);
	
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
};




#endif
