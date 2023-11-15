// - INCLUDES - //
#include <Arduino.h>                 // arduino core
#include <Adafruit_NeoPixel.h>       // neopixel library for ledring
#include <SD.h>                      // sd card library
#include <SPI.h>                     // spi library for sd card
#include <Adafruit_MPU6050.h>        // mpu6050 library
#include <Adafruit_Sensor.h>         // sensor library for mpu6050
#include <Wire.h>                    // wire library for mpu6050
#include <Adafruit_BusIO_Register.h> // busio library for mpu6050
#include <vector>                    // library for dynamic array (vector)
#include <string>
using namespace std;

// - DEFINES - //
// -- music notes -- //
#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392
#define NOTE_C5 523

// -- pins for sensor modules -- //
#define SCL_1 22 // pin for mpu6050 clock - I2C 1
#define SDA_1 23 // pin for mpu6050 sda - I2C 1
#define SCL_2 32 // pin for mpu6050 clock - I2C 2
#define SDA_2 33 // pin for mpu6050 sda- I2C 2
#define FSR 36   // pin for force sensor

// -- pins for feedback modules -- //
#define PIN_LED 15 // pin for neopixel ledring
#define PIN_BUZ 12 // pin for buzzer module
#define PIN_SND 27 // pin for sound module

// -- other defines -- //
Adafruit_NeoPixel ring = Adafruit_NeoPixel(12, PIN_LED, NEO_GRB + NEO_KHZ800); // define ledring
File myFile;                                                                   // define file for sd card
std::vector<int> exercises;                                                    // vector for storing exercises

Adafruit_MPU6050 mpu_hand;    // mpu hand
Adafruit_MPU6050 mpu_thumb;   // mpu thumb
Adafruit_MPU6050 mpu_fingers; // mpu fingers

void setup(){

}

void loop(){
  
}