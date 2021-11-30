// constants used to set a pin number:
//const int sensor1 = A0;
//const int sensor2 = A1;
//int data1, int data 2;
int i=0;

void setup() {
  Serial.begin(9600);
//  pinMode(sensor1, INPUT);
//  pinMode(sensor2, INPUT);
}

void loop() {
//    data1 = analogRead(sensor1);
//    data2 = analogRead(sensor2);
    i++;
    Serial.print(i);
    Serial.print(",");
    Serial.print(i+2);
    Serial.print(",");
    Serial.println(i*2);
    delay(1000);
  }
