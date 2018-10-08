#ifndef		__PASS_WORD_WINDOW_H
#define		__PASS_WORD_WINDOW_H

#include "Window/BaseWindow.h"

class PasswordWindow : public BaseWindow
{
	public:
		static PasswordWindow &instance(void)
		{
			static PasswordWindow win;
			return win;
		}
		
		virtual void show(WM_HWIN hWindow);
		
		virtual void dismiss(void);
		
		virtual void onHandleMessage(MessageId msgId);
		
		void draw(void);
		
	private:
		
		void append(char c); 
		
		void clear(void);
		
		bool isChecked(void);
		
	private:
		PasswordWindow(void);
		
	private:
		GUI_HWIN mWindow;
		EDIT_Handle mEdit;
		bool isShow;
		char mText[10];
		int mTextLength;
};


#endif
