#include <Wire.h>
#include "Adafruit_TCS34725.h"

//A4 = SDA (grey), A5 = SCL (blue)
const int RED_PIN = 3;
const int GREEN_PIN = 5;
const int BLUE_PIN = 6;

//Color Sensor
Adafruit_TCS34725 tcs1 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
/*
Adafruit_TCS34725 tcs2 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Adafruit_TCS34725 tcs3 = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
 */

void setup(){
  Serial.begin(9600);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  if(tcs1.begin()){
    Serial.println("Found sensor #1");
  } else {
    Serial.println("Sensor #1 not found... check connections!");
    while(1); //stop the program
  }
  /*
  if(tcs2.begin()){
    Serial.println("Found sensor #2");
  } else {
    Serial.println("Sensor #2 not found... check connections!");
    while(1); //stop the program
  }
  
  if(tcs3.begin()){
    Serial.println("Found sensor #3");
  } else {
    Serial.println("Sensor #3 not found... check connections!");
    while(1); //stop the program
  }
   */
}

void loop(){
  colorSensor(tcs1);
  /*
  colorSensor(tcs2);
  colorSensor(tcs3);
   */
}

void colorSensor(Adafruit_TCS34725 tcs){
  float red, green, blue;

  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRGB(&red, &green, &blue);
  
  tcs.setInterrupt(true);  // turn off LED

  Serial.print("R:\t"); Serial.print(int(red)); 
  Serial.print("\tG:\t"); Serial.print(int(green)); 
  Serial.print("\tB:\t"); Serial.print(int(blue));
  Serial.print("\n");

  if(red > green && red > blue && red > 145){
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
}

//RGB LED Test
void mainColors(){
  // Off (all LEDs off):
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  
  delay(1000);
  
  // Red (turn just the red LED on):
  
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  
  delay(1000);
  
  // Green (turn just the green LED on):
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  
  delay(1000);
  
  // Blue (turn just the blue LED on):
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  
  delay(1000);
  
  // Yellow (turn red and green on):
  
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
  
  delay(1000);
  
  // Cyan (turn green and blue on):
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  
  delay(1000);
  
  // Purple (turn red and blue on):
  
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  
  delay(1000);
  
  // White (turn all the LEDs on):
  
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);

  delay(1000);
}
