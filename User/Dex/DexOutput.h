#ifndef		__DEX_OUT_PUT_H
#define		__DEX_OUT_PUT_H

#include <stdint.h>

class DexOutput
{
	public:
		DexOutput(uint8_t *buffer);
		
		inline DexOutput &start(void)
		{
			nIndex = 0;
			return *this;
		}
	
		DexOutput &operator <<(uint8_t byte);
	
		DexOutput &operator <<(const char *cString);
	
		DexOutput &append(const uint8_t *buffer, uint32_t length);
	
		DexOutput &append(uint8_t byte);
	
		DexOutput &append(const char *cString);
		
		void buildAndWrite(void);
	
		void buildAndCRCWrite(void);
	
		virtual void write(const uint8_t *buffer, uint32_t length) = 0;
	
	private:
		uint8_t *mOutputBuffer;
		uint32_t nIndex;
};




#endif
