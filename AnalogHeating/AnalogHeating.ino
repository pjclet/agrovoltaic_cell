/*
*/

int tempsensorPin = PLACEHOLDER;    // select the input pin for the potentiometer
int heatingPin = PLACEHOLDER;      // select the pin for the heating
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
