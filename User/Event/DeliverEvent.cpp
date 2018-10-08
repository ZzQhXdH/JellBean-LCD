#include "Event/DeliverEvent.h"
#include "Task/GUITask.h"
#include "Custom/FaultManager.h"


void DeliverEvent::exec(void)
{
	if (!isCorrect()) {
		return;
	}
	
	switch (type())
	{
		case 0x8A:
			FaultManager::instance().update(arg(1), arg(2), arg(3));
			GUITask::instance().sendMessage(MSG_STATUS_UPDATE);
			break;
		
		case 0x89:
			{
				MessageId msgId = ((arg(1) == 0x00) ? MSG_DELIVER_SUCCESS : MSG_DELIVER_ERROR);
				GUITask::instance().sendMessage(msgId);
			}
			break;
	}
}






