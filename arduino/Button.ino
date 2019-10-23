#define BTN_PIN 16
#define LED_PIN 5

void setup() {
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  float btnValue = digitalRead(BTN_PIN);
  Serial.print("Button state:");
  Serial.println(btnValue);
  Serial.println();

  if (btnValue == 1) {
    
  }
}
