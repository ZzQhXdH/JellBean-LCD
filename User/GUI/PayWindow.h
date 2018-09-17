#ifndef		__PAY_WINDOW_H
#define		__PAY_WINDOW_H

#include "GUI/BaseWindow.h"
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
	
		void show(WM_HWIN parent, uint32_t price);
	
		virtual void onKeyClick(uint16_t keyValue);
	
		virtual bool isShowing(void);
		
		virtual void onTimerEvent(void);
		
		void timeOut(void);
		
		void dismiss(void);
	
		void recv5c(void);
		void recv10c(void);
		void recv5s(void);
		void recv10s(void);
		void recv20s(void);
		void stat(void);
		void statOfVpos(void);
		
		bool isPaySuccess;
	
	private:
		WM_HWIN mWindow;
		TEXT_Handle mTextTitle;
		TEXT_Handle mTextMessage;
		TEXT_Handle mTextRefund;
		uint16_t mCounter5c;
		uint16_t mCounter10c;
		uint16_t mCounter5s;
		uint16_t mCounter10s;
		uint16_t mCounter20s;
		uint32_t mNeed;
		char mTextBuffer[20];
		bool isShow;
};



#endif
