#include <Adafruit_CCS811.h>

Adafruit_CCS811 ccs;
const int fanPin = 4;
const int errorLED = 13;
int airQualityThreshold = 1000;
int fanState = HIGH;


void setup() {
  Serial.begin(9600);

//  Serial.println("CCS811 test");

  if(!ccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!ccs.available());
  digitalWrite(fanPin, fanState);
}

void loop() {
//  if(ccs.available()){
//    if(!ccs.readData()){
//      Serial.print("CO2: ");
//      Serial.print(ccs.geteCO2());
//      Serial.print("ppm, TVOC: ");
//      Serial.println(ccs.getTVOC());
//    }
//    else{
//      Serial.println("ERROR!");
//      while(1);
//    }
//  }
  atmosphere();
  
  delay(500);
}

void atmosphere(){

  if (ccs.available()){ // check if sensors are active
    if (!ccs.readData()){

//      Serial.print("CO2: ");
      Serial.print(millis());
      Serial.print(",");
      Serial.print(ccs.geteCO2());
//      Serial.print("ppm, TVOC: ");
//      Serial.println(ccs.getTVOC());

      if ((fanState == HIGH) && (ccs.geteCO2() > airQualityThreshold)) {
        fanState = LOW;
        digitalWrite(fanPin, fanState);
        digitalWrite(errorLED, HIGH);
//        Serial.println("CHANGE: Fan off");
        
      } else if ((fanState == LOW) && (ccs.geteCO2() <= airQualityThreshold)) {
        fanState = HIGH;
        digitalWrite(fanPin, fanState);
        digitalWrite(errorLED, LOW);
//        Serial.println("CHANGE: Fan on");
      }
      Serial.print(",");
      Serial.print(fanState);
      Serial.println();
    } else {
//      Serial.println("ERROR: Air Sensor Inactive");
      for (int i = 1; i < 10; i++){
        digitalWrite(errorLED, HIGH);
        delay(100);
        digitalWrite(errorLED, LOW);
        delay(100);
      }
    }
    
  }
  
}
