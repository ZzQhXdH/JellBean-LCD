#include "Event/Timer.h"


void Timer::timerCallback(void *arg)
{
	((Timer *) arg)->onTimerEvent();
}

Timer::Timer(const char *name, osTimerType_t type)
{
	mAttr.name = name;
	mAttr.attr_bits = 0;
	mAttr.cb_mem = mCbMemory;
	mAttr.cb_size = osRtxTimerCbSize;
	mId = osTimerNew(timerCallback, type, this, &mAttr);
}



