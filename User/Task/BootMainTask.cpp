#include "Task/BootMainTask.h"
#include "Driver/LogUart.h"
#include "Driver/Lcd.h"
#include "Driver/KeyUart.h"
#include "Driver/DeliverUart.h"
#include "Driver/FlashMemory.h"
#include "Custom/WaresManager.h"
#include "Task/DexTask.h"
#include "Task/GUITask.h"
#include "Driver/DexUart.h"

BootMainTask::BootMainTask(void) : Task("Boot", mStack, sizeof (mStack))
{
	
}


void BootMainTask::run(void)
{
	vLcdInit();
	KeyUart::instance();
	LogUart::instance();
	DeliverUart::instance();
	FlashMemory::instance();
	DexUart::instance();
	WaresManager::instance().load(); // 加载商品数据
	
	DexTask::instance().start();
	GUITask::instance().start(); // 启动GUI线程
	
	LogEvent logEnv;
	DeliverEvent deliverEnv;
	KeyEvent keyEnv;
	
	osStatus_t ret;
	
	while (true)
	{
		ret = LogUart::instance().recv(&logEnv, 10);
		if (ret == osOK) {
			logEnv.exec();
		}
		
		ret = DeliverUart::instance().recv(&deliverEnv, 10);
		if (ret == osOK) {
			deliverEnv.exec();
		}
		
		ret = KeyUart::instance().recv(&keyEnv, 10);
		if (ret == osOK) {
			keyEnv.exec();
		}
	}
}



