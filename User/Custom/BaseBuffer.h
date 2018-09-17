#ifndef		__BASE_BUFFER_H
#define		__BASE_BUFFER_H

#include <stdint.h>

#define SECTOR_SIZE						0x1000 
#define GetSectorMinAddress(a)			( a & (~0xFFF))			
#define GetSectorMaxAddress(a)			( (( a + 0xFFF ) & (~0xFFF)) - 1 )
#define IsAlign(a)						( (a & 0xFFF) == 0x00 )

class BaseBuffer
{
	public:
		BaseBuffer(void);
	
		BaseBuffer &setAddress(uint32_t address); 
	
		BaseBuffer &append(uint8_t byte);
		
		BaseBuffer &append(const uint8_t *byteArray, uint32_t size);
		
		BaseBuffer &writeString(uint32_t address, const char *cString, uint32_t size);
	
		BaseBuffer &readString(uint32_t address, char *cString, uint32_t size);
	
		BaseBuffer &writeByteArray(uint32_t address, const uint8_t *byteArray, uint32_t size);
	
		BaseBuffer &readByteArray(uint32_t address, uint8_t *byteArray, uint32_t size);
	
		BaseBuffer &writeInt(uint32_t address, uint32_t value);
		
		BaseBuffer &readInt(uint32_t address, uint32_t *pvalue);
	
		bool writeStringInCheck(uint32_t address, const char *cString, uint32_t size);
	
		void commit(void);
	
	protected:
		virtual void write(uint32_t address, const uint8_t *buffer, uint32_t size) = 0;
	
		virtual void read(uint32_t address, uint8_t *buffer, uint32_t size) = 0;
		
		virtual void earse(uint32_t address) = 0;
	
	private:
		uint32_t mFlashTargetAddress;
		uint32_t mBufferTargetAddress;
		uint64_t mAppendBuffer[ 4096 / 8 ];
		uint64_t mArrayBuffer[ 4096 / 8 ];
		//uint64_t mEarseBuffer[ 4096 / 8 ];
		
		void writeInAlign(uint32_t address, const uint8_t *data, uint32_t size); 
	
		void copy(uint8_t *target, const uint8_t *sourece, uint32_t size);
	
		void copyXor(uint8_t *target, const uint8_t *source, uint32_t size);
};





#endif
