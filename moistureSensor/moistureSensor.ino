int sensorPin = 0;    // select the input pin for the Soil moisture sensor
int pumpPin = 9;
int sensorValue = 0;  // variable to store the value coming from the sensor
 
int sensorVCC = 10;

 
void setup() {
  // declare the ledPin as an OUTPUT:
   Serial.begin(9600);  
   pinMode(sensorVCC, OUTPUT); 
   pinMode(pumpPin, OUTPUT);
   digitalWrite(sensorVCC, LOW);
   digitalWrite(pumpPin, HIGH);
   delay(1000);
   digitalWrite(pumpPin, LOW);
   delay(1000);
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
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);          
  if (sensorValue >= 30){
    Serial.println("HIGH");
    digitalWrite(pumpPin, HIGH);        
  } else {
    digitalWrite(pumpPin, LOW);
  }
}
