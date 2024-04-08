void setup()
{
  Serial.begin(115200);
}

void loop()
{
  Serial.print("Enter a number: ");

  while (!Serial.available())
  {
    delay(100);
  }

  int number = Serial.parseInt(); // Read the entered number

  // Clear the serial buffer
  while (Serial.available())
  {
    Serial.read();
  }

  bool isInRange = (number >= 10) && (number <= 20);

  if (isInRange)
  {
    Serial.print("It's TRUE ");
    Serial.print(number);
    Serial.println(" is between 10 and 20\n");
  }
  else
  {
    Serial.print("It's FALSE ");
    Serial.print(number);
    Serial.println(" is NOT between 10 and 20\n");
  }
  delay(1000);
}
