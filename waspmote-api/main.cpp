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
	
	// Check OTA EEPROM flag and mark flag in Waspmote 
	// Control Register if corresponds to
	if( Utils.readEEPROM(0x01) == 0x01 )
	{
		// set register flag
		WaspRegister |= REG_OTA;
		
		// clear eeprom flag
		eeprom_write_byte((unsigned char *) 0x01, 0x00);
	}

	// get serial id
	_serial_id = Utils.readSerialID();
	
	setup();
    
	for (;;) {
		loop();

	}
        
	return 0;
}
