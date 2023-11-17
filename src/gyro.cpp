#include <Arduino.h>
#include <Adafruit_MPU6050.h>        // mpu6050 library
#include <Adafruit_Sensor.h>         // sensor library for mpu6050
#include <Wire.h>                    // wire library for mpu6050
#include <Adafruit_BusIO_Register.h> // busio library for mpu6050
#include <gyro.h>

gyro::gyro(Adafruit_MPU6050 sensor){
    _sensor = sensor;
}

void gyro::gyroSetup(TwoWire &wire){
    if(!_sensor.begin(0x69, &wire)){}
}

int conv(int input)
{
  if (input < -7)
  {
    return -1;
  }
  else if (input > 7)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}