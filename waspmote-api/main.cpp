#include <Waspmote.h>
volatile unsigned long _serial_id;

int main(void)
{
	
	pinMode(HIB_PIN, OUTPUT);
	digitalWrite(HIB_PIN,HIGH);
	pinMode(RTC_SLEEP, OUTPUT);
	digitalWrite(RTC_SLEEP,HIGH);
	init();

	// get serial id
	_serial_id = Utils.readSerialID();
	
	setup();
    
	for (;;) {
		loop();

	}
        
	return 0;
}
