//
//    FILE: Mpu6050.h
//  AUTHOR: Bjarke Waltenburg
// VERSION: 0.1.00
//    DATE: 2018-June-14
// PURPOSE: Recording data from the MPU6050 sensor
//     URL: comming
// HISTORY: See Mpu6050.cpp

#ifndef Mpu6050_h
#define Mpu6050_h

#include "Arduino.h"
#include <Wire.h>

class Mpu6050
{
public:
  Mpu6050(int  _address);
  void setup(int SCL, int SDA);
  void dataReceiver();
  void processData();
  void debugFunction();
  void debugFunctionAc();
  void debugFunctionGy();
  float gForceX, gForceY, gForceZ, rotX, rotY, rotZ, gForceSum;
private:
  int _address;
  int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;
};

#endif
