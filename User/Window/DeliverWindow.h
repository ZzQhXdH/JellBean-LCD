#ifndef		__UI_PROGBAR_H
#define		__UI_PROGBAR_H

#include "Window/BaseWindow.h"
#include "Widget/UiStatus.h"
#include "Event/Timer.h"

class DeliverWindow : public BaseWindow, public Timer
{
	public:
		static DeliverWindow &instance(void)
		{
			static DeliverWindow w;
			return w;
		}
		
		void showWithTimeOut(WM_HWIN hParent, uint32_t timeOut);
		virtual void onHandleMessage(MessageId msgId);
		virtual void dismiss(void);
		virtual void onTimerEvent(void);
	
		void update(void);
		void success(void);
		void error(void);
		
	private:
		DeliverWindow(void);
	
		UiStatus hStatus;
		WM_HWIN mWindow;
		CHECKBOX_Handle mCheckBox;
		TEXT_Handle mText;
		WM_HWIN mProgBar;
		char mTextBuffer[10];
};





#endif
