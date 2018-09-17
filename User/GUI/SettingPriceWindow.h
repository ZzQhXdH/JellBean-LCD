#ifndef		__SETTING_PRICE_WINDOW_H
#define		__SETTING_PRICE_WINDOW_H

#include "GUI/BaseWindow.h"
#include "GUI/UiStatus.h"

class SettingPriceWindow : public BaseWindow
{
	public:
		static SettingPriceWindow &instance(void)
		{
			static SettingPriceWindow window;
			return window;
		}
		
		void show(WM_HWIN parent, uint32_t id);
		
		void draw(void);
		
		void dismiss(void);
		
		virtual void onKeyClick(uint16_t keyValue);
	
		virtual bool isShowing(void);
		
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
		bool isShow;
};






#endif
