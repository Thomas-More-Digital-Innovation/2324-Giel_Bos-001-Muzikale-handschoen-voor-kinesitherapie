#ifndef gyro_h
#define gyro_h
#include <Arduino.h>
#include <Adafruit_MPU6050.h>        // mpu6050 library
#include <Adafruit_Sensor.h>         // sensor library for mpu6050
#include <Wire.h>                    // wire library for mpu6050
#include <Adafruit_BusIO_Register.h> // busio library for mpu6050

class gyro{
    public:
        gyro(Adafruit_MPU6050 sensor);
        void gyroSetup(TwoWire &wire);
        int conv(int input);
    private:
        Adafruit_MPU6050 _sensor;
};

#endif