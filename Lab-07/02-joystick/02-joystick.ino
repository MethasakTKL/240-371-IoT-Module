const int joyXPin = 34;   
const int joyYPin = 35;   
const int ledXPin = 12;    
const int ledYPin = 13;   

void setup() {
  pinMode(ledXPin, OUTPUT);
  pinMode(ledYPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  int joyXValue = analogRead(joyXPin);
  int joyYValue = analogRead(joyYPin);

  int brightnessX = map(joyXValue, 0, 4095, 0, 255);
  int brightnessY = map(joyYValue, 0, 4095, 0, 255);

  analogWrite(ledXPin, brightnessX);
  analogWrite(ledYPin, brightnessY);

  Serial.printf("X-Axis Value: %d\n",joyXValue);
  Serial.printf("Y-Axis Value: %d\n",joyYValue);
  Serial.printf("LED X Brightness: %d\n",brightnessX);
  Serial.printf("LED Y Brightness: %d\n",brightnessY);
  delay(200); 
}
