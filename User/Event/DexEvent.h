#ifndef		__DEX_EVENT_H
#define		__DEX_EVENT_H

#include "Dex/Dex.h"

class DexEvent
{
	public:
		DexEvent(void);
	
		inline void set(uint8_t *buffer, uint32_t size) {
			mInputBuffer = buffer;
			nSize = size;
		}
		
		void exec(void);
	
	private:
		
		void onHandleHandShake1(void);
		void onHandleHandShake2(void);
		void onHandleHandShake3(void);
	
		inline bool isENQ(void) { return mInputBuffer[0] == _ENQ; }
		
		inline bool isDLE_SOH(void) 
		{ 
			return (mInputBuffer[0] == _DLE) &&
				   (mInputBuffer[1] == _SOH);
		}
		
		inline bool isEOT(void) { return mInputBuffer[0] == _EOT; }
		
		inline bool isDLE0(void) 
		{ 
			return  (nSize == 2) &&
					(mInputBuffer[0] == _DLE) &&
					(mInputBuffer[1] == '0');
		}
		
		inline bool isDLE1(void) 
		{
			return 	(nSize == 2) &&
					(mInputBuffer[0] == _DLE) &&
					(mInputBuffer[1] == '1');
		}
		
	private:
		uint8_t *mInputBuffer;
		uint32_t nSize;
};



#endif
