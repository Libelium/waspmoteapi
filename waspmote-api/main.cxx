
#include <WProgram.h>

int main(void)
{
	init();
	
	// get serial id
	_serial_id = Utils.readSerialID();
	
	setup();
    
	for (;;)
		loop();
        
	return 0;
}

