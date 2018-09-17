#include "Driver/KeyUart.h"

static KeyEvent KeyEnv;

/**
 * @brief PC10 <-> UART4_TX, PC11 <-> UART4_RX
 * AF8
 */
KeyUart::KeyUart(void) : Receiver("Key", KeyMessageQueueMem, KEY_OBJ_COUNT, KEY_OBJ_SIZE)
{
	RCC->AHB1ENR |= 0x04;
	
	GPIOC->MODER &= ~0xF00000;
	GPIOC->MODER |= 0xA00000;
	GPIOC->OSPEEDR |= 0xF00000;
	GPIOC->PUPDR &= ~0xF00000;
	GPIOC->PUPDR |= 0x500000;
	GPIOC->OTYPER &= ~0xC00;
	GPIOC->AFR[1] &= ~0xFF00;
	GPIOC->AFR[1] |= 0x8800;
	
	RCC->APB1ENR |= 0x80000;
	
	UART4->CR1 = 0x00;
	UART4->CR2 = 0x00;
	UART4->CR3 = 0x00;
	UART4->BRR = 42000000 / 115200;
	UART4->CR1 = 0x202C;
	
	NVIC_EnableIRQ(UART4_IRQn);
}

extern "C" void UART4_IRQHandler(void)
{
	if (UART4->SR & 0x20) 
	{
		KeyEnv.setValue((KeyValue) UART4->DR);
		KeyUart::instance().put(&KeyEnv);
	}
}










