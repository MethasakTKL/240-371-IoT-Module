void setup()
{

  Serial.begin(115200);
}

void loop()
{
  int sensorValue;
  long sum = 0;
  sensorValue = analogRead(4);
  Serial.println(sensorValue);
  // for (int i = 0; i < 4095; i++) // accumulate readings for 1024 times
  // {
  //   sensorValue = analogRead(4);
  //   sum = sensorValue + sum;
  //   delay(2);
  // }
  // long meanVal = sum / 4095; // get mean value
  // Serial.print("The current UV index is:");
  // Serial.print((meanVal * 1000 / 4.3 - 83) / 21); // get a detailed calculating expression for UV index in schematic files.
  // Serial.print("\n");
  delay(500);
}