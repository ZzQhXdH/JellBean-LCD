#include "Event/KeyEvent.h"


KeyEvent::KeyEvent(void) : mValue(KeyKnown) {}

KeyEvent::KeyEvent(KeyValue v) : mValue(v) {}

uint16_t KeyEvent::valueInteger(void)
{
	switch (mValue)
	{
		case Key0: return 0;
		case Key1: return 1;
		case Key2: return 2;
		case Key3: return 3;
		case Key4: return 4;
		case Key5: return 5;
		case Key6: return 6;
		case Key7: return 7;
		case Key8: return 8;
		case Key9: return 9;
	}
	return 0xFFFF;
}

bool KeyEvent::isInteger(void)
{
	return (mValue >= Key0) && (mValue <= Key7);
}






