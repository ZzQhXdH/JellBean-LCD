#include "Dex/DexFileBuilder.h"
#include <stdarg.h>

DexFileBuilder::DexFileBuilder(void)
{}

DexFileBuilder &DexFileBuilder::init(void)
{
	nIndex = 0;
	uint32_t ret = Dex::xDexFormat((char *) mBuffer + nIndex, "DXS", "ssss", "HOH1234567", "VA", "V0/6", "1");
	nIndex += ret;
	
	nStartIndex = nIndex; // ¿ªÊ¼¼ÆËãCRC
	ret = Dex::xDexFormat((char *) mBuffer + nIndex, "ST", "ss", "001", "0001");
	nIndex += ret;
	
	ret = Dex::xDexFormat((char *) mBuffer + nIndex, "ID1", "s0000s", "MCU", "112233");
	nIndex += ret;
	
	nPartCount = 2;
	
	return *this;
}

DexFileBuilder &DexFileBuilder::append(const char *header, const char *format, ...)
{
	va_list ap;
	uint32_t ret;
	char c;
	
	va_start(ap, format);
	
	ret = Dex::xStrCopy((char *) mBuffer + nIndex, header);
	nIndex += ret;
	
	while ((c = *format) != '\0')
	{
		mBuffer[nIndex ++] = '*';
		switch (c)
		{
			case 'd':
				ret = Dex::xStrValueOf((char *) mBuffer + nIndex, va_arg(ap, uint32_t));
				nIndex += ret;
				break;
			
			case 's':
				ret = Dex::xStrCopy((char *) mBuffer + nIndex, va_arg(ap, const char *));
				nIndex += ret;
				break;
			
			case 'x':
				ret = Dex::xStrHexOf((char *) mBuffer + nIndex, va_arg(ap, uint32_t));
				nIndex += ret;
				break;
		}
		format ++;
	}
	mBuffer[nIndex ++] = '\r';
	mBuffer[nIndex ++] = '\n';
	nPartCount ++;
	return *this;
}

void DexFileBuilder::build(void)
{
	uint32_t crc = Dex::xGetCRCValue(mBuffer + nStartIndex, nIndex - nStartIndex);
	append("G85", "x", crc);
	append("SE", "ds", nPartCount + 1, "0001");
	append("DXE", "ss", "1", "1");
}







