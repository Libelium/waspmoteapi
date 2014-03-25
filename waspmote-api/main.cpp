#include <Waspmote.h>
volatile unsigned long _serial_id;

int main(void)
{
	init();

	// proceed depending on the bootloader version
	if( Utils.getBootVersion() >= 'E')
	{
		pinMode(RTC_SLEEP, OUTPUT);
		digitalWrite(RTC_SLEEP, HIGH);
	}

	// get serial id
	_serial_id = Utils.readSerialID();
	
	setup();
    
	for (;;) {
		loop();

	}
        
	return 0;
}
