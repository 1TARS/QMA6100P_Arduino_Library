/*
  example6-tap

  This example shows the how to enable the tap interrupts.

	Please refer to the header file for more possible settings, found here:
	..\SparkFun_KX13X_Arduino_Library\src\sfe_kx13x_defs.h

  Written by Elias Santistevan @ SparkFun Electronics, October 2022

	Product:

		https://www.sparkfun.com/products/17871

  Repository:

		https://github.com/sparkfun/SparkFun_KX13X_Arduino_Library

  SparkFun code, firmware, and software is released under the MIT 
	License	(http://opensource.org/licenses/MIT).
*/

#include <Wire.h>
#include "SparkFun_KX13X.h"

SparkFun_KX132 kxAccel; 
// SparkFun_KX134 kxAccel; // For the KX134, uncomment this and comment line above

byte direction = 0;

void setup() 
{
	
	Wire.begin();

	Serial.begin(115200);
  Serial.println("Welcome.");

	// Wait for the Serial monitor to be opened. 
  while(!Serial)
    delay(50);


  if( !kxAccel.begin() )
	{
    Serial.println("Could not communicate with the the KX13X. Freezing.");
    while(1);
	}

	Serial.println("Ready.");

	// Reset the chip so that old settings don't apply to new setups.
	if( kxAccel.softwareReset() )
		Serial.println("Reset.");

	// Many settings for KX13X can only be                    														
	// applied when the accelerometer is powered down.                  														
	// However there are many that can be changed "on-the-fly"
	// check datasheet for more info, or the comments in the
	// "...regs.h" file which specify which can be changed when.
	kxAccel.enableAccel(false); 

  kxAccel.setRange(0x18);                 //  16g Range
	kxAccel.enableTapEngine();              //  Enable tap Engine
	kxAccel.enableDirecTapInterupt();       //  This enables checking the direction of the interrupt
	//kxAccel.setTapDataRate(uint8_t rate); //  Default is 400Hz
	kxAccel.enableAccel();          


}

void loop() 
{
	// Check if tap was detected
	if( kxAccel.tapDetected() )
	{
		Serial.print("Tap Detected: ");
		Serial.println(kxAccel.getDirection(), HEX);
		kxAccel.clearInterrupt();
	}

	if( kxAccel.unknownTap() || kxAccel.doubleTapDetected() ) // These all share the same bit space
		kxAccel.clearInterrupt();

  delay(25); // Delay should be 1/ODR (Output Data Rate), default tap ODR is 400Hz

}
