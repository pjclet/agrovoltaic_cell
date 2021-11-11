/*
A simple light follower
 
author: Arturo Guadalupi <a.guadalupi@arduino.cc>
 */
#include <Servo.h>
#include <BH1750.h>
#include <Wire.h>
BH1750 lightMeter1(0x23);
BH1750 lightMeter2(0x5C);
Servo myservo;
int lux1; // bottom sensor
int lux2; // top sensor
int val = 90;
int diff;
const int threshold = 50;
unsigned long previousMillis = 0; // will store last time servo was updated
const long interval = 1000;       // interval at which to update (milliseconds)
void setup() {
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  myservo.attach(11);
  myservo.write(val);
  Wire.begin();
  lightMeter1.begin();
  lightMeter2.begin();
}
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    float lux1 = lightMeter1.readLightLevel();
    float lux2 = lightMeter2.readLightLevel();
    diff = abs(lux1 - lux2); //checking the difference between the two sensors
    previousMillis = currentMillis;
    if ((lux2 > lux1) && (diff > threshold))
      {
      if (val < 180) //if different from max val
        {
        val++;
        myservo.write(val);
        }
      }
    if((lux1 > lux2) && (diff > threshold))
      {
      if (val > 0) //if different from min val
        {
        val--;
        myservo.write(val);
        }
      }
  }
}
