int sensorPin = A0;
int buttonPin = 16;
void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  float btnValue = digitalRead(buttonPin);

  if (btnValue == 1.0) {
    //Serial.print("Original value:");
    //Serial.println(sensorValue);

    //convesion
    float temp = (float (sensorValue) / 1024);
    temp = temp * 3.3;
    temp = temp - 0.5;
    temp = temp * 1000;
    temp = temp / 10;
    delay(50); 
    btnValue = digitalRead(buttonPin);
    if (btnValue == 0.0) {


      Serial.print("Celsius:");
      Serial.println(temp);
      //Serial.println("Button value:");
      //Serial.println(btnValue);
      Serial.println();
    }
  }

}
