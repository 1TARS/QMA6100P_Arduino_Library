//  QMA6100P.h
//
// This is a library written for the SparkFun Triple Axis Accelerometer - QMA6100P
//

// The following class implements the	Arduino Interface for the SparkFun Triple
// Axis Acceleromters - QMA6100P.

#pragma once
#include "Qwiic_QMA6100P.h"
#include <Wire.h>

class QMA6100P : public QwDevQMA6100P
{

public:
  QMA6100P(){};

  ///////////////////////////////////////////////////////////////////////
  // begin()
  //
  // This method is called to initialize the ISM330DHCX library and connect to
  // the ISM330DHCX device. This method must be called before calling any other method
  // that interacts with the device.
  //
  // This method follows the standard startup pattern in SparkFun Arduino
  // libraries.
  //
  //  Parameter   Description
  //  ---------   ----------------------------
  //  wirePort    optional. The Wire port. If not provided, the default port is used
  //  address     optional. I2C Address. If not provided, the default address is used.
  //  retval      true on success, false on startup failure
  //
  // This methond is overridden, implementing two versions.
  //
  // Version 1:
  // User skips passing in an I2C object which then defaults to Wire.
  bool begin(uint8_t deviceAddress = QMA6100P_ADDRESS_HIGH)
  {
    // Setup  I2C object and pass into the superclass
    setCommunicationBus(_i2cBus, deviceAddress);

    // Initialize the I2C buss class i.e. setup default Wire port
    _i2cBus.init();

    // Initialize the system - return results
    return this->init();
  }

  // Version 2:
  //  User passes in an I2C object and an address (optional).
  bool begin(TwoWire &wirePort, uint8_t deviceAddress = QMA6100P_ADDRESS_HIGH)
  {
    // Setup  I2C object and pass into the superclass
    setCommunicationBus(_i2cBus, deviceAddress);

    // Give the I2C port provided by the user to the I2C bus class.
    _i2cBus.init(wirePort, true);

    // Initialize the system - return results
    return this->QwDevQMA6100P::init();
  }

private:
  // I2C bus class
  sfe_QMA6100P::QwI2C _i2cBus;
}; 