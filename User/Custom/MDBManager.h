#ifndef		__MDB_MANAGER_H
#define		__MDB_MANAGER_H

#include "Driver/LogUart.h"

class MDBManager
{
	public:
		enum MoneyType {
			Paper20 = 0x01,
			Paper10 = 0x02,
			Paper5 = 0x03,
			Paper1 = 0x04,
			Coin1 = 0x05,
			Coin05 = 0x06,
		};
	
	public:
		static MDBManager &instance(void)
		{
			static MDBManager INSTANCE;
			return INSTANCE;
		}
		
		void onPayStart(uint32_t money); // 开始支付
		
		void onPayStop(void); // 停止支付
		
		void onError(void); // 出货失败 
		
		void onSuccess(void); // 出货成功 
		
		void onVposChecked(void); // 收到VPOS请求
		
		void onCashChecked(uint32_t money); // 收到现金支付请求
		
		inline uint32_t getAlreadyMoney(void) { return MoneyAlready; }
		
		inline bool isPaySuccessing() { return isPaySuccess; }
		
		inline void giveChange(uint32_t number) // 退钱 1分钱的个数
		{
			LogUart::instance()
				.setAction(0x07)
				.append1(number / 50)
				.buildAndWrite();
		}
		
	private:
		bool isPaySuccess;
		bool isVposPay;
		bool isCashPay;
		uint32_t TotalMoney; // 需要支付的钱
		uint32_t MoneyAlready; // 已经支付的钱
		
	private:
		MDBManager(void);
};



#endif
