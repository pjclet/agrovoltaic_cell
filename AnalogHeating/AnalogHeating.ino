/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13 through 220 ohm resistor
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInput
*/

int tempsensorPin = A0;    // select the input pin for the potentiometer
int heatingPin = 13;      // select the pin for the heating
int tempsensorValue = 0;  // variable to store the value coming from the sensor


void setup() {
  
  pinMode(heatingPin, OUTPUT);// declare the ledPin as an OUTPUT:
}

void loop() {
  
  tempsensorValue = analogRead(tempsensorPin);// read the value from the sensor:
  if(tempsensorValue <= 65){
    digitalWrite(heatingPin,HIGH);
  }
  
  delay(tempsensorValue);// stop the program for <sensorValue> milliseconds:
  if(tempsensorValue >= 70){
    digitalWrite(heatingPin, LOW);// turn the heatingPin off:
  }
    delay(tempsensorValue);// stop the program for for <sensorValue> milliseconds:
}
