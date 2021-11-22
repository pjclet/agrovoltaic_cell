/*
  Blink without Delay

  Turns on and off a light emitting diode (LED) connected to a digital pin,
  without using the delay() function. This means that other code can run at the
  same time without being interrupted by the LED code.
*/

// constants used to set a pin number:
const int pumpPin =  PLACEHOLDER;// the number of the pump pin
const int heaterPin =  PLACEHOLDER;// heater pin number

const int cold = PLACEHOLDER; // when temperature drops below this, turn heater on
const int hot = PLACEHOLDER; // when temperature rises above this, turn heater off
const int dry = PLACEHOLDER; // when humidity drops below this, turn pump on
const int wet = PLACEHOLDER; // when humidity rises above this, turn pump off


int pumpState = LOW;             // used to set pump
int heaterState = LOW;

int temp =  PLACEHOLDER; // temperature read from thermometer
int water = PLACEHOLDER; // humidity read from thermometer

void setup() {
  // set the digital pin as output:
  pinMode(pumpPin, OUTPUT);
  pinMode(heaterPin, OUTPUT);
}

void loop() {
    if (temp < cold) {
      heaterState = HIGH;
    }
    if (temp > hot) {
      heaterState = LOW;
    }
    if (water < dry) {
      pumpState = HIGH;
    }
    if (water > wet) {
      pumpState = LOW;
    }

    // set the pump with the pumpState of the variable:
    digitalWrite(pumpPin, pumpState);
    digitalWrite(heaterPin, heaterState);
  }
}
