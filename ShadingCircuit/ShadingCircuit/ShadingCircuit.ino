/*
A simple light follower
 
author: Arturo Guadalupi <a.guadalupi@arduino.cc>
 */
#include <Servo.h>
Servo myservo;
int A0_val; // bottom sensor
int A1_val; // top sensor
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
}
void loop() {
  A0_val = analogRead(A0); //reading data from sensors
  A1_val = analogRead(A1); 
  unsigned long currentMillis = millis();
  diff = abs(A1_val-A0_val); //checking the difference between the two sensors
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if ((A1_val > A0_val) && (diff > threshold))
      {
      if (val < 180) //if different from max val
        {
        val++;
        myservo.write(val);
        }
      }
    if((A0_val > A1_val) && (diff > threshold))
      {
      if (val > 0) //if different from min val
        {
        val--;
        myservo.write(val);
        }
      }
  }
}
