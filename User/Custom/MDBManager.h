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
		
		void payStart(uint32_t money); // 开始支付
		
		void payStop(void); // 停止支付
		
		void error(void); // 退款
		
		void success(void); // 成功
		
		void disableCoin(void);
		
		void enableCoin(void);
		
		void disablePaper(void);
		
		void enablePaper(void);
		
		void enableVpos(void);
		
		void disableVpos(void);

		void giveChange(uint32_t number5); // 找钱
		
		void gatherPaper(void); // 接收纸币
		
		void returnPaper(void); // 退还纸币
		
		void setPos(void); 
		
		bool isPaySuccess;
		bool isVposPay;
		bool isCashPay;
		uint32_t TotalMoney; // 需要支付的钱
		uint32_t MoneyAlready; // 已经支付的钱
		
	private:
		MDBManager(void);
};



#endif
