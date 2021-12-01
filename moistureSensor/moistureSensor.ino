int sensorPin = 0;    // select the input pin for the Soil moisture sensor
int pumpPin = 13;
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorVCC = 10;
int dry = 250;
 
void setup() {
  // declare the ledPin as an OUTPUT:
   Serial.begin(9600);  
   pinMode(sensorVCC, OUTPUT); 
   pinMode(pumpPin, OUTPUT);
   digitalWrite(sensorVCC, LOW);
}
 
void loop() {
  // power the sensor
  digitalWrite(sensorVCC, HIGH);
  delay(100); //make sure the sensor is powered
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin); 
  //stop power 
  digitalWrite(sensorVCC, LOW);  
  //wait
  delay(1000);//delay time change according to your need          
//  Serial.print("sensor = " );
  Serial.print(millis());
  Serial.print(",");                       
  Serial.print(sensorValue); 
  Serial.println();         
  if (sensorValue <= dry){
//    Serial.println("HIGH");
    digitalWrite(pumpPin, HIGH);        
  } else {
    digitalWrite(pumpPin, LOW);
  }
}
