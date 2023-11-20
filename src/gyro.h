#ifndef gyro_h
#define gyro_h
#include <Arduino.h>
#include <Adafruit_MPU6050.h>        // mpu6050 library
#include <Adafruit_Sensor.h>         // sensor library for mpu6050
#include <Wire.h>                    // wire library for mpu6050
#include <Adafruit_BusIO_Register.h> // busio library for mpu6050

class gyro{
    public:
        void gyroSetup(int hex, TwoWire &wire);
        std::array<int, 3> gyroData();
        int conv(int input);
    private:
        Adafruit_MPU6050 _sensor;
};

#endif