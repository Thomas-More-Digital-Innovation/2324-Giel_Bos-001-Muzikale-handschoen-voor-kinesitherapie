// - INCLUDES - //
#include <Arduino.h>                 // arduino core

#include <Adafruit_MPU6050.h>        // mpu6050 library
#include <Adafruit_Sensor.h>         // sensor library for mpu6050
#include <Wire.h>                    // wire library for mpu6050
#include <Adafruit_BusIO_Register.h> // busio library for mpu6050
#include <gyro.h>

#include<fileToVector.h>

#include <Adafruit_NeoPixel.h>       // neopixel library for ledring

#include <vector>                    // library for dynamic array (vector)

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLEServer* pServer = NULL;
BLECharacteristic* pLedCharacteristic = NULL;
BLECharacteristic* pNotificationCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

bool executeExBool = false;
std::string incomingValue = "";

std::vector<std::array<int, 3>> oefeningen =  toIntVector(incomingValue.c_str());
std::array<bool, 3> boolArray;

#define SERVICE_UUID "19b10000-e8f2-537e-4f6c-d104768a1214"
#define LED_CHARACTERISTIC_UUID "19b10002-e8f2-537e-4f6c-d104768a1214"
#define NOTIFICATION_CHARACTERISTIC_UUID "19b10001-e8f2-537e-4f6c-d104768a1214"

using namespace std;

std::vector<String> reeksenArray;                 // define file for sd card
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

void notifyExerciseDone() {
  if (deviceConnected) {
    String message = "ExerciseDone";
    pNotificationCharacteristic->setValue(message.c_str());
    pNotificationCharacteristic->notify(); // Notify connected devices
    Serial.println("Notification Send");
    delay(1000);
  }
}

void notifyRewardDone() {
  if (deviceConnected) {
    String message = "RewardDone";
    pNotificationCharacteristic->setValue(message.c_str());
    pNotificationCharacteristic->notify(); // Notify connected devices
    Serial.println("Notification Send");
    delay(1000);
  }
}

std::array<uint32_t, 3> hexToRGB(String hex) {
    // Convert the hexadecimal string to integer values
    uint32_t color = strtol(hex.substring(1).c_str(), NULL, 16); // Skip the '#' character

    std::array<uint32_t, 3> rgb;
    // Extract red, green, and blue components
    rgb[0] = (color >> 16) & 0xFF; // Red
    rgb[1] = (color >> 8) & 0xFF;  // Green
    rgb[2] = color & 0xFF;         // Blue

    return rgb;
}


void ledReward(String ledString){
  if(ledString != ""){
    std::vector<String> hexCodeArray = splitString(ledString, ';');
    std::array<std::array<uint32_t, 3>,12> hexInt;
    for(int i = 0; i< hexCodeArray.size(); i++){
      hexInt[i] = hexToRGB(hexCodeArray[i]);
    }
    showFigure(hexInt, 255);
  }
}

void musicReward(String musicString){
  if(musicString == ""){
    delay(1000);
  }
  else{
    std::vector<String> musicRewardString = splitString(musicString, ';');
    for(int i = 0; i < musicRewardString.size(); i++){
      int hzValue = musicRewardString[i].toInt();
      playsound(hzValue, 250);
    }
  }
  off();
}

void executeEx(){
  bool oefeningKlaar = false;
  if(incomingValue != "p"){
    std::array<int, 3> coHand = hand.gyroData();
    std::array<int, 3> coThumb = thumb.gyroData();
    std::array<int, 3> coFingers = fingers.gyroData();
    std::array<std::array<int, 3>, 3> co2D{coHand, coThumb, coFingers};

    for(int i = 0; i < oefeningen.size(); i++){
      if(boolArray[i] == true){
        if(oefeningen[i] == co2D[i]){
          oefeningKlaar = true;
          executeExBool = false;
          notifyExerciseDone();
        }
      }
    }
  }
  else{
    uint16_t fsrReading = analogRead(FSR); // analog reading from FSR
    Serial.println(fsrReading);
    if (fsrReading > 2500){
      oefeningKlaar = true;
      executeExBool = false;
      notifyExerciseDone();
    }
  }
}

class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};
class MyCharacteristicCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* onCharacteristic) {
    incomingValue = onCharacteristic->getValue();
    Serial.println(incomingValue.c_str());
    if (incomingValue.length() > 0) {
      if(incomingValue[0] == 'R'){
        std::string myString = incomingValue.substr(2);

        int indexOfH = myString.find('H');

        if (indexOfH != -1) {
          std::string beforeH = myString.substr(0, indexOfH);
          std::string afterH = myString.substr(indexOfH+1);
          Serial.println(beforeH.c_str());
          Serial.println(afterH.c_str());
          ledReward(afterH.c_str());
          musicReward(beforeH.c_str());
          notifyRewardDone();
        }
      }
      else{
        if(incomingValue != "p"){

          oefeningen =  toIntVector(incomingValue.c_str());
          for(int i= 0; i< boolArray.size(); i++){
            boolArray[i] = false;
          }
          for(int i = 0; i < oefeningen.size(); i++){
            for(int j = 0; j < oefeningen[i].size(); j++){
              if(oefeningen[i][j] != 0){
                boolArray[i] = true;
              }
            }
          }

          for(int i= 0; i< boolArray.size(); i++){
            Serial.println(boolArray[i]);
          }
        }
        executeExBool = true;
      }

    }
  }
};

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
  Serial.println("hand");
  hand.gyroSetup(0x69, Wire);
  Serial.println("thumb");
  thumb.gyroSetup(0x68, Wire);
  Serial.println("fingers");
  fingers.gyroSetup(0x68, Wire1);

    // Create the BLE Device
  BLEDevice::init("ESP32");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create the ON button Characteristic
  pLedCharacteristic = pService->createCharacteristic(
                      LED_CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_WRITE
                    );
  pNotificationCharacteristic = pService->createCharacteristic(
                      NOTIFICATION_CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // Register the callback for the ON button characteristic
  pLedCharacteristic->setCallbacks(new MyCharacteristicCallbacks());

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pLedCharacteristic->addDescriptor(new BLE2902());
  pNotificationCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");

  //showFigure(smiley, 50);
  //playsound(NOTE_C4, 250);
  //playsound(NOTE_E4, 250);
  //playsound(NOTE_G4, 250);
  //playsound(NOTE_C5, 250);
  //delay(1000);
  //off();
}

void loop(){
    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        Serial.println("Device disconnected.");
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("Start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
        Serial.println("Device Connected");
    }

    if(executeExBool == true){
      executeEx();
    }
}