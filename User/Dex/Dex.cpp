#include "Dex/Dex.h"
#include <stdarg.h>

namespace Dex {
	
	const char __HEX_LIST[] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'A', 'B',
		'C', 'D', 'E', 'F',
	};
	
	uint32_t xStrValueOf(char *target, uint32_t value)
	{
		uint32_t length = 1;
		uint32_t tmp = value;

		while ((tmp /= 10) != 0)
		{
			length ++;
		}

		for (uint32_t i = 0; i < length; i ++)
		{
			target[length - i - 1] = '0' + (value % 10);
			value /= 10;
		}
		return length;
	}
	
	uint32_t xStrHexOf(char *target, uint32_t value)
	{
		uint32_t length = 1;
		uint32_t tmp = value;

		while ((tmp >>= 4) != 0)
		{
			length ++;
		}

		for (uint32_t i = 0; i < length; i ++)
		{
			target[length - i - 1] = __HEX_LIST[ value & 0x0F ];
			value >>= 4;
		}

		return length;
	}
	
	uint32_t xStrCopy(char *target, const char *source)
	{
		char c;
		uint32_t length = 0;
		while ((c = *source) != '\0')
		{
			*target = c;
			target ++;
			source ++;
			length ++;
		}
		return length;
	}
	
	uint32_t xDexFormat(char *buffer, const char *header, const char *format, ...)
	{
		char c;
		uint32_t ret = 0;
		uint32_t index = 0;
		va_list ap;
		va_start(ap, format);
		
		ret = xStrCopy(buffer + index, header);
		index += ret;
		
		while ((c = *format) != 0)
		{
			buffer[index ++] = '*';
			switch (c)
			{
				case 's':
					ret = xStrCopy(buffer + index, va_arg(ap, const char *));
					index += ret;
					break;
				
				case 'd':
					ret = xStrValueOf(buffer + index, va_arg(ap, uint32_t));
					index += ret;
					break;
				
				case 'x':
					ret = xStrHexOf(buffer + index, va_arg(ap, uint32_t));
					index += ret;
					break;
			}
			format ++;
		}
		
		buffer[index ++] = '\r';
		buffer[index ++] = '\n';
		return index;
	}
	
	void vCalcCRC(uint32_t *pCrc, uint8_t data)
	{
		for (uint32_t i = 0; i < 8; i ++, data >>= 1)
		{
			
			if ((data ^ *pCrc) & 0x01)
			{
				*pCrc >>= 1;
				*pCrc ^= 0xA001;
			}
			else
			{
				*pCrc >>= 1;
			}
		}
	}
	
	uint32_t xGetCRCValue(const uint8_t *buffer, uint32_t length)
	{
		uint32_t crc = 0x00;
		for (uint32_t i = 0; i < length; i ++)
		{
			vCalcCRC(&crc, buffer[i]);
		}
		return crc ;
	}
	
	uint32_t xGetCRCValueOfNotDLE(const uint8_t *buffer, uint32_t length)
	{
		uint32_t crc = 0x00;
		uint8_t v;
		for (uint32_t i = 0; i < length; i ++)
		{
			v = buffer[i];
			if (v == _DLE) {
				continue;
			}
			vCalcCRC(&crc, v);
		}
		return crc ;
	}
	
	void vBufferCopy(uint8_t *target, const uint8_t *source, uint32_t length)
	{
		for (uint32_t i = 0; i < length; i ++)
		{
			target[i] = source[i];
		}
	}
}

















