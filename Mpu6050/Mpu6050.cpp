//
//    FILE: Mpu6050.cpp
//  AUTHOR: Bjarke Waltenburg
// VERSION: 0.1.00
//    DATE: 2018-June-14
// PURPOSE: Recording data from the MPU6050 sensor
//
// The library gets data from the sensor and makes it available for use
// in your sketch.
// The values recorded from the sensor is converted to respectively force
// in g's and rotation in degrees.
//
// CREDIT:
// The library is based on a sketch from Justin of the blog itsalllost.com
// https://www.itsalllost.com/mpu6050-esp8266-01-mqtt/
//
// HISTORY:
// 0.1.00 - 2018-06-14 initial version


#include "Arduino.h"
#include "Mpu6050.h"
#include <Wire.h>
#include <math.h>

Mpu6050::Mpu6050(int address){
  _address=address;
  AcX=0;
  AcY=0;
  AcY=0;
  GyX=0;
  GyY=0;
  GyZ=0;
}

void Mpu6050::setup(int SCL, int SDA){
  Wire.begin(SCL, SDA); //Initialize the sensor. SCL and SDA pins as arguments.
  Wire.beginTransmission(_address);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void Mpu6050::dataReceiver(){
  Wire.beginTransmission(_address);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(_address, 14, true); // request a total of 14 registers
  AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  processData();
}

void Mpu6050::processData(){
  gForceX = AcX / 16400.0;
  gForceY = AcY / 16400.0;
  gForceZ = AcZ / 16400.0;

  rotX = GyX / 131.0;
  rotY = GyY / 131.0;
  rotZ = GyZ / 131.0;

  //sum of forces acting expressed in g-force
  gForceSum = fabsf(gForceX) + fabsf(gForceY) + fabsf(gForceZ);
}

void Mpu6050::debugFunction(){
  // Print the MPU values to the serial monitor
  Serial.print("Accelerometer: ");
  Serial.print("X="); Serial.print(gForceX);
  Serial.print("|Y="); Serial.print(gForceY);
  Serial.print("|Z="); Serial.println(gForceZ);
  Serial.print("Gyroscope:");
  Serial.print("X="); Serial.print(rotX);
  Serial.print("|Y="); Serial.print(rotY);
  Serial.print("|Z="); Serial.println(rotZ);
}

void Mpu6050::debugFunctionAc(){
  // Print the MPU Acc values to the serial monitor
  Serial.print("Accelerometer: ");
  Serial.print("X="); Serial.print(gForceX);
  Serial.print("|Y="); Serial.print(gForceY);
  Serial.print("|Z="); Serial.println(gForceZ);
}

void Mpu6050::debugFunctionGy(){
  // Print the MPU Gyro values to the serial monitor
  Serial.print("Gyroscope:");
  Serial.print("X="); Serial.print(rotX);
  Serial.print("|Y="); Serial.print(rotY);
  Serial.print("|Z="); Serial.println(rotZ);
}
