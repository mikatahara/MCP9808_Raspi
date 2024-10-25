#include <stdio.h>
#include <stdint.h>

#include "Wiringpi_MCP9808.h"
#include <wiringPi.h>

int main()
{
	// Make sure the sensor is found, you can also pass in a different i2c
	// address with tempsensor.begin(0x19) for example, also can be left in blank for default address use
	// Also there is a table with all addres possible for this sensor, you can connect multiple sensors
	// to the same i2c bus, just configure each sensor with a different address and define multiple objects for that
	//  A2 A1 A0 address
	//  0  0  0   0x18  this is the default address
	//  0  0  1   0x19
	//  0  1  0   0x1A
	//  0  1  1   0x1B
	//  1  0  0   0x1C
	//  1  0  1   0x1D
	//  1  1  0   0x1E
	//  1  1  1   0x1F
	Wiringpi_MCP9808 mcp9808;
	bool result = mcp9808.init(MCP9808_I2CADDR_DEFAULT);

	if(result){
		fprintf(stderr,"Success to create the interface for MCP9808\n");
	} else {
		fprintf(stderr,"Fale to create the interface for MCP9808\n");
	}
	
	// sets the resolution mode of reading, the modes are defined in the table bellow:
	// Mode Resolution SampleTime
	//  0    0.5°C       30 ms
	//  1    0.25°C      65 ms
	//  2    0.125°C     130 ms
	//  3    0.0625°C    250 ms
    mcp9808.write8(MCP9808_REG_RESOLUTION, 3);	//Set Resolution
	fprintf(stderr,"Resolution = %d\n",mcp9808.read8(MCP9808_REG_RESOLUTION));	//Read Resolution
	
	while(1){
		mcp9808.wake_shutdown(true);
		fprintf(stderr,"%5.2f *C\n",mcp9808.readTempC());
		mcp9808.wake_shutdown(false);
		delay(1000);
	}
}
