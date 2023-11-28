#include <Arduino.h>
#include <Adafruit_MPU6050.h>        // mpu6050 library
#include <Adafruit_Sensor.h>         // sensor library for mpu6050
#include <Wire.h>                    // wire library for mpu6050
#include <Adafruit_BusIO_Register.h> // busio library for mpu6050
#include <gyro.h>

gyro::gyro(Adafruit_MPU6050 sensor){
  _sensor = sensor;
}

void gyro::gyroSetup(int hex,TwoWire &wire){

  if (!_sensor.begin(hex, &wire))
  {
    Serial.println("Failed to find gyro");
    while (1)
    {
      delay(1000);
    }
  }
    _sensor.begin(hex, &wire);

    _sensor.setAccelerometerRange(MPU6050_RANGE_8_G);

    _sensor.setFilterBandwidth(MPU6050_BAND_5_HZ);
}

std::array<int, 3> gyro::gyroData(){
  std::array<int, 3> result;
  sensors_event_t a, g, t;
  _sensor.getEvent(&a, &g, &t);

  result[0] = conv((int)a.acceleration.x);
  result[1] = conv((int)a.acceleration.y);;
  result[2] = conv((int)a.acceleration.z);;
  return result;
}

int gyro::conv(int input){
  if (input < -7){
    return -1;
  }
  else if (input > 7){
    return 1;
  }
  else{
    return 0;
  }
}