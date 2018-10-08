#ifndef		__SETTING_PRICE_WINDOW_H
#define		__SETTING_PRICE_WINDOW_H

#include "Window/BaseWindow.h"
#include "Widget/UiStatus.h"

class SettingPriceWindow : public BaseWindow
{
	public:
		static SettingPriceWindow &instance(void)
		{
			static SettingPriceWindow window;
			return window;
		}
		
		void showWithId(WM_HWIN parent, uint32_t id);
		
		virtual void dismiss(void);
		
		virtual void onHandleMessage(MessageId msgId);
		
		void draw(void);
	
	private:
		SettingPriceWindow(void);
		void appendText(char c);
		void savePrice(void);
	
		WM_HWIN mWindow;
		UiStatus hStatus;
		EDIT_Handle mEditOriginal;
		EDIT_Handle mEditNow;
		TEXT_Handle mTextMessage;
		char mTextBuffer[10];
		uint32_t nInputIndex;
		uint32_t mId;
};






#endif
