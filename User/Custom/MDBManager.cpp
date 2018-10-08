#include "MDBManager.h"


MDBManager::MDBManager(void)
{
	
}

// 检测到现金支付
void MDBManager::onCashChecked(uint32_t money)
{
	isCashPay =  true;
	MoneyAlready += money;
	if (isVposPay) // 如果先前VPOS已经支付过了
	{
		giveChange(MoneyAlready); // 把现金退回去
		isCashPay = false;
		MoneyAlready = 0;
		return;
	}
	if (MoneyAlready >= TotalMoney)
	{
		isPaySuccess = true;
		if (MoneyAlready > TotalMoney)
		{
			giveChange(MoneyAlready - TotalMoney);
		}
		
		LogUart::instance()
			.setAction(0x13)
			.append1(0x01) // 结束交易
			.buildAndWrite();
//		LogUart::instance()
//			.setAction(0x13)
//			.append1(0x04) // 结束会话
//			.buildAndWrite();
	}
}

// 检测到VPOS刷卡 <=> 收到0x05
void MDBManager::onVposChecked(void)
{
	isVposPay = true;
	isPaySuccess = true;
	if (isCashPay) // 如果先前已经付过现金了
	{
		giveChange(MoneyAlready); // 把之前的现金退掉
		isCashPay = false;
		MoneyAlready = 0;
		return;
	}
}

/**
 * @brief 支付开始
 */
void MDBManager::onPayStart(uint32_t money)
{
	MoneyAlready = 0;
	TotalMoney = money;
	LogUart::instance()
		.setAction(0xA1)
		.buildAndWrite(); // 启动收钱
	
	LogUart::instance()
		.setAction(0x13)
		.append1(0x00)
		.append1(money >> 8)
		.append1(money & 0xFF)
		.buildAndWrite(); // 设置VPOS收钱
	isPaySuccess = false; // 支付成功
	isVposPay = false; // 使用VPOS支付标志 
	isCashPay = false; // 使用现金支付标志
}

/**
 * @brief 支付结束
 */
void MDBManager::onPayStop(void)
{
	LogUart::instance()
		.setAction(0xA2)
		.buildAndWrite(); // 停止收钱
	if ((!isPaySuccess) && (MoneyAlready > 0)) // 如果支付失败就退钱
	{
		giveChange(MoneyAlready);
	}
	
	if (!isVposPay)
	{
		LogUart::instance().setAction(0x13).append1(0x01).buildAndWrite();
		LogUart::instance().setAction(0x13).append1(0x04).buildAndWrite();
	}
}

/**
 * @brief 出货成功
 */
void MDBManager::onSuccess(void)
{
	if (isVposPay) // 使用VPOS收钱
	{
		LogUart::instance()
			.setAction(0x13)
			.append1(0x02)
			.buildAndWrite(); // 出货成功开始扣款
		
		LogUart::instance()
		.setAction(0x13)
		.append1(0x04) 
		.buildAndWrite(); // 会话完成
	}
	isVposPay = false;
	isCashPay = false;	
}

/**
 * @brief 出货失败
 */
void MDBManager::onError(void)
{
	if (isVposPay) // 如果是VPOS支付
	{
		LogUart::instance()
			.setAction(0x13)
			.append1(0x03) // 出货失败 取消扣款
			.buildAndWrite();
		LogUart::instance()
			.setAction(0x13)
			.append1(0x04) // 结束会话
			.buildAndWrite();
	}
	
	if (isCashPay) // 如果是现金支付
	{
		giveChange(MoneyAlready);
	}
	
	isVposPay = false;
	isCashPay = false;
}





