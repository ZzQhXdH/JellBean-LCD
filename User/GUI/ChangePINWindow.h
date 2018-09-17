#ifndef		__CHANGE_PIN_WINDOW_H
#define		__CHANGE_PIN_WINDOW_H

#include "GUI/BaseWindow.h"
#include "GUI/UiStatus.h"

class ChangePINWindow : public BaseWindow
{
	public:
		static ChangePINWindow &instance(void)
		{
			static ChangePINWindow win;
			return win;
		}
		
		void show(WM_HWIN parent);
		
		void dismiss(void);
		
		void draw(void);
		
		void enter(void);
		
		virtual bool isShowing(void);
		
		virtual void onKeyClick(uint16_t keyValue);
		
	private:
		ChangePINWindow(void);
	
		void appendText(char c);
		
	private:
		WM_HWIN mWindow;
		EDIT_Handle mEditRawPIN;
		EDIT_Handle mEditNowPin;
		UiStatus hStatus;
		bool isShow;
		bool isEnter;
		char mTextBuffer[10];
		uint16_t nIndex;
};




#endif
