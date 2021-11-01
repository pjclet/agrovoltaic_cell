#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin PLACEHOLDER on the Arduino
#define ONE_WIRE_BUS PLACEHOLDER

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// set up const vars for ports used for each sensor, motor
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Start up the library
  sensors.begin(); // IC Default 9 bit. If you have troubles consider upping it 12. Ups the delay giving the IC more time to process the temperature measurement
}

void loop() {
  // put your main code here, to run repeatedly:
// I'm assuming that the fewer times the code has to turn stuff on/off the better, so rather than one target value, there will be a minimum and maximum value
// Thermo section: read thermometer (see amazon comments). If below minimum temperature, turn on heating element. If above maximum temperature, turn off heating element
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures();
  Serial.print("Temperature for Device 1 is: ");
  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
// Water section: read moisture sensor. Turn pump on/off as above
// Shading section: read thermometer/light sensor (depending on design decision). Rotate solar panels to increase/decrease effective surface area as needed.
// Air circulation section: not sure under what conditions we intend to circulate air. On a timer?
// Fertilizer: Dispense fertilizer on a timer, or with the water?
<<<<<<< Updated upstream

// PJ
=======
// Val
>>>>>>> Stashed changes
}
