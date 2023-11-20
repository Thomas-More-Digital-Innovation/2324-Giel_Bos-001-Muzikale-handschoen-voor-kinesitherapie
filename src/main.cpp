// - INCLUDES - //
#include <Arduino.h>                 // arduino core
#include <Adafruit_NeoPixel.h>       // neopixel library for ledring

#include <SD.h>                      // sd card library
#include <SPI.h>                     // spi library for sd card
#include <fileToVector.h>

#include <gyro.h>

#include <vector>                    // library for dynamic array (vector)
using namespace std;

File reeksenFile;
std::vector<String> reeksenArray;
File oefeningenFile;                         // define file for sd card
std::vector<String> oefeningenArray;

fileToVector fileToVectorFunctions;

#define SCL_1 22 // pin for mpu6050 clock - I2C 1
#define SDA_1 23 // pin for mpu6050 sda - I2C 1
#define SCL_2 32 // pin for mpu6050 clock - I2C 2
#define SDA_2 33 // pin for mpu6050 sda- I2C 2

gyro hand;
gyro thumb;
gyro fingers;


void setup() {
  Serial.begin(115200);      // open serial monitor

  pinMode(14, OUTPUT);       // pin 14 is output pin
  digitalWrite(14, HIGH);    // pin 14 output high (used for changing I2C address gyro hand)
  Wire.begin(SDA_1, SCL_1);  // I2C bus 1
  Wire1.begin(SDA_2, SCL_2); // I2C bus 2

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
  Serial.print("Initializing SD card...");
 
 if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");


  oefeningenFile = SD.open("/oefeningen.txt");
  oefeningenArray = fileToVectorFunctions.toStringVector(oefeningenFile);

  reeksenFile = SD.open("/reeksen.txt");
  reeksenArray = fileToVectorFunctions.toStringVector(reeksenFile);

  hand.gyroSetup(0x69, Wire);
  thumb.gyroSetup(0x68, Wire);
  fingers.gyroSetup(0x68, Wire1);
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
      oefeningen = fileToVectorFunctions.toIntVector(oefeningenArray[oefening]);

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
      //push sensor test
    }
  }
}