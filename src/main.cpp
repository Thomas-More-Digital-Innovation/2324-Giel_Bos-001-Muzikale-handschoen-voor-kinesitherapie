// - INCLUDES - //
#include <Arduino.h>                 // arduino core
#include <Adafruit_NeoPixel.h>       // neopixel library for ledring
#include <SD.h>                      // sd card library
#include <SPI.h>                     // spi library for sd card
#include <vector>                    // library for dynamic array (vector)
using namespace std;

File reeksen;
std::vector<String> reeksenArray;
File myFile;                         // define file for sd card
std::vector<String> exercises;  

std::vector<String>  splitString(String input, char character){
  std::vector<String> result{};
  int firstCharacter = -1;

  for(int i=0; i<input.length(); i++){
    if((input.charAt(i) == character)){
      result.push_back(input.substring(firstCharacter+1, i));
      firstCharacter = i;
    }
    
    if(i == input.length()-1){
      result.push_back(input.substring(firstCharacter+1, i+1));
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
        exercises.push_back(input);
      }
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening oefeningen.txt");
  }

  reeksen = SD.open("/reeksen.txt");

  if (reeksen) {
    while (reeksen.available()) {
      String input = "";
      input = reeksen.readStringUntil('\n');
      input.trim();
      reeksenArray.push_back(input);
    }
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop(){
  Serial.println("geef de oefeningen reeks in");
  while(Serial.available() == 0);
  int oefeningenreek = Serial.parseInt();
  for(int i = 0; i < reeksenArray[oefeningenreek].length(); i++){
    int ex = reeksenArray[oefeningenreek].substring(i, i+1).toInt();
    Serial.println(exercises[ex]);
    if(exercises[ex] != "p"){
      std::vector<String> gyroData = splitString(exercises[ex], ';');
      std::vector<std::vector<int>> gyroInt;
      for(int j=0; j < gyroData.size(); j++){
        std::vector<String> gyroString = splitString(gyroData[j], ',');
        std::vector<int> gyroPreInt;
        for(int k=0; k<gyroString.size(); k++){
          gyroPreInt.push_back(gyroString[k].toInt());
          Serial.print(gyroString[k].toInt());
        }
        Serial.println();
        gyroInt.push_back(gyroPreInt);
      }
    }
  }
}