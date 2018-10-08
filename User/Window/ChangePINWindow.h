#ifndef		__CHANGE_PIN_WINDOW_H
#define		__CHANGE_PIN_WINDOW_H

#include "Window/BaseWindow.h"
#include "Widget/UiStatus.h"

class ChangePINWindow : public BaseWindow
{
	public:
		static ChangePINWindow &instance(void)
		{
			static ChangePINWindow win;
			return win;
		}
		
		virtual void show(WM_HWIN parent);
		
		virtual void dismiss(void);
		
		virtual void onHandleMessage(MessageId msgId);
		
		void draw(void);
		
		void enter(void);
		
	private:
		ChangePINWindow(void);
	
		void appendText(char c);
		
	private:
		WM_HWIN mWindow;
		EDIT_Handle mEditRawPIN;
		EDIT_Handle mEditNowPin;
		UiStatus hStatus;
		bool isEnter;
		char mTextBuffer[10];
		uint16_t nIndex;
};




#endif
