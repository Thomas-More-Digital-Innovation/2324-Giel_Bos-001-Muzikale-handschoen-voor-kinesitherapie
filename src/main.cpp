// - INCLUDES - //
#include <Arduino.h>                 // arduino core

#include <SD.h>                      // sd card library
#include <SPI.h>                     // spi library for sd card
#include <fileToVector.h>
#include <stdio.h>
#include <stdlib.h> 

#include <Adafruit_MPU6050.h>        // mpu6050 library
#include <Adafruit_Sensor.h>         // sensor library for mpu6050
#include <Wire.h>                    // wire library for mpu6050
#include <Adafruit_BusIO_Register.h> // busio library for mpu6050
#include <gyro.h>

#include <Adafruit_NeoPixel.h>       // neopixel library for ledring

#include <vector>                    // library for dynamic array (vector)

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"

#include <ArduinoJson.h> 

const char* ssid = "iPhone van Matt";
const char* password = "helloThisIsAPassword";

AsyncWebServer server(80);
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

#define PIN_SND 27 // pin for sound module

#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392
#define NOTE_C5 523

Adafruit_MPU6050 mpu_hand;    // mpu hand
Adafruit_MPU6050 mpu_thumb;   // mpu thumb
Adafruit_MPU6050 mpu_fingers; // mpu fingers

gyro hand(mpu_hand);
gyro thumb(mpu_thumb);
gyro fingers(mpu_fingers);

std::array<string,2> wifiCred;

Adafruit_NeoPixel ledring = Adafruit_NeoPixel(12, PIN_LED,  NEO_GRB + NEO_KHZ800);

std::array<std::array<uint32_t, 3>,12> smiley;


void off(){
  ledring.show();
  delay(1000);
  for(int i = 0; i<12; i++){
    ledring.setPixelColor(i, 0,0,0);
  }
  ledring.show();
}

void showFigure(std::array<std::array<uint32_t, 3>,12> figure, int brightness){
    ledring.setBrightness(brightness);
    for(int i = 0; i < figure.size(); i++){
        if (i >= 0 && i < 12) {
            ledring.setPixelColor(i,figure[i][0],figure[i][1],figure[i][2]);
        }
    }
    ledring.show();
}

void playsound(int note, int duration){
  pinMode(PIN_SND, OUTPUT); // sound pin is output
  tone(PIN_SND, note, duration);
}

String getMime(String filename){
  if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else {
    return "application/octet-stream";
  }
}

void setup() {
  Serial.begin(115200);      // open serial monitor

  pinMode(14, OUTPUT);       // pin 14 is output pin
  digitalWrite(14, HIGH);    // pin 14 output high (used for changing I2C address gyro hand)
  Wire.begin(SDA_1, SCL_1);  // I2C bus 1
  Wire1.begin(SDA_2, SCL_2); // I2C bus 2

  pinMode(PIN_SND, OUTPUT);

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

  hand.gyroSetup(0x69, Wire);
  thumb.gyroSetup(0x68, Wire);
  fingers.gyroSetup(0x68, Wire1);

  showFigure(smiley, 50);
  //playsound(NOTE_C4, 250);
  //playsound(NOTE_E4, 250);
  //playsound(NOTE_G4, 250);
  //playsound(NOTE_C5, 250);
  delay(1000);
  off();
  

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println();
  Serial.println(WiFi.localIP());

  std::vector<String> directories;
  directories.push_back("/webpage");

  File root = SD.open(directories[0]);
  if(!root){
    Serial.println("Opening directory failed");
    return;
  }
  if(!root.isDirectory()){
    Serial.println("Not a directory");
    return;
  }
  File file = root.openNextFile();
  while(directories.size() > 0){
    while(file){
      if(file.isDirectory()){
        directories.push_back(directories[0] + "/" + file.name());
      }
      else{
        String filePath = directories[0] + "/"+ file.name();
        String fileMime = getMime(file.name());
        Serial.println(fileMime);
        String requestPath = "";
        filePath.replace("/webpage", "");
        requestPath = filePath;
        filePath = directories[0] + "/"+ file.name();
        Serial.println(filePath);
        if(requestPath == "/index.html"){
          server.on("/", HTTP_GET, [filePath, fileMime](AsyncWebServerRequest *request){
            request->send(SD, filePath, fileMime);
          });
        }
        const char* requestCString = requestPath.c_str();
        Serial.println(requestCString);
        server.on(requestCString, HTTP_GET, [filePath, fileMime](AsyncWebServerRequest *request){
          request->send(SD, filePath, fileMime);
        });
      }
      file = root.openNextFile();
    }
    directories.erase(directories.begin());
    if(directories.size() >0){
      root = SD.open(directories[0]);
      file = root.openNextFile();
    }
  }

  server.on("/getex", HTTP_GET, [](AsyncWebServerRequest *request){
    File file = SD.open("/database/exercises.json");
        if(!file){
      request->send(500, "text/plain", "Failed to open exercises file");
      return;
    }
    
    // Parse the JSON data
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
      request->send(500, "text/plain", "Failed to parse exercises file");
      return;
    }
    
    // Send JSON response
    String json;
    serializeJsonPretty(doc, json);
    request->send(200, "application/json", json);
  });

  server.begin();

  Serial.println("server began");
}

void executeExSequence(){

  std::vector<std::array<int, 3>> oefeningen;
  int oefeningenreek = Serial.parseInt();
  for(int i = 0; i < reeksenArray[oefeningenreek].length(); i++){
    int oefening = reeksenArray[oefeningenreek].substring(i, i+1).toInt();
    bool oefeningKlaar = false;
    Serial.println(oefeningenArray[oefening]);
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
              oefeningKlaar = true;
            }
          }
        }
      }
    }
    else{
      while (oefeningKlaar == false){
        uint16_t fsrReading = analogRead(FSR); // analog reading from FSR
        if (fsrReading > 2500){
          oefeningKlaar = true;
        }
      }
    }
  showFigure(smiley, 50);
  playsound(NOTE_C4, 250);
  playsound(NOTE_E4, 250);
  playsound(NOTE_G4, 250);
  playsound(NOTE_C5, 250);
  off();
    Serial.println("oefening klaar");
  }
  Serial.println("oefeningenreeks klaar");
}

void loop(){
  
}