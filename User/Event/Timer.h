#ifndef		__TIMER_H
#define		__TIMER_H

#include <rtx_os.h>
#include <stdint.h>

class Timer
{
	public:
		Timer(const char *name, osTimerType_t type);
		
		inline void startTimer(uint32_t tick) {
			osTimerStart(mId, tick);
		}
		
		inline void stopTimer(void) {
			osTimerStop(mId);
		}
	
	protected:
		static void timerCallback(void *arg);
		virtual void onTimerEvent(void) = 0;

	private:
		uint64_t mCbMemory[ (osRtxTimerCbSize + 7) / 8];
		osTimerAttr_t mAttr;
		osTimerId_t mId;
};




#endif
