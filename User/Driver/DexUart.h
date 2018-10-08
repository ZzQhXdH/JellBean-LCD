#ifndef		__DEX_UART_H
#define		__DEX_UART_H

#include "stm32f4xx.h"
#include "Event/Receiver.h"
#include "Dex/DexOutput.h"
#include "Event/DexEvent.h"

#define DEX_MSG_OBJ_SIZE		sizeof (DexEvent)
#define DEX_MSG_OBJ_COUNT		10
#define DEX_MSG_SIZE			osRtxMessageQueueMemSize( DEX_MSG_OBJ_COUNT, DEX_MSG_OBJ_SIZE )

class DexUart : public DexOutput, public Receiver
{
	public:
		static DexUart &instance(void)
		{
			static DexUart uart;
			return uart;
		}
	
		virtual void write(const uint8_t *buffer, uint32_t length);
		
	private:
		DexUart(void);
		
	private:
		uint8_t mOutputArray[1024];
		uint64_t mMessageQueueBuffer[(DEX_MSG_SIZE + 7) / 8];
};


#endif
