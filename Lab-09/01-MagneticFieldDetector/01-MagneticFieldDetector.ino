void setup() {
  Serial.begin(115200);
}

void loop() {
  int magneticFieldStrength = abs(hallRead());

  Serial.print("Magnetic Field Strength: ");
  Serial.println(magneticFieldStrength);

  int thresholdmag = 100;  
  if (abs(magneticFieldStrength) > thresholdmag) {
    Serial.println("Magnet Detected!");
  }

  delay(500);
}
