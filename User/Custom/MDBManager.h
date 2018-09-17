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
		
		void payStart(uint32_t money); // ��ʼ֧��
		
		void payStop(void); // ֹ֧ͣ��
		
		void error(void); // �˿�
		
		void success(void); // �ɹ�
		
		void disableCoin(void);
		
		void enableCoin(void);
		
		void disablePaper(void);
		
		void enablePaper(void);
		
		void enableVpos(void);
		
		void disableVpos(void);

		void giveChange(uint32_t number5); // ��Ǯ
		
		void gatherPaper(void); // ����ֽ��
		
		void returnPaper(void); // �˻�ֽ��
		
		void setPos(void); 
		
		bool isPaySuccess;
		bool isVposPay;
		bool isCashPay;
		uint32_t TotalMoney; // ��Ҫ֧����Ǯ
		uint32_t MoneyAlready; // �Ѿ�֧����Ǯ
		
	private:
		MDBManager(void);
};



#endif