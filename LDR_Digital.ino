#define PIN 16

void setup() {
 Serial.begin(9600); 
   pinMode(PIN, INPUT);
}

void loop() {
  int sensorValue = digitalRead(PIN);
  //Serial.print("Sensor value: ");
  //Serial.println(sensorValue);
  delay(1000);

  if (sensorValue == 0) {
    Serial.println("No light!");
  }
    else if (sensorValue == 1) {
      Serial.println("Light!");
  }
}
