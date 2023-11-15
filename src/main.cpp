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

// // -- other defines -- //
//Adafruit_NeoPixel ring = Adafruit_NeoPixel(12, PIN_LED, NEO_GRB + NEO_KHZ800); // define ledring
File myFile;                                                                   // define file for sd card
std::vector<vector<String>> exercises;                                                    // vector for storing exercises

Adafruit_MPU6050 mpu_hand;    // mpu hand
Adafruit_MPU6050 mpu_thumb;   // mpu thumb
Adafruit_MPU6050 mpu_fingers; // mpu fingers

std::vector<String> splitString(String input, char character){
  std::vector<String> result;
  int firstCharacter = 0;
  int secondCharacter = 0;

  while(firstCharacter != input.length()-1){
    secondCharacter = input.indexOf(character, firstCharacter);
    result.push_back(input.substring(firstCharacter, secondCharacter));
    firstCharacter = secondCharacter;
  }
  return result;
}

void setup(){
  Serial.begin(115200);  

  Serial.print("Initializing SD card...");
 
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  myFile = SD.open("/oefeningen.txt");
  if (myFile) {
      while (myFile.available()) {
        String input = "";
        input = myFile.readStringUntil('\n'); 
        input.trim();
        exercises.push_back(splitString(input, ';'));
      }
  }

  for(int i=0; i < exercises.size(); i++){
    Serial.println(exercises[i][0]);
  }
}

void loop(){

}