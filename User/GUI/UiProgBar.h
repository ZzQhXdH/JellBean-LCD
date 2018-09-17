#ifndef		__UI_PROGBAR_H
#define		__UI_PROGBAR_H

#include "GUI/BaseWindow.h"
#include "GUI/UiStatus.h"

class UiProgBarTimeOutListener
{
	public:
		virtual void onProgBarTimeOut(void) = 0;
};

class UiProgBar : public BaseWindow
{
	public:
		static UiProgBar &instance(void)
		{
			static UiProgBar progbar;
			return progbar;
		}
		
		void show(UiProgBarTimeOutListener *listen, uint16_t max);
		void dismiss(void);
		void draw(void);
		void update(void);
		void success(void);
		void error(void);
		virtual bool isShowing(void);
		
	private:
		UiProgBar(void);
		UiStatus hStatus;
		WM_HWIN mWindow;
		CHECKBOX_Handle mCheckBox;
		TEXT_Handle mText;
		WM_HWIN mProgBar;
		
		bool isShow;
		UiProgBarTimeOutListener *timeOutListen;
		char mTextBuffer[10];
};





#endif
