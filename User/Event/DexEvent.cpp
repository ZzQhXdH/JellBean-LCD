#include "Event/DexEvent.h"
#include "Dex/DexFileBuilder.h"
#include "Custom/WaresManager.h"
//#include "Driver/LogUart.h"
#include "Driver/DexUart.h"
#include "Custom/FaultManager.h"

static uint32_t nHandShake;
static uint32_t nAlreadyWriteBytes;

DexEvent::DexEvent(void)
{
}

void DexEvent::exec(void)
{	
//	LogUart::instance().format("recv-%d\r\n", nSize);
	if (isENQ()) // VPOS发起通信请求
	{
//		LogUart::instance().format("onENQ\r\n");
		
		WaresManager &manager = WaresManager::instance();
		FaultManager &fault = FaultManager::instance();
		DexFileBuilder &builder = DexFileBuilder::instance();
		
		builder.init()
			.append("PA1", "sd0000d", "W1", manager.getPrice(1), 1)
			.append("PA2", "d00000000000", manager.getSalesVolume(1))
			.append("PA1", "sd0000d", "W2", manager.getPrice(2), 1)
			.append("PA2", "d00000000000", manager.getSalesVolume(2))
			.append("PA1", "sd0000d", "W3", manager.getPrice(3), 1)
			.append("PA2", "d00000000000", manager.getSalesVolume(3))
			.append("PA1", "sd0000d", "W4", manager.getPrice(4), 1)
			.append("PA2", "d00000000000", manager.getSalesVolume(4))
			.append("PA1", "sd0000d", "W5", manager.getPrice(5), 1)
			.append("PA2", "d00000000000", manager.getSalesVolume(5))
			.append("EA2", "s000d0", "DoorClose", fault.isDoorCloseChecked())
			.append("EA2", "s000d0", "PowerBox1", fault.isPowerBox1Checked())
			.append("EA2", "s000d0", "PowerBox2", fault.isPowerBox2Checked())
			.append("EA2", "s000d0", "PowerBox3", fault.isPowerBox3Checked())
			.append("EA2", "s000d0", "PowerBox4", fault.isPowerBox4Checked())
			.append("EA2", "s000d0", "PowerBox5", fault.isPowerBox5Checked())
			.append("EA2", "s000d0", "RotationDoorOpen", fault.isRotationOpenChecked())
			.append("EA2", "s000d0", "StepMotorFault", fault.isStepFault())
			.append("EA2", "s000d0", "StepOrigin", fault.isStepOriginChecked())
			.build();
		
		DexUart::instance()
		.start()
		.append(_DLE).append('0').buildAndWrite();
		
		nHandShake = 1;
		nAlreadyWriteBytes = 0;
		return;
	}
	switch (nHandShake)
	{
		case 1: onHandleHandShake1(); break;
		case 2: onHandleHandShake2(); break;
		case 3: onHandleHandShake3(); break;
	}
	
}

void DexEvent::onHandleHandShake1(void)
{
	if (isDLE_SOH())
	{
		DexUart::instance()
			.start()
			.append(_DLE)
			.append('1')
			.buildAndWrite();
		
//		LogUart::instance().format("h1--DLE_SOH\r\n");
		return;
	}
	
	if (isEOT())
	{
		DexUart::instance()
			.start()
			.append(_ENQ)
			.buildAndWrite();
//		LogUart::instance().format("h1--EOT\r\n");
		nHandShake = 2;
		return;
	}
}

void DexEvent::onHandleHandShake2(void)
{
	if (isDLE0())
	{
		DexUart::instance().start()
			.append(_DLE)
			.append(_SOH)
			.append("00")
			.append("HOH1234567")
			.append("R01L01")
			.append(_DLE)
			.append(_ETX)
			.buildAndCRCWrite();
	//	LogUart::instance().format("h2-DLE0\r\n");
		return;
	}
	
	if (isDLE1()) 
	{
		nHandShake = 3;
		DexUart::instance().start()
			.append(_EOT)
			.buildAndWrite();
		osDelay(10);
		DexUart::instance().start()
			.append(_ENQ)
			.buildAndWrite();
	//	LogUart::instance().format("h2-DEL1\r\n");
	}
	
}

void DexEvent::onHandleHandShake3(void)
{
	DexFileBuilder &builder = DexFileBuilder::instance();
	uint32_t len = builder.size();
	uint32_t blockSize ;
	//LogUart::instance().format("%d,%d\r\n", nAlreadyWriteBytes, len);
	if (isDLE0() || isDLE1())
	{
		uint8_t e;
		
		if (nAlreadyWriteBytes >= len)
		{
			DexUart::instance().start()
				.append(_EOT)
				.buildAndWrite();
//			LogUart::instance().format("end\r\n");
			return;
		}
		
		if ((nAlreadyWriteBytes + 220) <= len) {
			blockSize = 220;
			e = _ETB;
		} else {
			blockSize = len - nAlreadyWriteBytes;
			e = _ETX;
		}
		
		DexUart::instance().start()
			.append(_DLE)
			.append(_STX)
			.append(builder.blocks() + nAlreadyWriteBytes, blockSize)
			.append(_DLE)
			.append(e)
			.buildAndCRCWrite();
		
		nAlreadyWriteBytes += blockSize;
			
		return;
	}
}












