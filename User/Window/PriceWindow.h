#ifndef		__PRICE_WINDOW_H
#define		__PRICE_WINDOW_H

#include "Window/BaseWindow.h"

class PriceWindow : public BaseWindow
{
	public:
		static PriceWindow &instance(void)
		{
			static PriceWindow win;
			return win;
		}
		
		virtual void show(WM_HWIN parent);
		
		virtual void dismiss(void);
		
		virtual void onHandleMessage(MessageId msgId);
		
		void notifyUpdate(void);
		
		void draw(void);
		
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
