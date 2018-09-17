#ifndef		__WARES_MANAGER_H
#define		__WARES_MANAGER_H

#include "Custom/WaresInfo.h"
#include "Driver/DeliverUart.h"
#include "Driver/FlashMemory.h"

#define WARES_FALSH_DATA_ADDRESS 			0x00

class WaresManager
{
	public:
		static WaresManager &instance(void)
		{
			static WaresManager man;
			return man;
		}
		
		inline uint32_t getPrice(uint32_t id) { return mInfoArray[id - 1].Price; }
		
		inline uint32_t getInventory(uint32_t id) { return mInfoArray[id - 1].Inventory; }
		
		inline void DeduInventory(uint32_t id, uint32_t number) { mInfoArray[id - 1].Inventory -= number; }
		
		inline void setPrice(uint32_t id, uint32_t price) { mInfoArray[id - 1].Price = price; save(); }
		
		inline char *getPassword(void) { return mPassword; }
		
		void setPassword(const char *password);
		
		bool isPasswordEquals(const char *password);
		
		bool isPasswordDefaultEquals(const char *password);
		
		inline void save(void) 
		{ 
			FlashMemory::instance().writeByteArray(WARES_FALSH_DATA_ADDRESS, (const uint8_t *) this, sizeof (WaresManager));
		}
		
		inline void load(void)
		{
			FlashMemory::instance().read(WARES_FALSH_DATA_ADDRESS, (uint8_t *) this, sizeof (WaresManager));
		}
		
	private:
		WaresInfo mInfoArray[5];
		char mPassword[10];
};



#endif
