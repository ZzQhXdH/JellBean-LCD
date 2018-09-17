#ifndef		__PRICE_WINDOW_H
#define		__PRICE_WINDOW_H

#include "GUI/BaseWindow.h"

class PriceWindow : public BaseWindow
{
	public:
		static PriceWindow &instance(void)
		{
			static PriceWindow win;
			return win;
		}
		
		void show(WM_HWIN parent);
		
		void dismiss(void);
		
		void draw(void);
		
		virtual void onKeyClick(uint16_t keyValue);
	
		virtual bool isShowing(void);
		
	private:
		WM_HWIN mWindow;
		EDIT_Handle mEditPrice1;
		EDIT_Handle mEditPrice2;
		EDIT_Handle mEditPrice3;
		EDIT_Handle mEditPrice4;
		EDIT_Handle mEditPrice5;
		bool isShow;
		char mTextBuffer[10];
	
	private:
		PriceWindow(void);
	
		void setState(uint32_t id);
};




#endif
