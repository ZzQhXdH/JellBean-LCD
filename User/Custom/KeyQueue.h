#ifndef		__KEY_QUEUE_H
#define		__KEY_QUEUE_H

#include <stdint.h>

class KeyListener
{
	public:
		virtual void onDisplayPasswordWindow(void) {}
};

class KeyQueue
{
	public:
		static KeyQueue &instance(void)
		{
			static KeyQueue queue;
			return queue;
		}
		
		void push(uint16_t key);
		
		inline void setListener(KeyListener *listener) { pListener = listener; }
	
	private:
		KeyQueue(void);
		bool isChecked(void);
	
	private:
		KeyListener *pListener;
		uint16_t mKeyArray[6];
};



#endif
