/*
A simple light follower
 
author: Arturo Guadalupi <a.guadalupi@arduino.cc>
 */
#include <Servo.h>
#include <BH1750_WE.h>
#include <Wire.h>
BH1750_WE lightMeter1(0x5C);
BH1750_WE lightMeter2(0x23);
Servo myservo;
int lux1; // bottom sensor
int lux2; // top sensor
int val = 90;
int diff;
const int threshold = 50;
unsigned long previousMillis = 0; // will store last time servo was updated
const long interval = 1000;       // interval at which to update (milliseconds)
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  myservo.attach(11);
  myservo.write(val);
  Wire.begin();
    lightMeter1.init();
    lightMeter2.init();
}
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    float lux1 = lightMeter1.getLux();
    float lux2 = lightMeter2.getLux();
    Serial.print(lux1);
    Serial.print("  ");
    Serial.print(lux2);
    diff = abs(lux1 - lux2); //checking the difference between the two sensors
    previousMillis = currentMillis;
    if ((lux2 > lux1) && (diff > threshold))
      {
      if (val < 174) //if different from max val
        {
        val+=5;
        myservo.write(val);
        }
      }
    if((lux1 > lux2) && (diff > threshold))
      {
      if (val > 6) //if different from min val
        {
        val-=5;
        myservo.write(val);
        }
      }
    Serial.println();
  }
}
