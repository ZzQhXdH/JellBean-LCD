#ifndef		__BOOT_MAIN_TASK_H
#define		__BOOT_MAIN_TASK_H

#include "Task/Task.h"


class BootMainTask : public Task
{
	public:
		static BootMainTask &instance(void)
		{
			static BootMainTask task;
			return task;
		}
		
	protected:
		virtual void run(void);
		
	private:
		BootMainTask(void);
	
	private:
		uint64_t mStack[2048 / 8];
};



#endif
