#ifndef		__DEX_DEX_FILE_BUILDER_H
#define		__DEX_DEX_FILE_BUILDER_H

#include "Dex/Dex.h"

#define PART_MAX			200

class DexFileBuilder
{
	public:
		static DexFileBuilder &instance(void)
		{
			static DexFileBuilder builder;
			return builder;
		}
	
		DexFileBuilder &init(void);
	
		void build(void);
		
		DexFileBuilder &append(const char *header, const char *format, ...);
		
		const uint8_t *blocks(void) {
			return mBuffer;
		}
		
		inline uint32_t size(void) {
			return nIndex;
		}
	
	private:
		DexFileBuilder(void);
	
	private:
		uint8_t mBuffer[1024];
		uint32_t nIndex;
		uint32_t nPartCount; 
		uint32_t nStartIndex; // Start CRC
};





#endif
