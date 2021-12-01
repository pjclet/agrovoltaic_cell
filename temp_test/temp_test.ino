/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
  Based on the Dallas Temperature Library example
*********/

#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to the Arduino digital pin 3
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

const int heaterPin =  4;// heater pin number

const int cold = 27; // when temperature drops below this, turn heater on
const int hot = 29; // when temperature rises above this, turn heater off

int heaterState = LOW;
int temp;
const long failsafeHeaterOn = 15000; // how long heater can stay on if temp sensor is unresponsive
const long failsafeHeaterOff = 5000; // how long heater must stay off if temp sensor is unresponsive
unsigned long offMillis = 0; // when heater turned off
unsigned long onMillis = 0; // when heater turned on
const long interval = 1000; // how often heater is updated
unsigned long prevMillis = 0; // when heater was last updated

void setup(void)
{
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  pinMode(heaterPin, OUTPUT);
}

void loop(void){ 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  unsigned long currentMillis = millis();
  if(currentMillis - prevMillis > interval){
    prevMillis = currentMillis;
    sensors.requestTemperatures(); 
//    Serial.print("Fahrenheit temperature: ");
    // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
    temp = sensors.getTempFByIndex(0);
    Serial.print(temp); 
//    Serial.print(" - Celsius temperature: ");
//    Serial.println(sensors.getTempCByIndex(0));
    Serial.print(",");
    Serial.print(currentMillis);
    Serial.print(",");
    Serial.print(heaterState);
    Serial.print("\n");
//    Serial.print("\t");
//    Serial.print(onMillis);
//    Serial.print("\t");
    if ((temp < cold) and (currentMillis-offMillis>failsafeHeaterOff)) {
      if(heaterState == LOW){
        onMillis = currentMillis;
      }
      heaterState = HIGH;
  
    }
    if ((temp > hot) or (currentMillis-onMillis>failsafeHeaterOn)) {
      if(heaterState == HIGH){
        offMillis = currentMillis;
      }
      heaterState = LOW;
    }
    // set the pump with the pumpState of the variable:
    digitalWrite(heaterPin, heaterState);
  }
}
