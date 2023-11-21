// - INCLUDES - //
#include <Arduino.h>                 // arduino core

#include <SD.h>                      // sd card library
#include <SPI.h>                     // spi library for sd card
#include <fileToVector.h> 

#include <Adafruit_MPU6050.h>        // mpu6050 library
#include <Adafruit_Sensor.h>         // sensor library for mpu6050
#include <Wire.h>                    // wire library for mpu6050
#include <Adafruit_BusIO_Register.h> // busio library for mpu6050
#include <gyro.h>

#include <Adafruit_NeoPixel.h>       // neopixel library for ledring
#include <ledring.h>

#include <vector>                    // library for dynamic array (vector)
using namespace std;

File reeksenFile;
std::vector<String> reeksenArray;
File oefeningenFile;                         // define file for sd card
std::vector<String> oefeningenArray;

#define SCL_1 22 // pin for mpu6050 clock - I2C 1
#define SDA_1 23 // pin for mpu6050 sda - I2C 1
#define SCL_2 32 // pin for mpu6050 clock - I2C 2
#define SDA_2 33 // pin for mpu6050 sda- I2C 2

#define FSR 36   // pin for force sensor

#define PIN_LED 15 // pin for neopixel ledring

Adafruit_MPU6050 mpu_hand;    // mpu hand
Adafruit_MPU6050 mpu_thumb;   // mpu thumb
Adafruit_MPU6050 mpu_fingers; // mpu fingers

gyro hand(mpu_hand);
gyro thumb(mpu_thumb);
gyro fingers(mpu_fingers);

Adafruit_NeoPixel ledring1 = Adafruit_NeoPixel(12, PIN_LED, NEO_GRB + NEO_KHZ800);

ledring ring(ledring1);

std::array<std::array<uint32_t, 3>,12> smiley;

void setup() {
  Serial.begin(115200);      // open serial monitor

  pinMode(14, OUTPUT);       // pin 14 is output pin
  digitalWrite(14, HIGH);    // pin 14 output high (used for changing I2C address gyro hand)
  Wire.begin(SDA_1, SCL_1);  // I2C bus 1
  Wire1.begin(SDA_2, SCL_2); // I2C bus 2

  for(int i; i < smiley.size(); i++){
    if((i != 5) && (i != 7) && (i != 9)){
      smiley[i][0] = 5;
      smiley[i][1] = 213;
      smiley[i][2] = 250;
    }
    else{
      smiley[i][0] = 0;
      smiley[i][1] = 0;
      smiley[i][2] = 0;
    }
  }

  while (!Serial);
 
  Serial.print("Initializing SD card...");
 
 if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  oefeningenFile = SD.open("/oefeningen.txt");
  oefeningenArray = toStringVector(oefeningenFile);

  reeksenFile = SD.open("/reeksen.txt");
  reeksenArray = toStringVector(reeksenFile);

  hand.gyroSetup(0x69, Wire);
  Serial.println("hand done");
  thumb.gyroSetup(0x68, Wire);
  Serial.println("thumb done");
  fingers.gyroSetup(0x68, Wire1);
  Serial.println("fingers done");

  //ring.showFigure(smiley, 50);
  delay(1000);
}

void loop(){
  Serial.println("geef de oefeningen reeks in");
  while(Serial.available() == 0);

  std::vector<std::array<int, 3>> oefeningen;
  int oefeningenreek = Serial.parseInt();
  for(int i = 0; i < reeksenArray[oefeningenreek].length(); i++){

    int oefening = reeksenArray[oefeningenreek].substring(i, i+1).toInt();

    bool oefeningKlaar = false;

    if(oefeningenArray[oefening] != "p"){
      oefeningen = toIntVector(oefeningenArray[oefening]);

      while (oefeningKlaar == false){
        std::array<int, 3> coHand = hand.gyroData();
        std::array<int, 3> coThumb = thumb.gyroData();
        std::array<int, 3> coFingers = fingers.gyroData();

        std::array<std::array<int, 3>, 3> co2D{coHand, coThumb, coFingers};
        std::array<bool, 3> boolArray;
        for(int i = 0; i < oefeningen.size(); i++){
          for(int j = 0; j < oefeningen[i].size(); j++){
            if(oefeningen[i][j] != 0){
              boolArray[i] = true;
            }
          }
        }

        for(int i = 0; i < oefeningen.size(); i++){
          if(boolArray[i] == true){
            if(oefeningen[i] == co2D[i]){
              oefeningKlaar == true;
            }
          }
        }
      }
    }
    else{
      while (oefeningKlaar == false){
        uint16_t fsrReading = analogRead(FSR); // analog reading from FSR
        if (fsrReading > 2500){
          oefeningKlaar == true;
        }
      }
    }
  }
}