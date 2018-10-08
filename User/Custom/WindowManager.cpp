#include "Custom/WindowManager.h"

bool WindowManager::onMessageReceiver(MessageId msgId)
{
	if (pActiveWindow == nullptr) {
		return false;
	}
	pActiveWindow->onHandleMessage(msgId);
	return true;
}

WindowManager::WindowManager(void)
{
	pActiveWindow = nullptr;
}




