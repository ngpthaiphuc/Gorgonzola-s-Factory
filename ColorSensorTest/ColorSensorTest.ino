#include <Wire.h>
#include "Adafruit_TCS34725.h"
//#include "Adafruit_TCS34725softi2c.h"

//A4 = SDA (grey), A5 = SCL (blue)
const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;

//Color Sensor Pins for Power
const int SENSOR_A = 8;
const int SENSOR_B = 9;
const int SENSOR_C = 10;

boolean isCorrect_R = false;
boolean isCorrect_G = false;
boolean isCorrect_B = false;

void setup(){
  Serial.begin(9600);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);

  pinMode(SENSOR_A, OUTPUT);
  pinMode(SENSOR_B, OUTPUT);
  pinMode(SENSOR_C, OUTPUT);
}

void loop(){
  
  for(int i = 0; i < 5; i++){
    colorSensorCheck(SENSOR_A, "R");
  }
  delay(500);
  digitalWrite(SENSOR_A, LOW);

  for(int i = 0; i < 5; i++){
    colorSensorCheck(SENSOR_B, "G");
  }
  delay(500);
  digitalWrite(SENSOR_B, LOW);
  
  //colorSensor(SENSOR_C, "B");
}

void colorSensorCheck(int sensorPin, String color){
  Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

  digitalWrite(sensorPin, HIGH);

  if(tcs.begin()){
    float red, green, blue;

    tcs.setInterrupt(false);  // turn on LED
  
    delay(60);  // takes 50ms to read
  
    tcs.getRGB(&red, &green, &blue);
    
    tcs.setInterrupt(true);  // turn off LED
  
    if(red > green && red > blue && red > 135 && color == "R"){
      digitalWrite(RED_PIN, HIGH);
      isCorrect_R = true;
      Serial.println("Red");
    } else if (green > red && green > blue && color == "G"){
      digitalWrite(GREEN_PIN, HIGH);
      isCorrect_G = true;
      Serial.println("Green");
    } else if(blue > red && blue > green && color == "B"){
      digitalWrite(BLUE_PIN, HIGH);
      isCorrect_B = true;
      Serial.println("Blue");
    }
  } else{
    Serial.println("Sensor not detected :(");
  }
}

void colorSensorTest(int sensorPin, String sensorName){
  Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

  digitalWrite(sensorPin, HIGH);

  if(tcs.begin()){
    float red, green, blue;
  
    tcs.setInterrupt(false);  // turn on LED
  
    delay(60);  // takes 50ms to read
  
    tcs.getRGB(&red, &green, &blue);
    
    tcs.setInterrupt(true);  // turn off LED
  
    Serial.print("R:\t"); Serial.print(int(red)); 
    Serial.print("\tG:\t"); Serial.print(int(green)); 
    Serial.print("\tB:\t"); Serial.print(int(blue));
    Serial.print("\n");
  
    if(red > green && red > blue && red > 135){
      digitalWrite(RED_PIN, HIGH);
      digitalWrite(BLUE_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
    } else if(blue > red && blue > green){
      digitalWrite(BLUE_PIN, HIGH);
      digitalWrite(RED_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
    } else if (green > red && green > blue){
      digitalWrite(GREEN_PIN, HIGH);
      digitalWrite(RED_PIN, LOW);
      digitalWrite(BLUE_PIN, LOW);
    } else{
      digitalWrite(RED_PIN, LOW);
      digitalWrite(BLUE_PIN, LOW);
      digitalWrite(GREEN_PIN, LOW);
    }
  } else {
    Serial.println(sensorName + " not found... check connections!");
  } 
}
