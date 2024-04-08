const int ledPin = 12;  

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Fade-in
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);
    Serial.println(brightness);
    delay(10);  
  }

  // Fade-out
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    Serial.println(brightness);
    delay(10);  
  }
  
}
