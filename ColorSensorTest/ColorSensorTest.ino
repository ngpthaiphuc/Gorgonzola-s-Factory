#include <Wire.h>
#include <Servo.h>
#include "Adafruit_TCS34725.h"

//A4 = SDA (grey), A5 = SCL (blue)

//TCA Multiplexer:
#define TCAADDR 0x70

void tcaselect(uint8_t i){
  if(i > 7) return;

  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

//LEDs Pins (Comment out when you're ready for feedback)
const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;

//Offical LEDs for feedback (uncomment the code below and wire them accordingly. There are 6 LEDs, 3 red and 3 yellow because we have an abundance of those. Just wire them accordingly to the port.
//Make sure to add resistor for ground. Go down and uncomment more stuff)
//const int YAY_A = 3;
//const int NOPE_A = 4;
//const int YAY_B = 6;
//const int NOPE_B = 7;
//const int YAY_C = 8;
//const int NOPE_C = 9;

//Servo for Barrier
//const int SERVO_PIN = 11;
//Servo servo;

//Color Sensor Pins for Power
//const int SENSOR_A = 8;
//const int SENSOR_B = 9;
//const int SENSOR_C = 10;

//Color Sensor Ports
const uint8_t SENSOR_A = 3;
const uint8_t SENSOR_B = 5;
const uint8_t SENSOR_C = 7;

Adafruit_TCS34725 tcs_A = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs_B = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs_C = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  

//Based on the output of the color sensors
boolean isCorrect_R = false;
boolean isCorrect_G = false;
boolean isCorrect_B = false;

void setup(){
  Serial.begin(115200);
  Serial.println("Setting up");

  //Comment out when you're ready for feedback
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  //Uncomment out when LEDs for feedback is wired (there are more to comment/uncomment below)
//  pinMode(YAY_A, OUTPUT);
//  pinMode(NOPE_A, OUTPUT);
//  pinMode(YAY_B, OUTPUT);
//  pinMode(NOPE_B, OUTPUT);
//  pinMode(YAY_C, OUTPUT);
//  pinMode(NOPE_C, OUTPUT);

//  servo.attach(SERVO_PIN);

  //Sensor Ports Version
  tcaselect(SENSOR_A);
//  Serial.println("Selecting");
  if(tcs_A.begin()){
    Serial.println("Sensor A is activated @ Port 3");
  } else{
    Serial.println("Sensor A not found");
  }
  tcaselect(SENSOR_B);
  if(tcs_B.begin()){
    Serial.println("Sensor B is activated! @ Port 5");
  } else{
    Serial.println("Sensor B not found");
  }
  tcaselect(SENSOR_C);
  if(tcs_C.begin()){
    Serial.println("Sensor C is activated! @ Port 7");
  } else{
    Serial.println("Sensor C not found");
  }
  
  //Sensor Pins Version
//  pinMode(SENSOR_A, OUTPUT);
//  pinMode(SENSOR_B, OUTPUT);
//  pinMode(SENSOR_C, OUTPUT);
}

void loop(){
  //Comment out LEDTest(); and uncomment feedbackLED();
  //LEDTest -> Red LED turns on if it detects red, green if green, etc.
  LEDTest();
  //feedbackLED -> If the right color is placed in front of a sensor, the LED turns from red to yellow! Else it will stay red
  //feedbackLED();

//  if(isCorrect_R && isCorrect_G && isCorrect_B){
//    servo.write(160);
//    Serial.println("Yeet");
//  } else {
//    servo.write(20);
//  }
  
  //Sensor Ports Version
  colorSensorCheck(tcs_A, SENSOR_A, "R");
  colorSensorCheck(tcs_B, SENSOR_B, "G");
  colorSensorCheck(tcs_C, SENSOR_C, "B");

  //Sensor Pins Version  
//  for(int i = 0; i < 5; i++){
//    colorSensorCheck(SENSOR_A, "R");
//  }
//  delay(500);
//  digitalWrite(SENSOR_A, LOW);
//
//  for(int i = 0; i < 5; i++){
//    colorSensorCheck(SENSOR_B, "G");
//  }
//  delay(500);
//  digitalWrite(SENSOR_B, LOW);
//    
//  for(int i = 0; i < 5; i++){
//    colorSensorCheck(SENSOR_C, "B");
//  }
//  delay(500);
//  digitalWrite(SENSOR_C, LOW);
}

//Comment this whole method out (ctrl + /)
void LEDTest(){
  if(isCorrect_R == true){
     digitalWrite(RED_PIN, HIGH);
  } else{
    digitalWrite(RED_PIN, LOW);
  }
  if(isCorrect_G == true){
    digitalWrite(GREEN_PIN, HIGH);
  } else{
    digitalWrite(GREEN_PIN, LOW);
  }
  if(isCorrect_B == true){
    digitalWrite(BLUE_PIN, HIGH);
  } else{
    digitalWrite(BLUE_PIN, LOW);
  }
}

//Last thing to uncomment!
//void feedbackLED(){
//  if(isCorrect_R == true){
//    digitalWrite(NOPE_A, LOW);
//    digitalWrite(YAY_A, HIGH);
//  } else{
//    digitalWrite(YAY_A, LOW);
//    digitalWrite(NOPE_A, HIGH);
//  }
//  if(isCorrect_G == true){
//    digitalWrite(NOPE_B, LOW);
//    digitalWrite(YAY_B, HIGH);
//  } else{
//    digitalWrite(YAY_B, LOW);
//    digitalWrite(NOPE_B, HIGH);
//  }
//  if(isCorrect_B == true){
//    digitalWrite(NOPE_C, LOW);
//    digitalWrite(YAY_C, HIGH);
//  } else{
//    digitalWrite(YAY_C, LOW);
//    digitalWrite(NOPE_C, HIGH);
//  }
//}

//Sensor Ports Version
void colorSensorCheck(Adafruit_TCS34725 sensor, uint8_t port, String color){
  float red, green, blue;

  tcaselect(port);
  // turn on the sensor LED
  sensor.setInterrupt(false);
  delay(50);
  //Get the RGB value from the sensor
  sensor.getRGB(&red, &green, &blue);
  // turn off the sensor LED
  sensor.setInterrupt(true);

  if(color == "R"){
    if(red > green && red > blue && red > 92){//92
      isCorrect_R = true;
      Serial.println("Red");
    } else {
      isCorrect_R = false;
    }
  } else if(color == "G"){
    if(green > red && green > blue && green > 95){//95
      isCorrect_G = true;
      Serial.println("Green");
    } else {
      isCorrect_G = false;
    }
  } else if(color == "B"){
    if(blue > red && blue > green){
      isCorrect_B = true;
      Serial.println("Blue");
    } else {
      isCorrect_B = false;
    }
  }
//  Serial.print("R:\t"); Serial.print(int(red)); 
//  Serial.print("\tG:\t"); Serial.print(int(green)); 
//  Serial.print("\tB:\t"); Serial.print(int(blue));
//  Serial.print("\n");
}

//Sensor Pins Version
//void colorSensorCheck(int sensorPin, String color){
//  Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
//
//  digitalWrite(sensorPin, HIGH);
//
//  if(tcs.begin()){
//    float red, green, blue;
//
//    tcs.setInterrupt(false);  // turn on the sensor LED
//  
//    delay(60);  // takes 50ms to read
//  
//    tcs.getRGB(&red, &green, &blue);
//    
//    tcs.setInterrupt(true);  // turn off the sensor LED
//  
//    if(color == "R"){
//      if(red > green && red > blue && red > 135){
//        isCorrect_R = true;
//        Serial.println("Red");
//      } else {
//        isCorrect_R = false;
//      }
//    } else if(color == "G"){
//      if(green > red && green > blue){
//        isCorrect_G = true;
//        Serial.println("Green");
//      } else {
//        isCorrect_G = false;
//      }
//    } else if(color == "B"){
//      if(blue > red && blue > green){
//        isCorrect_B = true;
//        Serial.println("Blue");
//      } else {
//        isCorrect_B = false;
//      }
//    }
//  } else{
//    Serial.println("Sensor not detected :(");
//  }
//}
//
//void colorSensorTest(int sensorPin, String sensorName){
//  Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
//
//  digitalWrite(sensorPin, HIGH);
//
//  if(tcs.begin()){
//    float red, green, blue;
//  
//    tcs.setInterrupt(false);  // turn on LED
//  
//    delay(60);  // takes 50ms to read
//  
//    tcs.getRGB(&red, &green, &blue);
//    
//    tcs.setInterrupt(true);  // turn off LED
//  
//    Serial.print("R:\t"); Serial.print(int(red)); 
//    Serial.print("\tG:\t"); Serial.print(int(green)); 
//    Serial.print("\tB:\t"); Serial.print(int(blue));
//    Serial.print("\n");
//    
////    if(red > green && red > blue && red > 135){
////      digitalWrite(RED_PIN, HIGH);
////      digitalWrite(BLUE_PIN, LOW);
////      digitalWrite(GREEN_PIN, LOW);
////    } else if(blue > red && blue > green){
////      digitalWrite(BLUE_PIN, HIGH);
////      digitalWrite(RED_PIN, LOW);
////      digitalWrite(GREEN_PIN, LOW);
////    } else if (green > red && green > blue){
////      digitalWrite(GREEN_PIN, HIGH);
////      digitalWrite(RED_PIN, LOW);
////      digitalWrite(BLUE_PIN, LOW);
////    } else{
////      digitalWrite(RED_PIN, LOW);
////      digitalWrite(BLUE_PIN, LOW);
////      digitalWrite(GREEN_PIN, LOW);
////    }
//  } else {
//    Serial.println(sensorName + " not found... check connections!");
//  }
//}
