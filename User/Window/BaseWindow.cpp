#include "Window/BaseWindow.h"
#include "Custom/WindowManager.h"

void BaseWindow::show(WM_HWIN hParentWindow)
{
	mActiveFlag = true;
	WindowManager::instance().setActive(this);
}

void BaseWindow::dismiss(void)
{
	mActiveFlag = false;
	WindowManager::instance().clrActive();
}

