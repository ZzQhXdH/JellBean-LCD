#include "Task/DeliverUartTask.h"
#include "Driver/DeliverUart.h"


DeliverUartTask::DeliverUartTask(void) : Task("DeliverUart", mStack, sizeof (mStack))
{}

void DeliverUartTask::run(void)
{
	DeliverUart &uart = DeliverUart::instance();
	DeliverEvent env;
	while (true)
	{
		uart.recv(&env);
		//uart.write(env);
	}
}		






