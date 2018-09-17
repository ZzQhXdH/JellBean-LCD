#ifndef		__DELIVER_UART_TASK_H
#define		__DELIVER_UART_TASK_H


#include "Task/Task.h"
#include "Event/DeliverEvent.h"

class DeliverUartTask : public Task
{
	public:
		inline static DeliverUartTask &instance(void) {
			static DeliverUartTask task;
			return task;
		}
	
	private:
		virtual void run(void);
		
	private:
		DeliverUartTask(void);
	
	private:
		uint64_t mStack[ 512 / 8 ];
};






#endif
