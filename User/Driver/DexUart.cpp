#include "Driver/DexUart.h"


static uint64_t RecvBuffer[512 / 8];
static uint64_t RecvSingleBuffer[64 / 8];

static DexEvent DexEnv;

// PA2 <=> USART2_TX
// PA3 <=> USART2_RX <=> DMA1_Stream5_Channel4
static void DriverInit(void)
{
	RCC->AHB1ENR |= 0x01;
	RCC->APB1ENR |= 0x20000;
	
	GPIOA->MODER &= ~0xF0;
	GPIOA->MODER |= 0xA0;
	GPIOA->PUPDR &= ~0xF0;
	GPIOA->PUPDR |= 0x50;
	GPIOA->OSPEEDR |= 0xF0;
	GPIOA->AFR[0] &= ~0xFF00;
	GPIOA->AFR[0] |= 0x7700;
	
	USART2->CR1 = 0x00;
	USART2->CR2 = 0x00;
	USART2->CR3 = 0x40;
	USART2->BRR = 42000000 / 9600;
	USART2->CR1 = 0x201C;
	
	RCC->AHB1ENR |= 0x200000;

	DMA1->HIFCR = 0x0FC0;
	DMA1_Stream5->CR = 0x00;
	DMA1_Stream5->M0AR = (uint32_t) &RecvBuffer;
	DMA1_Stream5->PAR = (uint32_t) &USART2->DR;
	DMA1_Stream5->NDTR = sizeof (RecvBuffer);
	DMA1_Stream5->CR = 	(0x04 << 25) |
						(0x00 << 23) |
						(0x00 << 21) |
						(0x00 << 19) |
						(0x00 << 18) |
						(0x02 << 16) |
						(0x00 << 15) |
						(0x00 << 13) |
						(0x00 << 11) |
						(0x01 << 10) |
						(0x00 << 9) |
						(0x01 << 8) |
						(0x00 << 6) |
						(0x00 << 5) |
						(0x01 << 0) ;
	NVIC_EnableIRQ(USART2_IRQn);
}

static void WriteByte(uint8_t byte)
{
	while (0 == (USART2->SR & 0x80));
	USART2->DR = byte;
}

DexUart::DexUart(void) :
	DexOutput(mOutputArray),
	Receiver("Dex", mMessageQueueBuffer, DEX_MSG_OBJ_COUNT, DEX_MSG_OBJ_SIZE)
{
	DriverInit();
}
	
void DexUart::write(const uint8_t *buffer, uint32_t size)
{
	while (size --)
	{
		WriteByte(*buffer ++);
	}
}

static inline void vBufferOver(uint32_t index, uint32_t lastIndex)
{
	uint32_t k = 0;
	uint8_t *p1 = (uint8_t *) RecvSingleBuffer;
	uint8_t *p2 = (uint8_t *) RecvBuffer;
	for (uint32_t i = lastIndex; i < sizeof (RecvBuffer); i ++, k ++) {
		p1[k] = p2[i];
	}
	for (uint32_t i = 0; i < index; i ++, k ++) {
		p1[k] = p2[i];
	}
	DexEnv.set(p1, k);
}

extern "C" void USART2_IRQHandler(void)
{
	static uint32_t lastIndex;
	uint32_t index;
	if (0 == (USART2->SR & 0x10)) {
		return ;
	}
	index = USART2->DR;
	index = sizeof(RecvBuffer) - DMA1_Stream5->NDTR;
	if (index > lastIndex) {
		DexEnv.set((uint8_t *) (RecvBuffer) + lastIndex, index - lastIndex);
	} else {
		vBufferOver(index, lastIndex);
	}
	DexUart::instance().put(&DexEnv);
	lastIndex = index;
}













