#include "MDBManager.h"


MDBManager::MDBManager(void)
{
	
}

void MDBManager::disableCoin(void) // 失能硬币器
{
	LogUart::instance().setAction(0x01).buildAndWrite();
}

void MDBManager::enableCoin(void) // 使能硬币器
{
	LogUart::instance().setAction(0x02).buildAndWrite();
}

void MDBManager::disablePaper(void) // 失能纸币器
{
	LogUart::instance().setAction(0x03).buildAndWrite();
}

void MDBManager::enablePaper(void) // 使能纸币器
{
	LogUart::instance().setAction(0x04).buildAndWrite();
}

void MDBManager::giveChange(uint32_t number5)
{
	LogUart::instance().setAction(0x07).append1(number5).buildAndWrite();
}

void MDBManager::gatherPaper(void)
{
	LogUart::instance().setAction(0x08).buildAndWrite();
}

void MDBManager::returnPaper(void)
{
	LogUart::instance().setAction(0x09).buildAndWrite();
}

void MDBManager::enableVpos(void)
{
	LogUart::instance().setAction(0x14).append1(0x01).buildAndWrite();
}

void MDBManager::disableVpos(void)
{
	LogUart::instance().setAction(0x14).append1(0x00).buildAndWrite();
}

void MDBManager::setPos() // 1分钱的个数
{
	isVposPay = true;
	uint32_t number = TotalMoney / 10;
	LogUart::instance().setAction(0x13)
			.append1(0x00)
			.append1(number >> 8)
			.append1(number & 0xFF)
			.buildAndWrite();
	
	if (isCashPay) // 在刷卡之前如果已经投过钱,则退钱
	{
		giveChange(MoneyAlready / 50);
		MoneyAlready = 0;
		isCashPay = false;
	}
}

void MDBManager::payStart(uint32_t money)
{
	MoneyAlready = 0;
	TotalMoney = money;
	enableCoin();
	enablePaper();
	isPaySuccess = false;
}

void MDBManager::payStop(void)
{
	disableCoin();
	disablePaper();
	if (!isPaySuccess)
	{
		giveChange(MoneyAlready / 50);
	}
}

void MDBManager::success(void)
{
	if (isVposPay)
	{
		LogUart::instance()
			.setAction(0x13)
			.append1(0x02)
			.buildAndWrite();
		
		LogUart::instance()
		.setAction(0x13)
		.append1(0x04)
		.buildAndWrite();
	}
	isVposPay = false;
	isCashPay = false;
	MoneyAlready = 0;
}	

void MDBManager::error(void)
{
	if (isVposPay) 
	{
		LogUart::instance()
			.setAction(0x13)
			.append1(0x03)
			.buildAndWrite();
		osDelay(10);
		LogUart::instance()
			.setAction(0x13)
			.append1(0x04)
			.buildAndWrite();
	}
	
	if (isCashPay)
	{
		LogUart::instance()
			.setAction(0x07)
			.append1(TotalMoney / 50)
			.buildAndWrite();
	}
	
	isCashPay = false;
	isVposPay = false;
}





