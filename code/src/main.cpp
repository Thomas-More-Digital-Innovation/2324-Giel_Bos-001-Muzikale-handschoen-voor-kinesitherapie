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

// -- positions -- //
// --- wrist positions --- //
array<int, 3> hand_up{0, 0, -1}; // palm up
array<int, 3> hand_l{0, 1, 0};   // palm left
array<int, 3> hand_dn{0, 0, 1};  // palm down
array<int, 3> hand_r{0, -1, 0};  // palm right
array<int, 3> hand_fw{1, 0, 0};  // palm forward
array<int, 3> hand_bw{-1, 0, 0}; // palm backward

// --- thumb positions (always combined with hand_l) --- //
array<int, 3> thumb_dn{0, 1, 0}; // thumb flat
array<int, 3> thumb_up{1, 0, 0}; // thumb up

// --- fingers positions (always combined with hand_up or hand_dn) --- //
array<int, 3> fingers_flat_dn{0, 0, 1};  // fingers flat (hand_dn)
array<int, 3> fingers_bend_dn{-1, 0, 0}; // fingers bent (hand_dn)

array<int, 3> fingers_flat_up{0, 0, -1}; // fingers flat (hand_up)
array<int, 3> fingers_bend_up{1, 0, 0};  // fingers bent (hand_up)

// --- combined positions (always combined with hand_up or hand_dn) --- //
array<int, 3> thumb_fist_dn{0, -1, 0};   // fingers fist (hand_dn)
array<int, 3> fingers_fist_dn{-1, 0, 0}; // fingers fist (hand_dn)

array<int, 3> thumb_fist_up{0, 1, 0};   // fingers fist (hand_up)
array<int, 3> fingers_fist_up{1, 0, 0}; // fingers fist (hand_up)

// --- free position (used when position isn't relevant) --- //
array<int, 3> free_pos{0, 0, 0}; // free position

// -- exercises -- //
// --- single positions --- //
array<array<int, 3>, 3> ex1 = {hand_up, free_pos, free_pos}; // exercise 1
array<array<int, 3>, 3> ex2 = {hand_l, free_pos, free_pos};  // exercise 2
array<array<int, 3>, 3> ex3 = {hand_dn, free_pos, free_pos}; // exercise 3
array<array<int, 3>, 3> ex4 = {hand_r, free_pos, free_pos};  // exercise 4
array<array<int, 3>, 3> ex5 = {hand_fw, free_pos, free_pos}; // exercise 5
array<array<int, 3>, 3> ex6 = {hand_bw, free_pos, free_pos}; // exercise 6

// --- double positions --- //
array<array<int, 3>, 3> ex7{hand_l, thumb_dn, free_pos}; // exercise 7
array<array<int, 3>, 3> ex8{hand_l, thumb_up, free_pos}; // exercise 8

array<array<int, 3>, 3> ex9{hand_dn, free_pos, fingers_flat_dn};  // exercise 9
array<array<int, 3>, 3> ex10{hand_dn, free_pos, fingers_bend_dn}; // exercise 10

array<array<int, 3>, 3> ex11{hand_up, free_pos, fingers_flat_up}; // exercise 11
array<array<int, 3>, 3> ex12{hand_up, free_pos, fingers_bend_up}; // exercise 12

// --- triple positions --- //
array<array<int, 3>, 3> ex13{hand_dn, thumb_fist_dn, fingers_fist_dn}; // exercise 13
array<array<int, 3>, 3> ex14{hand_up, thumb_fist_up, fingers_fist_up}; // exercise 14

// switch function used for linking input numbers to exercises
array<array<int, 3>, 3> selectex(int ex_nr)
{
  switch (ex_nr)
  {
  case 1:
    return ex1;
    break;
  case 2:
    return ex2;
    break;
  case 3:
    return ex3;
    break;
  case 4:
    return ex4;
    break;
  case 5:
    return ex5;
    break;
  case 6:
    return ex6;
    break;
  case 7:
    return ex7;
    break;
  case 8:
    return ex8;
    break;
  case 9:
    return ex9;
    break;
  case 10:
    return ex10;
    break;
  case 11:
    return ex11;
    break;
  case 12:
    return ex12;
    break;
  case 13:
    return ex13;
    break;
  case 14:
    return ex14;
    break;
  default:
    return ex1;
    break;
  }
}

// converts sensor readings to 1, -1 or 0
int conv(int input)
{
  if (input < -7)
  {
    return -1;
  }
  else if (input > 7)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

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
  Serial.begin(115200);      // open serial monitor
  pinMode(14, OUTPUT);       // pin 14 is output pin
  digitalWrite(14, HIGH);    // pin 14 output high (used for changing I2C address gyro hand)
  Wire.begin(SDA_1, SCL_1);  // I2C bus 1
  Wire1.begin(SDA_2, SCL_2); // I2C bus 2

  while (!Serial)
    delay(10); // pause until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // initialize gyro hand
  if (!mpu_hand.begin(0x69, &Wire))
  {
    Serial.println("Failed to find MPU6050 hand gyro");
    while (1)
    {
      delay(1000);
    }
  }
  Serial.println("MPU6050 hand -- Found!");

  // initialize gyro thumb
  if (!mpu_thumb.begin(0x68, &Wire))
  {
    Serial.println("Failed to find MPU6050 thumb gyro");
    while (1)
    {
      delay(1000);
    }
  }
  Serial.println("MPU6050 thumb -- Found!");

  // initialize gyro fingers
  if (!mpu_fingers.begin(0x68, &Wire1))
  {
    Serial.println("Failed to find MPU6050 fingers gyro");
    while (1)
    {
      delay(1000);
    }
  }
  Serial.println("MPU6050 fingers -- Found!");

  // Setting accelerometer ranges - hand
  mpu_hand.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu_hand.getAccelerometerRange())
  {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  // Setting accelerometer ranges - thumb
  mpu_thumb.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu_thumb.getAccelerometerRange())
  {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  // Setting accelerometer ranges - fingers
  mpu_fingers.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu_fingers.getAccelerometerRange())
  {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  // Setting gyro ranges - hand
  mpu_hand.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu_hand.getGyroRange())
  {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  // Setting gyro ranges - thumb
  mpu_thumb.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu_thumb.getGyroRange())
  {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  // Setting gyro ranges - fingers
  mpu_fingers.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu_fingers.getGyroRange())
  {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  // filtering bandwidth - hand
  mpu_hand.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu_hand.getFilterBandwidth())
  {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  // filtering bandwidth - thumb
  mpu_thumb.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu_thumb.getFilterBandwidth())
  {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  // filtering bandwidth - fingers
  mpu_fingers.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu_fingers.getFilterBandwidth())
  {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  sensorsucces();

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
    Serial.println("/oefeningen.txt");
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      String input = "";
      //read every line of the file and save it in a temporary variable of type String
      input = myFile.readStringUntil('\n'); 
      input.trim(); // Removes '\n' character
      if(isNumber(input) == true){    //checks if the line of the file is a number
        exercises.push_back(input.toInt());   // if it is a number it will write it to excersises with a type int
      }
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }


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
  Serial.print("Number of exercises: ");
  Serial.println(exercises.size());
  for (int i = 0; i < exercises.size(); i++) // for every exercise
  {
    Serial.print("Current exercise: ");
    Serial.println(exercises[i]);
    currentex = selectex(exercises[i]);
    toggle = true;
    while (toggle)
    {
      // provide sensor event
      sensors_event_t a_hand, g_hand, temp_hand;
      sensors_event_t a_thumb, g_thumb, temp_thumb;
      sensors_event_t a_fingers, g_fingers, temp_fingers;

      // get acceleration, angular velocity and temperature from sensors (only acceleration is used)
      mpu_hand.getEvent(&a_hand, &g_hand, &temp_hand);
      mpu_thumb.getEvent(&a_thumb, &g_thumb, &temp_thumb);
      mpu_fingers.getEvent(&a_fingers, &g_fingers, &temp_fingers);

      // get x,y,z acceleration from hand sensor, convert & store in array
      int x_hand = conv((int)a_hand.acceleration.x);
      int y_hand = conv((int)a_hand.acceleration.y);
      int z_hand = conv((int)a_hand.acceleration.z);
      std::array<int, 3> co_hand{x_hand, y_hand, z_hand};

      // get x,y,z acceleration from thumb sensor, convert & store in array
      int x_thumb = conv((int)a_thumb.acceleration.x);
      int y_thumb = conv((int)a_thumb.acceleration.y);
      int z_thumb = conv((int)a_thumb.acceleration.z);
      std::array<int, 3> co_thumb{x_thumb, y_thumb, z_thumb};

      // get x,y,z acceleration from fingers sensor, convert & store in array
      int x_fingers = conv((int)a_fingers.acceleration.x);
      int y_fingers = conv((int)a_fingers.acceleration.y);
      int z_fingers = conv((int)a_fingers.acceleration.z);
      std::array<int, 3> co_fingers{x_fingers, y_fingers, z_fingers};

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
      else if (exercises[i] > 0 && exercises[i] < 7) // single positions
      {
        if (co_hand == currentex[0])
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
      else if (exercises[i] > 6 && exercises[i] < 9) // double positions - thumb exercises
      {
        if (co_hand == currentex[0] && co_thumb == currentex[1])
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
      else if (exercises[i] > 8 && exercises[i] < 13) // double positions - fingers exercises
      {
        if (co_hand == currentex[0] && co_fingers == currentex[2])
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
      else if (exercises[i] > 12 && exercises[i] < 15) // triple positions
      {
        if (co_hand == currentex[0] && co_thumb == currentex[1] && co_fingers == currentex[2])
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