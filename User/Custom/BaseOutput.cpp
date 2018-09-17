#include "Custom/BaseOutput.h"
#include <stdio.h>
#include <stdarg.h>

void BaseOutput::format(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int len = vsprintf((char *)pByteArrayBuffer, format, ap);
	va_end(ap);
	write(pByteArrayBuffer, len);
}

void BaseOutput::buildAndWrite(void)
{
	uint8_t *p = pByteArrayBuffer + nIndex + 5;
	uint16_t len = build(p);
	write(p, len);
}

uint16_t BaseOutput::build(uint8_t *content)
{
	content[0] = 0xE1;
	content[1] = nIndex + 5;
	content[2] = mAction;
	uint8_t c = 0;
	for (uint16_t i = 0; i < nIndex; i ++)
	{
		c ^= pByteArrayBuffer[i];
		content[3 + i] = pByteArrayBuffer[i];
	}
	content[nIndex + 3] = c;
	content[nIndex + 4] = 0xEF;
	return nIndex + 5;
}








