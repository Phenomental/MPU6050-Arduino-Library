#include <Mpu6050.h>

// I2C address of the MPU-6050 - 0x68 or 0x69 if AD0 is pulled HIGH
int mpuAddress = 0x68;

//initialize the MPU sensor object
Mpu6050 mpu(mpuAddress);

//defining the pin connections
#define SCL D5
#define SDA D6

void setup() {
  Serial.begin(9600);
  mpu.setup(D5, D6);
}

//Data can be accessed by using any of the below function calls:
  //mpu.gForceX;
  //mpu.gForceY;
  //mpu.gForceZ;
  //mpu.gForceSum;
  //mpu.rotX;
  //mpu.rotY;
  //mpu.rotZ;

void loop() {
  mpu.dataReceiver(); //get data from MPU sensor
  mpu.debugFunction(); //prints out recieved data from the sensor

  delay(1000);
}
