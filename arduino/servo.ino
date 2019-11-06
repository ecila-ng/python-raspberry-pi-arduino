#include <Servo.h>
Servo myServo;

void setup() {
  myServo.attach(D4);
  myServo.write(0);
  delay(2000);
}

void loop() {
  myServo.write(90);
  delay(1000);
  myServo.write(0);
  delay(1000);

  //Red wire comes from 3v3
  //Brown/Black to Ground
  //Orange/White to digital input
}
