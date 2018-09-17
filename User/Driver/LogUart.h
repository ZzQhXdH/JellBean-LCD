#ifndef		__LOG_UART_H
#define		__LOG_UART_H

#include "stm32f4xx.h"
#include "Event/Sender.h"
#include "Event/Receiver.h"
#include "Event/LogEvent.h"
#include "Custom/BaseOutput.h"


#define LOG_UART_OBJ_SIZE			sizeof (LogEvent)
#define LOG_UART_OBJ_NUMBER			20
#define LOG_UART_SIZE				osRtxMessageQueueMemSize(LOG_UART_OBJ_NUMBER, LOG_UART_OBJ_SIZE)

class LogUart : public Sender, public Receiver, public BaseOutput
{
	public:
		static LogUart &instance(void) 
		{
			static LogUart uart;
			return uart;
		}
		
		virtual void write(const uint8_t *byteArray, uint16_t length);
		
	private:
		LogUart(void);
		void write(uint8_t byte);
		
	private:
		uint64_t qMqMem[ (LOG_UART_SIZE + 7) / 8 ];
		uint8_t mByteArrayBuffer[50];
};



#endif
