#include <Wire.h>
#include <Servo.h>
#include "Adafruit_TCS34725.h"
//#include "Adafruit_TCS34725softi2c.h"
//
//#define SDApin 12
//#define SCLpin 13

//A4 = SDA (grey), A5 = SCL (blue)
const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;

const int SERVO_PIN = 11;
Servo servo;

//Color Sensor Pins for Power
//const int SENSOR_A = 8;
//const int SENSOR_B = 9;
//const int SENSOR_C = 10;

//Color Sensor Addresses
const uint8_t SENSOR_A = 0x29;
const uint8_t SENSOR_B = 0x30;
const uint8_t SENSOR_C = 0x31;

Adafruit_TCS34725 tcs_A = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs_B = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs_C = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  

boolean isCorrect_R = false;
boolean isCorrect_G = false;
boolean isCorrect_B = false;

void setup(){
  Serial.begin(9600);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  servo.attach(SERVO_PIN);

//Sensor Pins Version
//  pinMode(SENSOR_A, OUTPUT);
//  pinMode(SENSOR_B, OUTPUT);
//  pinMode(SENSOR_C, OUTPUT);

//Sensor Address Version
  if(tcs_A.begin(SENSOR_A)){
    Serial.println("Sensor A is activated!");
  } else{
    Serial.println("Sensor A not found");
  }
  if(tcs_B.begin(SENSOR_B)){
    Serial.println("Sensor B is activated!");
  } else{
    Serial.println("Sensor B not found");
  }
  if(tcs_C.begin(SENSOR_C)){
    Serial.println("Sensor C is activated!");
  } else{
    Serial.println("Sensor C not found");
  }
}

void loop(){
  feedbackLED();

  if(isCorrect_R){
    servo.write(160);
    delay(1000);
  } else {
    servo.write(20);
    delay(1000);
  }
  
//Sensor Address Version
  colorSensorCheck(tcs_A, "R");
//  colorSensorCheck(tcs_B, "G");
//  colorSensorCheck(tcs_C, "B");

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

void feedbackLED(){
  if(isCorrect_R == true){
//     digitalWrite(RED_PIN, HIGH);
//     delay(50);
//     digitalWrite(RED_PIN, LOW);
//     delay(50);
//     digitalWrite(RED_PIN, HIGH);
//     delay(50);
//     digitalWrite(RED_PIN, LOW);
//     delay(50);
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

//Sensor Addresses Version
void colorSensorCheck(Adafruit_TCS34725 sensor, String color){
  float red, green, blue;

  sensor.setInterrupt(false);  // turn on the sensor LED

  delay(60);  // takes 50ms to read

  sensor.getRGB(&red, &green, &blue);
  
  sensor.setInterrupt(true);  // turn off the sensor LED

  if(color == "R"){
    if(red > green && red > blue && red > 135){
      isCorrect_R = true;
      Serial.println("Red");
    } else {
      isCorrect_R = false;
    }
  } else if(color == "G"){
    if(green > red && green > blue){
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
