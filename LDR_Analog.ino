void setup() {
 Serial.begin(9600); 
 Serial.println("Hello world!");
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println("Sensor value: ");
  Serial.println(sensorValue);

   delay(1000);
}
