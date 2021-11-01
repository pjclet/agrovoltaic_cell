// set up const vars for ports used for each sensor, motor
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
// I'm assuming that the fewer times the code has to turn stuff on/off the better, so rather than one target value, there will be a minimum and maximum value
// Thermo section: read thermometer (see amazon comments). If below minimum temperature, turn on heating element. If above maximum temperature, turn off heating element
// Water section: read moisture sensor. Turn pump on/off as above
// Shading section: read thermometer/light sensor (depending on design decision). Rotate solar panels to increase/decrease effective surface area as needed.
// Air circulation section: not sure under what conditions we intend to circulate air. On a timer?
// Fertilizer: Dispense fertilizer on a timer, or with the water?

// looks good - pj
}
