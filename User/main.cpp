#include "Task/BootMainTask.h"


int main(void)
{
	osKernelInitialize();
	BootMainTask::instance().start();
	osKernelStart();
}

