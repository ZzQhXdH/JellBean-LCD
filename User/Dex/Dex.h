#ifndef		__DEX_DEX_H
#define		__DEX_DEX_H

#include <stdint.h>

#define _SOH 	0x01
#define _STX 	0x02
#define _ETX 	0x03
#define _EOT 	0x04
#define _ENQ 	0x05
#define _LF  	0x0A
#define _CR  	0x0D
#define _DLE 	0x10
#define _NAK 	0x15
#define _SYN 	0x16
#define _ETB 	0x17

namespace Dex {
	
	uint32_t xStrValueOf(char *target, uint32_t value);
	
	uint32_t xStrHexOf(char *target, uint32_t value);
	
	uint32_t xStrCopy(char *target, const char *source);
	
	void vBufferCopy(uint8_t *target, const uint8_t *source, uint32_t length);
	
	uint32_t xDexFormat(char *buffer, const char *header, const char *format, ...);
	
	void vCalcCRC(uint32_t *pCrc, uint8_t data);
	
	uint32_t xGetCRCValue(const uint8_t *buffer, uint32_t length);
	
	uint32_t xGetCRCValueOfNotDLE(const uint8_t *buffer, uint32_t length);
};

#endif
