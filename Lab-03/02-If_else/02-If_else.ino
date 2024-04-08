void setup()
{
  Serial.begin(115200);
}

void loop()
{
  // Read Input
  Serial.print("Enter a number: ");

  while (!Serial.available())
  {
    delay(100);
  }

  int n = Serial.parseInt(); 

  while (Serial.available())
  {
    Serial.read();
  }

  // Main Function
  if (n == 0)
  {
    Serial.printf("%d is Zero\n\n", n);
  }
  else if (n < 0)
  {
    Serial.printf("%d is negative\n\n", n);
  }
  else if (n > 0)
  {
    Serial.printf("%d is positive\n\n", n);
  }
}
