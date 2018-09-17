#ifndef		__KEY_EVENT_H
#define		__KEY_EVENT_H

#include <stdint.h>

enum KeyValue {
	
	Key1 = 0x37,
	Key2 = 0x34,
	Key3 = 0x31,
	Key4 = 0x38,
	Key5 = 0x35,
	Key6 = 0x32,
	Key7 = 0x39,
	Key8 = 0X36,
	Key9 = 0x33,
	KeyCan = 0x41,
	Key0 = 0x30,
	KeyEnt = 0x44,
	KeyKnown,
};

class KeyEvent
{
	public:
		KeyEvent(void);
	
		KeyEvent(KeyValue v);
		
		inline void setValue(KeyValue v) {
			mValue = v;
		}
		
		inline KeyValue value(void) {
			return mValue;
		}
		
		uint16_t valueInteger(void);
		
		bool isInteger(void);
	
	private:
		KeyValue mValue;
};





#endif
