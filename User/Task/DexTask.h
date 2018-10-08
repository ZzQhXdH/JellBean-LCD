#ifndef		__DEX_TASK_H
#define		__DEX_TASK_H

#include "Task/Task.h"

class DexTask : public Task
{
	public:
		static DexTask &instance(void)
		{
			static DexTask task;
			return task;
		}
		
	public:
		virtual void run(void);
		
	private:
		DexTask(void);
		
	private:
		uint64_t mStack[1024 / 8];
};







#endif
