void setup() {
  Serial.begin(115200);
  int A = 10;
  float B = 5.3;
  char C = 'a';

  Serial.printf("A = %d\n", A);
  Serial.printf("B = %f\n", B);
  Serial.printf("C = %c\n", C);
}

void loop() {
}
