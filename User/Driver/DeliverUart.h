#ifndef		__DELIVER_UART_H
#define		__DELIVER_UART_H

#include "stm32f4xx.h"
#include "Event/Sender.h"
#include "Event/Receiver.h"
#include "Event/DeliverEvent.h"
#include "Custom/BaseOutput.h"

#define DELIVER_OBJ_NUMBER		100
#define DELIVER_OBJ_SIZE		sizeof (DeliverEvent)
#define DELIVER_SIZE			osRtxMessageQueueMemSize( DELIVER_OBJ_NUMBER, DELIVER_OBJ_SIZE )

class DeliverUart : public Sender, public Receiver, public BaseOutput
{
	public:
		static DeliverUart &instance(void) 
		{
			static DeliverUart uart;
			return uart;
		}
		
		virtual void write(const uint8_t *byteArray, uint16_t size);
		
	private:
		DeliverUart(void);
		void write(uint8_t byte);
	
	private:
		uint64_t mMqMem[ (DELIVER_SIZE + 7) / 8 ];
		uint8_t mBufferMemory[100];
};




#endif
