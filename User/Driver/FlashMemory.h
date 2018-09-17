#ifndef		__FLASH_MEMORY_H
#define		__FLASH_MEMORY_H

#include "Event/Sender.h"
#include "stm32f4xx.h"
#include "Custom/BaseBuffer.h"

/**
 */
class FlashMemory : public BaseBuffer
{
	public:
		static FlashMemory &instance(void) 
		{
			static FlashMemory m;
			return m;
		}
		
		virtual void read(uint32_t address, uint8_t *data, uint32_t size);
		
		virtual void write(uint32_t address, const uint8_t *data, uint32_t size);
		
		virtual void earse(uint32_t address);
		
		uint16_t xGetId(void);
		
	private:
		FlashMemory(void);
	
		void initSpiInterface(void);
	
		uint8_t xTranslateByte(uint8_t byte);
	
		uint8_t xQueryStatus(void);
	
		void vWriteEnable(void);
	
		void vPageProgram(uint32_t address, const uint8_t *data, uint32_t size);
	
		inline void vCsLow(void) { GPIOB->BSRRH = 0x40;}
		
		inline void vCsHigh(void) { GPIOB->BSRRL = 0x40;}
		
	private:
		//uint32_t MemoryArrayMap[1024];
};





#endif
