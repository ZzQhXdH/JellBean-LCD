#include "Driver/Lcd.h"
#include <rtx_os.h>

#define BASE_ADDR				0x60000000
#define vWrite(a, v)			*((volatile uint16_t *)(BASE_ADDR + a)) = v
#define vWriteCommand(x)		vWrite(0x00, x)
#define vWriteData(x)			vWrite(0x20000, x)
#define xReadData()				*((volatile uint16_t *)(BASE_ADDR + 0x20000))

static void vInitDriver(void);
static void vInitGpio(void);
static void vLcdOpenWindow(uint16_t x0, uint16_t y0, uint16_t xSize, uint16_t ySize);
static void LcdReset(void);

void vLcdDrawRect(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, uint16_t color)
{
	uint32_t i = width * height;
	vLcdOpenWindow(x0, y0, width, height);
	for (; i --; ) {
		vWriteData(color);
	}
}

void vLcdDrawRectColor(uint16_t x0, uint16_t y0, uint16_t width, uint16_t height, const uint16_t *pColor)
{
	uint32_t i = width * height;
	vLcdOpenWindow(x0, y0, width, height);
	for (; i --; ) {
		vWriteData(*pColor ++);
	}	
}

void vLcdClear(uint16_t color)
{
	vLcdOpenWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
	for (uint32_t i = 0; i < LCD_PIXELS; i ++) {
		vWriteData(color);
	}
}

uint16_t xLcdGetPixel(uint16_t x0, uint16_t y0)
{
	uint16_t ret = 0;
	
	vWriteCommand(0x4F);
	vWriteData(x0);
	vWriteCommand(0x4E);
	vWriteData(y0);
	vWriteCommand(0x22);
	ret = xReadData();
	return ret;
}

void vLcdDrawPixel(uint16_t x0, uint16_t y0, uint16_t color)
{
	vWriteCommand(0x2A);
	vWriteData(x0 >> 8);
	vWriteData(x0 & 0xFF);
	vWriteData(x0 >> 8);
	vWriteData(x0 & 0xFF);
	
	vWriteCommand(0x2B);
	vWriteData(y0 >> 8);
	vWriteData(y0 & 0xFF);
	vWriteData(y0 >> 8);
	vWriteData(y0 & 0xFF);
	
	vWriteCommand(0x2C);
	
	vWriteData(color);
}

void vLcdInit(void)
{
	vInitGpio();
	RCC->AHB1ENR |= 0x1000;
	RCC->AHB3ENR |= 0x01;
	FSMC_Bank1->BTCR[0] = 0x5010;
	FSMC_Bank1->BTCR[1] = (2 << 8) + 5 + (0 << 28);
	FSMC_Bank1E->BWTR[0] = (2 << 8) + 5 + (0 << 28);
	FSMC_Bank1->BTCR[0] = 0x5011;
	
	// RESET <-> PD3
	RCC->AHB1ENR |= 0x08;
	GPIOD->MODER &= ~0xC0;
	GPIOD->MODER |= 0x40;
	GPIOD->OTYPER &= ~0x08;
	GPIOD->PUPDR &= ~0xC0;
	GPIOD->PUPDR |= 0x40;
	GPIOD->OSPEEDR |= 0xC0;
	LcdReset();
	vInitDriver();	
}


static void LcdReset(void)
{
	GPIOD->BSRRH = 0x08;
	osDelay(100);
	GPIOD->BSRRL = 0x08;
	osDelay(100);
}

/**
 * @FsmcPin
 * D0 <-> PD14,  D1 <-> PD15,  D2 <-> PD0,   D3 <-> PD1
 * D4 <-> PE7,   D5 <-> PE8,   D6 <-> PE9,   D7 <-> PE10
 * D8 <-> PE11,  D9 <-> PE12,  D10 <-> PE13, D11 <-> PE14
 * D12 <-> PE15, D13 <-> PD8,  D14 <-> PD9,  D15 <-> PD10
 * A16 <-> PD11, NOE <-> PD4, NWE <-> PD5, NE1 <-> PD7
 * PD - 0, 1, 4, 5, 7, 8, 9, 10, 11, 14, 15
 * PE - 7, 8, 9, 10, 11, 12, 13, 14, 15
 **/
static void vInitGpio(void)
{
	RCC->AHB1ENR |= 0x08 + 0x10;
	
	GPIOD->MODER &= ~0xF0FFCF0F;
	GPIOD->MODER |= 0xA0AA8A0A;
	GPIOD->PUPDR &= ~0xF0FFCF0F;
	GPIOD->PUPDR |= 0x50554505;
	GPIOD->OSPEEDR |= 0xF0FFCF0F;
	GPIOD->OTYPER &= ~0xCFB3;
	GPIOD->AFR[0] &= ~0xF0FF00FF;
	GPIOD->AFR[0] |= 0xC0CC00CC;
	GPIOD->AFR[1] &= ~0xFF00FFFF;
	GPIOD->AFR[1] |= 0xCC00CCCC;
	
	GPIOE->MODER &= ~0xFFFFC000;
	GPIOE->MODER |= 0xAAAA8000;
	GPIOE->PUPDR &= ~0xFFFFC000;
	GPIOE->PUPDR |= 0x55554000;
	GPIOE->OSPEEDR |= 0xFFFFC000;
	GPIOE->OTYPER &= ~0xFF80;
	GPIOE->AFR[0] &= ~0xF0000000;
	GPIOE->AFR[0] |= 0xC0000000;
	GPIOE->AFR[1] = 0xCCCCCCCC;	
}

static void vInitDriver(void)
{
	vWriteCommand(0xB0);
	vWriteData(0x04);
	 
	vWriteCommand(0x36);    
	vWriteData(0x08);    
	 
	vWriteCommand(0x3A);    
	vWriteData(0x55);   
	 
	vWriteCommand(0xB4);    
	vWriteData(0x00); 
	 
	vWriteCommand(0xC0);
	vWriteData(0x03);//0013
	vWriteData(0xDF);//480
	vWriteData(0x40);
	vWriteData(0x12);
	vWriteData(0x00);
	vWriteData(0x01);
	vWriteData(0x00);
	vWriteData(0x43);

	vWriteCommand(0xC1);//frame frequency
	vWriteData(0x05);//BCn,DIVn[1:0
	vWriteData(0x2f);//RTNn[4:0] 
	vWriteData(0x08);// BPn[7:0]
	vWriteData(0x08);// FPn[7:0]
	vWriteData(0x00);
	 
	vWriteCommand(0xC4);
	vWriteData(0x63);
	vWriteData(0x00);
	vWriteData(0x08);
	vWriteData(0x08);
	 
	vWriteCommand(0xC8);//Gamma
	vWriteData(0x06);
	vWriteData(0x0c);
	vWriteData(0x16);
	vWriteData(0x24);//26
	vWriteData(0x30);//32 
	vWriteData(0x48);
	vWriteData(0x3d);
	vWriteData(0x28);
	vWriteData(0x20);
	vWriteData(0x14);
	vWriteData(0x0c);
	vWriteData(0x04);
	 
	vWriteData(0x06);
	vWriteData(0x0c);
	vWriteData(0x16);
	vWriteData(0x24);
	vWriteData(0x30);
	vWriteData(0x48);
	vWriteData(0x3d);
	vWriteData(0x28);
	vWriteData(0x20);
	vWriteData(0x14);
	vWriteData(0x0c);
	vWriteData(0x04);
	 
	vWriteCommand(0xC9);//Gamma
	vWriteData(0x06);
	vWriteData(0x0c);
	vWriteData(0x16);
	vWriteData(0x24);//26
	vWriteData(0x30);//32 
	vWriteData(0x48);
	vWriteData(0x3d);
	vWriteData(0x28);
	vWriteData(0x20);
	vWriteData(0x14);
	vWriteData(0x0c);
	vWriteData(0x04);
	 
	vWriteData(0x06);
	vWriteData(0x0c);
	vWriteData(0x16);
	vWriteData(0x24);
	vWriteData(0x30);
	vWriteData(0x48);
	vWriteData(0x3d);
	vWriteData(0x28);
	vWriteData(0x20);
	vWriteData(0x14);
	vWriteData(0x0c);
	vWriteData(0x04);
	 
	vWriteCommand(0xCA);//Gamma
	vWriteData(0x06);
	vWriteData(0x0c);
	vWriteData(0x16);
	vWriteData(0x24);//26
	vWriteData(0x30);//32 
	vWriteData(0x48);
	vWriteData(0x3d);
	vWriteData(0x28);
	vWriteData(0x20);
	vWriteData(0x14);
	vWriteData(0x0c);
	vWriteData(0x04);
	 
	vWriteData(0x06);
	vWriteData(0x0c);
	vWriteData(0x16);
	vWriteData(0x24);
	vWriteData(0x30);
	vWriteData(0x48);
	vWriteData(0x3d);
	vWriteData(0x28);
	vWriteData(0x20);
	vWriteData(0x14);
	vWriteData(0x0c);
	vWriteData(0x04);
	 
	vWriteCommand(0xD0);
	vWriteData(0x95);
	vWriteData(0x06);
	vWriteData(0x08);
	vWriteData(0x10);
	vWriteData(0x3f);
	 
	vWriteCommand(0xD1);
	vWriteData(0x02);
	vWriteData(0x28);
	vWriteData(0x28);
	vWriteData(0x40);
	 
	vWriteCommand(0xE1);    
	vWriteData(0x00);    
	vWriteData(0x00);    
	vWriteData(0x00);    
	vWriteData(0x00);    
	vWriteData(0x00);   
	vWriteData(0x00);   
	 
	vWriteCommand(0xE2);    
	vWriteData(0x80);    
	 
	vWriteCommand(0x2A);    
	vWriteData(0x00);    
	vWriteData(0x00);    
	vWriteData(0x01);    
	vWriteData(0x3F);    
	 
	vWriteCommand(0x2B);    
	vWriteData(0x00);    
	vWriteData(0x00);    
	vWriteData(0x01);    
	vWriteData(0xDF);    
	 
	vWriteCommand(0x11);
	 
	osDelay(120);
	 
	vWriteCommand(0x29);
	 
	vWriteCommand(0xC1);//frame frequency
	vWriteData(0x05);//BCn,DIVn[1:0
	vWriteData(0x2f);//RTNn[4:0] 
	vWriteData(0x08);// BPn[7:0]
	vWriteData(0x08);// FPn[7:0]
	vWriteData(0x00);

	vWriteCommand(0x20);
	
	vWriteCommand(0x36);
	vWriteData(0x60);
}

static void vLcdOpenWindow(uint16_t x0, uint16_t y0, uint16_t xSize, uint16_t ySize)
{
	vWriteCommand(0x2A);
	vWriteData(x0 >> 8);
	vWriteData(x0 & 0xFF);
	vWriteData((x0 + xSize - 1) >> 8);
	vWriteData((x0 + xSize - 1) & 0xFF);
	
	vWriteCommand(0x2B);
	vWriteData(y0 >> 8);
	vWriteData(y0 & 0xFF);
	vWriteData((y0 + ySize - 1) >> 8);
	vWriteData((y0 + ySize - 1) & 0xFF);
	
	vWriteCommand(0x2C);
}

