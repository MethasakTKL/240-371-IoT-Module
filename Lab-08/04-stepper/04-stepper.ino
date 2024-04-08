#include <AccelStepper.h>

const int potPin = 36;   
const int motorPin1 = 13; 
const int motorPin2 = 12; 
const int motorPin3 = 14; 
const int motorPin4 = 27; 

AccelStepper stepper(4, motorPin1, motorPin3, motorPin2, motorPin4);


void setup() {
  stepper.setMaxSpeed(1000.0);
  Serial.begin(115200);
}

void loop() {
  int potValue = analogRead(potPin);

  float speed = map(potValue, 0, 4095, 0, 1000);

  stepper.setSpeed(speed);

  stepper.runSpeed();

  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(", Speed: ");
  Serial.println(speed);

  delay(10);
}
