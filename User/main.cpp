#include "stm32f4xx.h"
#include "Driver/LogUart.h"
#include "Task/Task.h"
#include "Driver/Lcd.h"
#include "Driver/KeyUart.h"
#include "Task/GUITask.h"
#include "Task/DeliverUartTask.h"
#include "Driver/DeliverUart.h"
#include "Driver/FlashMemory.h"
#include "Custom/WaresManager.h"
#include "Custom/MDBManager.h"


class KeyTask : public Task
{
	public:
		static KeyTask &instance(void) 
		{
			static KeyTask task;
			return task;
		}
		
	protected:
		virtual void run(void)
		{
			KeyUart &key = KeyUart::instance();
			DeliverUart &deliver = DeliverUart::instance();
			KeyEvent env;
			DeliverEvent env2;
			osStatus_t ste;
			while (true)
			{
				ste = key.recv(&env, 100); // 按键数据返回
				if (ste == osOK)
				{
					GUITask::instance().vKeyValueClick(env.value());
					GUITask::instance().vKeyClick(env.valueInteger());
				}
				
				ste = deliver.recv(&env2, 100); // 出货数据返回
				if ((ste == osOK) && env2.isCorrect())
				{
					GUITask::instance().vDeliverResult(env2);
				}
			}
		}
		
	private:
		KeyTask(void) : Task("Log", mKeyTaskStack, sizeof (mKeyTaskStack)) {}
			
	private:
		uint64_t mKeyTaskStack[512 / 8];		
};

class LogTask : public Task
{
	public:
		static LogTask &instance(void) 
		{
			static LogTask task;
			return task;
		}
		
	protected:
		virtual void run(void)
		{
			LogUart &log = LogUart::instance();
			LogEvent env;
			while (true)
			{
				log.recv(&env);
				env.exec();
			}
		}
		
	private:
		LogTask(void) : Task("Log", mLogTaskStack, sizeof (mLogTaskStack)) {}
			
	private:
		uint64_t mLogTaskStack[512 / 8];	
};

class StartTask : public Task
{
	public:
		static StartTask &instance(void) 
		{
			static StartTask task;
			return task;
		}
		
	protected:
		virtual void run(void)
		{
			vLcdInit();
			KeyUart::instance();
			LogUart::instance();
			DeliverUart::instance();
			FlashMemory::instance();
			WaresManager::instance().load();
			LogTask::instance().start();
			KeyTask::instance().start();
			GUITask::instance().start();
		}
		
	private:
		StartTask(void) : Task("Start", mStartTaskStack, sizeof (mStartTaskStack)) {}
			
	private:
		uint64_t mStartTaskStack[512 / 8];
};


int main(void)
{
	osKernelInitialize();
	StartTask::instance().start();
	osKernelStart();
}











