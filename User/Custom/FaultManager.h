#ifndef		__FAULT_MANAGER_H
#define		__FAULT_MANAGER_H

#include "stm32f4xx.h"

#define FAULT_DATA_FLASH_ADDRESS			0x100

class FaultManager
{
	public:
		static FaultManager &instance(void)
		{
			static FaultManager manager;
			return manager;
		}
		
		void update(uint8_t d1, uint8_t d2, uint8_t d3)
		{
			mStatusByte1 = d1;
			mStatusByte2 = d2;
			mStatusByte3 = d3;
		}
		
		inline bool isPowerBox1Checked(void) {
			return (mStatusByte1 & 0x01) != 0x00;
		}
		
		inline bool isPowerBox2Checked(void) {
			return (mStatusByte1 & 0x02) != 0x00;
		}
		
		inline bool isPowerBox3Checked(void) {
			return (mStatusByte1 & 0x04) != 0x00;
		}
		
		inline bool isPowerBox4Checked(void) {
			return (mStatusByte1 & 0x08) != 0x00;
		}
		
		inline bool isPowerBox5Checked(void) {
			return (mStatusByte1 & 0x10) != 0x00;
		}
		
		inline bool isDoorCloseChecked(void) {
			return (mStatusByte2 & 0x01) != 0x00;
		}
		
		inline bool isRotationOpenChecked(void) {
			return (mStatusByte2 & 0x02) != 0x00;
		}
		
		inline bool isPushBackChecked(void) {
			return (mStatusByte2 & 0x04) != 0x00;
		}
		
		inline bool isPushFrontChecked(void) {
			return (mStatusByte2 & 0x08) != 0x00;
		}
		
		inline bool isPushChecked(void) {
			return (mStatusByte2 & 0x10) != 0x00;
		}
		
		inline bool isDropOutChecked(void) {
			return (mStatusByte2 & 0x20) != 0x00;
		}
		
		inline bool isYAxisUpChecked(void) {
			return (mStatusByte3 & 0x01) != 0x00;
		}
		
		inline bool isYAxisDownChecked(void) {
			return (mStatusByte3 & 0x02) != 0x00;
		}
		
		inline bool isStepFault(void) {
			return (mStatusByte3 & 0x04) != 0x00;
		}
		
		inline bool isStepOriginChecked(void) {
			return (mStatusByte3 & 0x08) != 0x00;
		}
		
		
	private:
		FaultManager();
	
		uint8_t mStatusByte1, mStatusByte2, mStatusByte3;
};





#endif
