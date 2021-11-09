#include <OneWire.h>
#include <DallasTemperature.h>
#include <DS18B20.h>

DS18B20 ds(2);
// Data wire is plugged into pin 2 on the Arduino
OneWire oneWire(2);
DallasTemperature dTemp(oneWire);
#define heating PORT


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
//OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
//DallasTemperature sensors(&oneWire);

// set up const vars for ports used for each sensor, motor
void setup() {

  
  // Serial.begin(9600);
  Serial.print("Devices: ");
  //Serial.println(ds.getNumberOfDevices());
  //Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:
// I'm assuming that the fewer times the code has to turn stuff on/off the better, so rather than one target value, there will be a minimum and maximum value
// Thermo section: read thermometer (see amazon comments). If below minimum temperature, turn on heating element. If above maximum temperature, turn off heating element
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
//  while (ds.selectNext()) {
//    switch (ds.getFamilyCode()) {
//      case MODEL_DS18S20:
//        Serial.println("Model: DS18S20/DS1820");
//        break;
//      case MODEL_DS1822:
//        Serial.println("Model: DS1822");
//        break;
//      case MODEL_DS18B20:
//        Serial.println("Model: DS18B20");
//        break;
//      default:
//        Serial.println("Unrecognized Device");
//        break;
//    }
    dTemp->requestTemperatures();
    Serial.println("Temp @ Index: 0:" + String(dtemp->getTempFByIndex(0)));

    uint8_t address[8];
    ds.getAddress(address);

    Serial.print("Address:");
    for (uint8_t i = 0; i < 8; i++) {
      Serial.print(" ");
      Serial.print(address[i]);
    }
    Serial.println();

    Serial.print("Resolution: ");
    Serial.println(ds.getResolution());

    Serial.print("Power Mode: ");
    if (ds.getPowerMode()) {
      Serial.println("External");
    } else {
      Serial.println("Parasite");
    }

    Serial.print("Temperature: ");
    Serial.print(ds.getTempC());
    Serial.print(" C / ");
    Serial.print(ds.getTempF());
    Serial.println(" F");
    Serial.println();
  }

  delay(1000);

// Water section: read moisture sensor. Turn pump on/off as above
// Shading section: read thermometer/light sensor (depending on design decision). Rotate solar panels to increase/decrease effective surface area as needed.
// Air circulation section: not sure under what conditions we intend to circulate air. On a timer?
// Fertilizer: Dispense fertilizer on a timer, or with the water?
}
