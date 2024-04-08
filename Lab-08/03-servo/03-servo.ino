#include <ESP32Servo.h>
Servo myServo; 

void setup() {
  Serial.begin(115200);
  myServo.attach(4);  
}

void loop() {
  // 0° to 180°
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(15);  
  }

  // 180° to 0°
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(15);  
  }
}
