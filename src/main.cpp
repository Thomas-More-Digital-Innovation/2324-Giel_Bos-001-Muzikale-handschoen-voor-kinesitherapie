// - INCLUDES - //
#include <Arduino.h>                 // arduino core
#include <Adafruit_NeoPixel.h>       // neopixel library for ledring
#include <SD.h>                      // sd card library
#include <SPI.h>                     // spi library for sd card

#include <vector>                    // library for dynamic array (vector)
#include <string>
using namespace std;

// - DEFINES - //
// -- music notes -- //
#define NOTE_C4 262
#define NOTE_E4 330
#define NOTE_G4 392
#define NOTE_C5 523

#define FSR 36   // pin for force sensor

// -- pins for feedback modules -- //
#define PIN_LED 15 // pin for neopixel ledring
#define PIN_BUZ 12 // pin for buzzer module
#define PIN_SND 27 // pin for sound module

// -- other defines -- //
Adafruit_NeoPixel ring = Adafruit_NeoPixel(12, PIN_LED, NEO_GRB + NEO_KHZ800); // define ledring



// - FEEDBACK MODULES - //
// -- ledring -- //
// --- turn all leds off --- //
void ledsoff()
{
  ring.setBrightness(50);
  for (int i = 0; i < 12; i++)
  {
    ring.setPixelColor(i, 0, 0, 0);
  }
  ring.show();
}

void smiley() {
  ring.setBrightness(50);
  ring.setPixelColor(6, 5, 213, 250); // left eye
  ring.setPixelColor(8, 5, 213, 250); // right eye
  ring.setPixelColor(10, 5, 213, 250);
  ring.setPixelColor(11, 5, 213, 250);
  ring.setPixelColor(0, 5, 213, 250);
  ring.setPixelColor(1, 5, 213, 250);
  ring.setPixelColor(2, 5, 213, 250);
  ring.setPixelColor(3, 5, 213, 250);
  ring.setPixelColor(4, 5, 213, 250);
  ring.show();
}

// -- sound module -- //
// --- play note for a certain duration --- //
void playsound(int note, int duration)
{
  pinMode(PIN_SND, OUTPUT); // sound pin is output
  int length = 1000 / duration;
  tone(PIN_SND, note, duration);
}

// -- buzzer -- //
// --- vibrate for a certain duration --- //
void vibrate(int duration)
{
  pinMode(PIN_BUZ, OUTPUT); // buzzer pin is output
  digitalWrite(12, HIGH);
  delay(duration);
  digitalWrite(12, LOW);
}

// -- combinated feedback -- //
// --- sensors succesfully initiated --- //
void sensorsucces()
{
  pinMode(12, OUTPUT); // buzzer pin is output
  ring.setBrightness(50);
  ring.setPixelColor(6, 5, 213, 250);
  ring.show();
  playsound(NOTE_E4, 8);
  delay(100);
}

// --- sd succesfully loaded --- //
void sdsucces()
{
  pinMode(12, OUTPUT); // buzzer pin is output
  ring.setBrightness(50);
  ring.setPixelColor(8, 5, 213, 250);
  ring.show();
  playsound(NOTE_C, 8);
  delay(100);
}

// --- ready to go --- //
void readysucces()
{
  pinMode(12, OUTPUT); // buzzer pin is output

  ring.setBrightness(50);
  ring.setPixelColor(4, 5, 213, 250);
  ring.show();
  playsound(NOTE_E4, 16);
  delay(100);

  ring.setPixelColor(3, 5, 213, 250);
  ring.show();
  playsound(NOTE_G4, 16);
  delay(100);

  ring.setPixelColor(2, 5, 213, 250);
  ring.show();
  playsound(NOTE_C4, 16);
  delay(100);

  ring.setPixelColor(1, 5, 213, 250);
  ring.show();
  playsound(NOTE_E4, 16);
  delay(100);

  ring.setPixelColor(0, 5, 213, 250);
  ring.show();
  playsound(NOTE_C4, 16);
  delay(100);

  ring.setPixelColor(11, 5, 213, 250);
  ring.show();
  playsound(NOTE_G4, 16);
  delay(100);

  ring.setPixelColor(10, 5, 213, 250);
  ring.show();
  playsound(NOTE_C5, 16);
  delay(500);

  ring.setPixelColor(8, 0, 0, 0);
  ring.show();
  playsound(NOTE_C5, 16);
  delay(200);

  ring.setPixelColor(8, 5, 213, 250);
  ring.show();
  playsound(NOTE_C5, 16);
  delay(500);
}

void alldone() {
  int a = 6; // left eye
  int b = 8; // right eye
  int c = 10;
  int d = 11;
  int e = 0;
  int f = 1;
  int g = 2;
  int h = 3;
  int i = 4;

  ring.setBrightness(50);
  ring.setPixelColor(a, 5, 213, 250); // left eye
  ring.setPixelColor(b, 5, 213, 250); // right eye
  ring.setPixelColor(c, 5, 213, 250);
  ring.setPixelColor(d, 5, 213, 250);
  ring.setPixelColor(e, 5, 213, 250);
  ring.setPixelColor(f, 5, 213, 250);
  ring.setPixelColor(g, 5, 213, 250);
  ring.setPixelColor(h, 5, 213, 250);
  ring.setPixelColor(i, 5, 213, 250);
  ring.show();

  for (int z = 0; z < 12; z++)
  {
    ring.setPixelColor(((a+z) % 12), 5, 213, 250); // left eye
    ring.setPixelColor(((b+z) % 12), 5, 213, 250); // right eye
    ring.setPixelColor(((c+z) % 12), 5, 213, 250);
    ring.setPixelColor(((d+z) % 12), 5, 213, 250);
    ring.setPixelColor(((e+z) % 12), 5, 213, 250);
    ring.setPixelColor(((f+z) % 12), 5, 213, 250);
    ring.setPixelColor(((g+z) % 12), 5, 213, 250);
    ring.setPixelColor(((h+z) % 12), 5, 213, 250);
    ring.setPixelColor(((i+z) % 12), 5, 213, 250);
    ring.show();
    delay(100);
    ledsoff();
  }
}

// --- exercise succesfull --- //
void exsucces()
{
  ring.setBrightness(50);
  ring.setPixelColor(6, 5, 213, 250);
  ring.setPixelColor(0, 5, 213, 250);
  ring.setPixelColor(1, 5, 213, 250);
  ring.setPixelColor(2, 5, 213, 250);
  ring.setPixelColor(8, 5, 213, 250);
  ring.show();
  playsound(NOTE_E4, 8);
  // vibrate(200);
  delay(100);
  ring.setPixelColor(11, 5, 213, 250);
  ring.setPixelColor(3, 5, 213, 250);
  ring.show();
  playsound(NOTE_C4, 8);
  // vibrate(200);
  delay(100);
  ring.setPixelColor(10, 5, 213, 250);
  ring.setPixelColor(4, 5, 213, 250);
  ring.show();
  playsound(NOTE_C5, 8);
  // vibrate(200);
  delay(100);
}

void deepsleep(){
  // wake up when pin 36 is high input
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_36, 1);
  // go to sleep
  esp_deep_sleep_start();
}

bool isNumber(String s){
  
  if(s.length() > 0){
    bool result = true;
    for(int i=0; i < s.length(); i++){
      Serial.println(s.charAt(i));
      if(isDigit(s.charAt(i)) == false){
        result = false;
      }
    }
    return result;
  }
  else{
    return false;
  }
}

void setup()
{

  sensorsucces();


  sdsucces();
  delay(500);
  readysucces();
  delay(500);
  ledsoff();
  delay(1000);
}

bool toggle;                       // toggle variable used for escaping while-loop when exercise is executed succesfully
array<array<int, 3>, 3> currentex; // variable for storing exercise to be executed

void loop()
{

      if (exercises[i] == 0) // force sensor exercise
      {
        uint16_t fsrReading = analogRead(FSR); // analog reading from FSR
        if (fsrReading > 2500)
        {
          exsucces();
          delay(500);
          ledsoff();
          Serial.println("SUCCES, ONTO THE NEXT EXERCISE!");
          toggle = false;
        }
        else
        {
          Serial.println("NOT QUIET RIGHT, PLEASE TRY AGAIN!");
        }
        delay(1000);
      }
    }
  }
  alldone();
  alldone();
  smiley();
  delay(500);
  ring.setPixelColor(8, 0, 0, 0);
  ring.show();
  playsound(NOTE_C5, 16);
  delay(200);
  ring.setPixelColor(8, 5, 213, 250);
  ring.show();
  playsound(NOTE_C5, 16);
  delay(2000);
  ledsoff();
  deepsleep();
}