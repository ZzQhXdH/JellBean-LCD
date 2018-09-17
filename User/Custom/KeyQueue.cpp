#include "Custom/KeyQueue.h"
#include "Driver/LogUart.h"

const uint16_t Password[] = {2, 5, 8, 3, 6, 9};

KeyQueue::KeyQueue(void)
{
}

bool KeyQueue::isChecked(void)
{
	for (uint16_t i = 0; i < 6; i ++) 
	{
		if (mKeyArray[i] != Password[i]) 
		{
			return false;
		}
	}
	return true;
}

void KeyQueue::push(uint16_t key)
{
	for (uint16_t i = 1; i < 6; i ++) { mKeyArray[i - 1] = mKeyArray[i];}
	mKeyArray[5] = key;
	if (isChecked()) 
	{
		pListener->onDisplayPasswordWindow();
	}
	
}








