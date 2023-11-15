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

File myFile;                         // define file for sd card
std::vector<std::vector<String>> exercises;  

std::vector<String>  splitString(String input, char character){
  std::vector<String> result{};
  int firstCharacter = 0;

  for(int i=0; i<input.length(); i++){
    if(input.charAt(i) == character){
      result.push_back(input.substring(firstCharacter, i));
      firstCharacter = i;
    }
  }
  return result;
}

void setup()
{
  Serial.begin(115200);      // open serial monitor

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
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
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  for(int i=0; i < exercises.size(); i++){
    for(int j=0; j < exercises[i].size(); j++){
      Serial.print(exercises[i][j]);
    }
    Serial.println();
  }
}

void loop(){

}