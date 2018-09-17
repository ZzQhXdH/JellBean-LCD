#ifndef		__KEY_UART_H
#define		__KEY_UART_H

#include "stm32f4xx.h"
#include "Event/Receiver.h"
#include "Event/KeyEvent.h"

#define KEY_OBJ_SIZE		sizeof (KeyEvent)
#define KEY_OBJ_COUNT		100
#define KEY_SIZE			osRtxMessageQueueMemSize(KEY_OBJ_COUNT, KEY_OBJ_SIZE)

class KeyUart : public Receiver
{
	public:
		static inline KeyUart &instance(void) {
			static KeyUart k;
			return k;
		}
		
	private:
		KeyUart(void);
	
	private:
		uint64_t KeyMessageQueueMem[ (KEY_SIZE + 7) / 8 ];
};





#endif
