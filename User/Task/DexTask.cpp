#include "Task/DexTask.h"
#include "Driver/DexUart.h"


DexTask::DexTask(void) : Task("Dex", mStack, sizeof (mStack))
{
	
}

void DexTask::run(void)
{
	DexUart &uart = DexUart::instance();
	DexEvent env;
	
	while (true)
	{
		uart.recv(&env);
		env.exec();
	}
}
















