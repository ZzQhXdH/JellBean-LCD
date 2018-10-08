#ifndef		__KEY_QUEUE_H
#define		__KEY_QUEUE_H

#include <stdint.h>

class KeyQueue
{
	public:
		static KeyQueue &instance(void)
		{
			static KeyQueue queue;
			return queue;
		}
		
		void push(uint16_t key);
		
		bool pushAndCheck(uint16_t key);
		
	private:
		KeyQueue(void);
		bool isChecked(void);
	
	private:
		uint16_t mKeyArray[6];
};



#endif
