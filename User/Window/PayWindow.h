#ifndef		__PAY_WINDOW_H
#define		__PAY_WINDOW_H

#include "Window/BaseWindow.h"
#include "Event/Timer.h"

class PayWindow : public BaseWindow, Timer
{
	public:
		PayWindow(void);
		
		static PayWindow &instance(void)
		{
			static PayWindow hWindow;
			return hWindow;
		}
	
		void showWithPrice(WM_HWIN parent, uint32_t price);
	
		virtual void onHandleMessage(MessageId msgId);
		
		virtual void onTimerEvent(void);
		
		virtual void dismiss(void);
		
	private:
			
		void onCashUpdate(void);
		
		void onVposUpdate(void);
	
	private:
		WM_HWIN mWindow;
		TEXT_Handle mTextTitle;
		TEXT_Handle mTextMessage;
		TEXT_Handle mTextRefund;
		char mTextBuffer[20];
};



#endif
