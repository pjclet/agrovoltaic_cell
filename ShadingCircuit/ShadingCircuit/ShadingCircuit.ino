/*
A simple light follower
 
author: Arturo Guadalupi <a.guadalupi@arduino.cc>
 */
#include <Servo.h>
Servo myservo;
int up_average;
int down_average;
int A0_val;
int A1_val;
int A2_val;
int A3_val;
int val = 90;
int diff;
const int threshold = PLACEHOLDER;
unsigned long previousMillis = 0; // will store last time servo was updated
const long interval = PLACEHOLDER;       // interval at which to update (milliseconds)
void setup() {
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  myservo.attach(PLACEHOLDER);
  myservo.write(val);
}
void loop() {
  A0_val = analogRead(A0); //reading data from sensors
  A1_val = analogRead(A1); 
  A2_val = analogRead(A2);
  A3_val = analogRead(A3);
  unsigned long currentMillis = millis();
  
  down_average = (A0_val + A1_val)/2; //the sum of the two lower sensors /2
  up_average = (A2_val + A3_val)/2;    //the sum of the two upper sensors /2
  diff = abs(up_average-down_average); //checking the difference between the two averages
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if ((up_average > down_average) && (diff > threshold))
      {
      if (val < 180) //if different from max val
        {
        val++;
        myservo.write(val);
        }
      }
    if((down_average > up_average) && (diff > threshold))
      {
      if (val > 0) //if different from min val
        {
        val--;
        myservo.write(val);
        }
      }
  }
}
