#ifndef		__PASS_WORD_WINDOW_H
#define		__PASS_WORD_WINDOW_H

#include "GUI/BaseWindow.h"

class PasswordWindow : public BaseWindow
{
	public:
		static PasswordWindow &instance(void)
		{
			static PasswordWindow win;
			return win;
		}
		
		void show(void);
		
		void dismiss(void);
		
		void dismissAtOnce(void);
		
		void append(char c); 
		
		void clear(void);
		
		bool isChecked(void);
		
		void draw(void);
		
		virtual void onKeyClick(uint16_t keyValue);
		
		virtual bool isShowing(void);
		
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
