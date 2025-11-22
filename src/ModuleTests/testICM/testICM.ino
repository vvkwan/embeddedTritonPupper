// I2C device class (I2Cdev) demonstration Arduino sketch adapted for ICM42670P
// This adaptation focuses on reading RAW Accelerometer and Gyroscope data

/* ============================================
 * Original I2Cdev library code is placed under the MIT license
 * Copyright (c) 2012 Jeff Rowberg
 * The ICM42670P-specific parts are adapted to use the provided driver.
 * ===============================================
*/

#include "I2Cdev.h" // Still required for I2Cdev functions if used, but ICM42670 driver handles I2C lower layer
#include "petoi_icm42670p.h" // The driver for the ICM42670P
#include "inv_imu_apex.h" // Required by the ICM42670P.h driver

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h, and by the ICM42670P driver.
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// Class default I2C address is 0x68 (AD0 low/LSB = 0) or 0x69 (AD0 high/LSB = 1)
// The ICM42670 constructor handles this: ICM42670(Wire, bool lsb_high);
// If AD0 is connected to GND, use false for lsb.
imu42670p imu(Wire, false); // Initialize ICM42670 with default I2C (Wire) and AD0/LSB low (0x68)

#define LED_PIN 13 // (Arduino is 13)
bool blinkState = false;

// Data structure to hold sensor readings from the ICM42670 driver
inv_imu_sensor_event_t event;

// Configuration settings
const uint16_t ACCEL_ODR_HZ = 100; // Accelerometer Output Data Rate
const uint16_t ACCEL_FSR_G = 4; // Accelerometer Full Scale Range (+/- 4G)
const uint16_t GYRO_ODR_HZ = 100; // Gyroscope Output Data Rate
const uint16_t GYRO_FSR_DPS = 500; // Gyroscope Full Scale Range (+/- 500 deg/s)
int devStatus = 100;


// ================================================================
// ===                       INITIAL SETUP                        ===
// ================================================================

void setup() {
  // join I2C bus (handled internally by imu.begin())
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#endif

  // initialize serial communication
  Serial.begin(115200);
  while (!Serial); // wait for Leonardo enumeration, others continue immediately

  // initialize device
  Serial.println(F("Initializing I2C devices (ICM42670P)..."));

  // Start the ICM42670P communication
  devStatus = imu.begin(); 
  imu.init(200, 2, 250);
  imu.getOffset(100);
  Serial.println(devStatus);
  // verify connection
  if (devStatus == 0) {
    Serial.println(F("ICM42670P connection successful (WHO_AM_I check passed)."));

    // Start Accelerometer and Gyroscope in Low Noise Mode
    Serial.print(F("Starting Accelerometer (")); Serial.print(ACCEL_FSR_G); Serial.print("G @ "); Serial.print(ACCEL_ODR_HZ); Serial.println("Hz)...");
    devStatus = imu.startAccel(ACCEL_ODR_HZ, ACCEL_FSR_G);
    if (devStatus != 0) Serial.println(F("Accel start failed!"));

    Serial.print(F("Starting Gyroscope (")); Serial.print(GYRO_FSR_DPS); Serial.print("dps @ "); Serial.print(GYRO_ODR_HZ); Serial.println("Hz)...");
    devStatus |= imu.startGyro(GYRO_ODR_HZ, GYRO_FSR_DPS);
    if (devStatus != 0) Serial.println(F("Gyro start failed!"));

    // Set a note that the sensor is ready (simplified from DMP logic)
    Serial.println(F("Sensor ready! Reading data..."));

  } else {
    // ERROR!
    Serial.print(F("ICM42670P Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F("). Check wiring and I2C address."));
  }

  // configure LED for output
  pinMode(LED_PIN, OUTPUT);
}



// ================================================================
// ===                      MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
  // In the original MPU6050 DMP sketch, the loop waits for an interrupt.
  // For raw polling, we just read the data directly.

  // int status = imu.getDataFromRegisters(event);
  imu.getImuGyro();
  imu.printRealworldData();
  // if (status == 0) {
    // Data successfully read
    
    // // Check if Accelerometer data is valid
    // if (imu.isAccelDataValid(&event)) {
    //   Serial.print("accel\t");
    //   Serial.print(event.accel[0]); // Raw X-axis acceleration
    //   Serial.print("\t");
    //   Serial.print(event.accel[1]); // Raw Y-axis acceleration
    //   Serial.print("\t");
    //   Serial.print(event.accel[2]); // Raw Z-axis acceleration
    // }
    
    // // Check if Gyroscope data is valid
    // if (imu.isGyroDataValid(&event)) {
    //   Serial.print("\tgyro\t");
    //   Serial.print(event.gyro[0]); // Raw X-axis rotation
    //   Serial.print("\t");
    //   Serial.print(event.gyro[1]); // Raw Y-axis rotation
    //   Serial.print("\t");
    //   Serial.print(event.gyro[2]); // Raw Z-axis rotation
    // }

    // Serial.println(devStatus); // Newline for the current reading
    
    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
    
  // } else {
  //   // Handle read error if necessary
  //   // Serial.println(F("Error reading data.")); 
  // }

  // Delay to control the output rate. This should be adjusted based on the ODR.
  // ODR is 100Hz, so a 10ms delay is appropriate for polling.
  delay(10); 
}