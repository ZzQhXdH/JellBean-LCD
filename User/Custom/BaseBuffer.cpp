#include "Custom/BaseBuffer.h"
/**
 * @FlashCheck "W25X128-"
 */


BaseBuffer::BaseBuffer(void)
{
	
}

BaseBuffer &BaseBuffer::setAddress(uint32_t address)
{
	return *this;
}

BaseBuffer &BaseBuffer::append(uint8_t byte)
{
	return *this;
}

BaseBuffer &BaseBuffer::append(const uint8_t *byteArray, uint32_t size)
{
	return *this;
}

BaseBuffer &BaseBuffer::writeByteArray(uint32_t address, const uint8_t *byteArray, uint32_t size)
{	
	uint32_t end;
	uint32_t alignSize;
	for (; ;)
	{
		end = IsAlign(address) ? (address + 0xFFF) : GetSectorMaxAddress(address);
		if ( (address + size - 1) > end ) { // 超越扇区边界
			alignSize = end - address + 1;
			writeInAlign(address, byteArray, alignSize);
			address += alignSize;
			byteArray += alignSize;
			size -= alignSize;
		} else {
			writeInAlign(address, byteArray, size);
			break;
		}
	}
	
	return *this;
}

BaseBuffer &BaseBuffer::readByteArray(uint32_t address, uint8_t *byteArray, uint32_t size)
{
	read(address, byteArray, size);
	return *this;
}

BaseBuffer &BaseBuffer::writeString(uint32_t address, const char *cString, uint32_t size)
{
	writeByteArray(address, (const uint8_t *) cString, size);
	return *this;
}

BaseBuffer &BaseBuffer::readString(uint32_t address, char *cString, uint32_t size)
{
	read(address, (uint8_t *) cString, size);
	return *this;
}

BaseBuffer &BaseBuffer::writeInt(uint32_t address, uint32_t value)
{
	writeByteArray(address, (const uint8_t *) &value, 4);
	return *this;	
}

BaseBuffer &BaseBuffer::readInt(uint32_t address, uint32_t *pvalue)
{
	read(address, (uint8_t *) pvalue, 4);
	return *this;
}

bool BaseBuffer::writeStringInCheck(uint32_t address, const char *cString, uint32_t size)
{
	return false;
}

void BaseBuffer::commit(void)
{
	
}

void BaseBuffer::writeInAlign(uint32_t address, const uint8_t *data, uint32_t size) // address + size 不能超过扇区的边界
{
	uint8_t *p = (uint8_t *) mAppendBuffer;
	//if (!isEarse(address, size))
	//{
		uint32_t offset = address - GetSectorMinAddress(address);
		read(GetSectorMinAddress(address), p, SECTOR_SIZE);
		copy(p + offset, data, size);
		earse(address);
		write(GetSectorMinAddress(address), p, SECTOR_SIZE);
		return;
	//}
	//write(address, data, size);
}

//bool BaseBuffer::isEarse(uint32_t address, uint32_t size)
//{
//	uint8_t *p = (uint8_t *) mEarseBuffer;
//	
//	read(address, p, size);
//	
//	for (uint32_t i = 0; i < size; i ++)
//	{
//		if (p[i] != 0xFF) {
//			return false;
//		}
//	}
//	return true;
//}

void BaseBuffer::copy(uint8_t *target, const uint8_t *sourece, uint32_t size)
{
	for (uint32_t i = 0; i < size; i ++)
	{
		target[i] = sourece[i];
	}
}

void BaseBuffer::copyXor(uint8_t *target, const uint8_t *source, uint32_t size)
{
	for (uint32_t i = 0; i < size; i ++)
	{
		target[i] = ~source[i];
	}
}

