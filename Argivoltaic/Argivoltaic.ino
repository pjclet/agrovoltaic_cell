#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>
#include <BH1750_WE.h>
#include <Wire.h>
// timer for all sybsystems
const long interval = 1000; // how often subsystems are updated
unsigned long prevMillis = 0; // when subsystems were last updated
unsigned long currentMillis = 0; // time since start

// heater subsystem
#define ONE_WIRE_BUS 3 // Data wire is conntec to the Arduino digital pin 3
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature sensor 
const int heaterPin =  4;// heater pin number
const int cold = 27; // when temperature drops below this, turn heater on
const int hot = 29; // when temperature rises above this, turn heater off
int heaterState = LOW; // whether heating is on or not
int temp; // temperature sensor readout
const long failsafeHeaterOn = 5000; // how long heater can stay on if temp sensor is unresponsive (millis)
const long failsafeHeaterOff = 5000; // how long heater must stay off if temp sensor is unresponsive (millis)
unsigned long heaterOffMillis = 0; // when heater turned off
unsigned long heaterOnMillis = 0; // when heater turned on

// shading subsystem
BH1750_WE lightMeter1(0x5C);
BH1750_WE lightMeter2(0x23);
Servo myservo;
int lux1; // bottom sensor
int lux2; // top sensor
int servoPos = 90; // starting servo posiiton
int luxDiff; // difference in lux reading
const int threshold = 50; // change angle when diff>threshold
const int increment = 5; // change in servo angle per loop

// watering system
int moisturePin = 0;    // input pin for the Soil moisture sensor
int pumpPin = 9;      // pin that controls pump
int moistureValue = 0;  // variable to store the value coming from the sensor
int moistureVCC = 10;   // moisutre sensor connected to digital pin for power so it can be turned on/off
int moistureState = LOW; // moisture sensor will be turned on/off
const int moistureDuration = 100; // how long mousture sensor takes to read a value
const int dry = 30; // when moisture drops below this, turn pump on
const int wet = 50; // when moisutre rises above this, turn pump off
int pumpState = LOW; // whether pump is on/off

void setup() {
  Serial.begin(9600);
  // heater setup
  sensors.begin();
  pinMode(heaterPin, OUTPUT);
  // shading setup
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  myservo.attach(11);
  myservo.write(servoPos);
  Wire.begin();
  lightMeter1.init();
  lightMeter2.init();
  // watering setup
  pinMode(moistureVCC, OUTPUT); 
  pinMode(pumpPin, OUTPUT);
  digitalWrite(moistureVCC, moistureState);
}

void loop() {
  currentMillis = millis();
  if(currentMillis - prevMillis > interval){
    prevMillis = currentMillis;
    // heater loop
    heater();
    // shading loop
    shading();
    // moisture loop
    moisture();
  }
  if((currentMillis - prevMillis > interval - moistureDuration) and (moistureState == LOW)){
    moistureState = HIGH;
    digitalWrite(moistureVCC, moistureState);
  }
}

void heater(){
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);
  if ((temp < cold) and (currentMillis-heaterOffMillis>failsafeHeaterOff)) {
    if(heaterState == LOW){
      heaterOnMillis = currentMillis;
    }
    heaterState = HIGH;
  }
  if ((temp > hot) or (currentMillis-heaterOnMillis>failsafeHeaterOn)) {
    if(heaterState == HIGH){
      heaterOffMillis = currentMillis;
    }
    heaterState = LOW;
  }
  digitalWrite(heaterPin, heaterState);
}

void shading(){
  float lux1 = lightMeter1.getLux();
  float lux2 = lightMeter2.getLux();
  luxDiff = abs(lux1 - lux2);
  if(pumpState == HIGH){
    servoPos = 90;
    myservo.write(servoPos);
  } else {
    if ((lux2 > lux1) && (luxDiff > threshold)) {
      if (servoPos < 179-increment) { //avoid setting servo above its max
        servoPos+=increment;
        myservo.write(servoPos);
      }
    }
    if((lux1 > lux2) && (luxDiff > threshold)) {
      if (servoPos > 1+increment) { //avoid setting servo below its min
        servoPos-=increment;
        myservo.write(servoPos);
      }
    }
  }
}

void moisture(){
  moistureValue = analogRead(moisturePin);  
  moistureState = LOW;
  digitalWrite(moistureVCC, moistureState); //stop power 
  if (moistureValue < dry) {
    pumpState = HIGH;
    digitalWrite(pumpPin, pumpState);        
  }
  if (moistureValue > wet) {
    pumpState = LOW;
    digitalWrite(pumpPin, pumpState);
  }
}
