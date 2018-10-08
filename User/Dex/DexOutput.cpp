#include "Dex/DexOutput.h"
#include "Dex/Dex.h"

DexOutput::DexOutput(uint8_t *buffer) : mOutputBuffer(buffer), nIndex(0)
{
}

		
DexOutput &DexOutput::operator <<(uint8_t byte)
{
	mOutputBuffer[nIndex ++] = byte;
	return *this;
}
	
DexOutput &DexOutput::operator <<(const char *cString)
{
	uint32_t ret = Dex::xStrCopy((char *) mOutputBuffer + nIndex, cString);
	nIndex += ret;
	return *this;
}
	
DexOutput &DexOutput::append(const uint8_t *buffer, uint32_t length)
{
	Dex::vBufferCopy(mOutputBuffer + nIndex, buffer, length);
	nIndex += length;
	return *this;
}
	
DexOutput &DexOutput::append(uint8_t byte)
{
	mOutputBuffer[nIndex ++] = byte;
	return *this;
}
	
DexOutput &DexOutput::append(const char *cString)
{
	uint32_t ret = Dex::xStrCopy((char *) mOutputBuffer + nIndex, cString);
	nIndex += ret;
	return *this;	
}

void DexOutput::buildAndWrite(void)
{
	write(mOutputBuffer, nIndex);
}

void DexOutput::buildAndCRCWrite(void)
{
	uint32_t crc = Dex::xGetCRCValueOfNotDLE(mOutputBuffer + 2, nIndex - 2);
	append(crc & 0xFF);
	append(crc >> 8);
	write(mOutputBuffer, nIndex);
}


