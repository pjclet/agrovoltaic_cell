/*
  Blink without Delay

  Turns on and off a light emitting diode (LED) connected to a digital pin,
  without using the delay() function. This means that other code can run at the
  same time without being interrupted by the LED code.
*/

// constants used to set a pin number:
const int pumpPin =  7;// the number of the pump pin
const int humidPin = A0;// the number of humidity sensor pin

const int dry = 0; // when humidity drops below this, turn pump on
const int wet = 0; // when humidity rises above this, turn pump off


int pumpState = LOW;             // used to set pump

int water; // humidity read from thermometer

void setup() {
  Serial.begin(9600);
  // set the digital pin as output:
  pinMode(pumpPin, OUTPUT);
  pinMode(humidPin, INPUT);
}

void loop() {
    water = analogRead(humidPin);
    Serial.println(water);
    if (water < dry) {
      pumpState = HIGH;
    }
    if (water > wet) {
      pumpState = LOW;
    }

    // set the pump with the pumpState of the variable:
    digitalWrite(pumpPin, pumpState);
    delay(1000);
  }
