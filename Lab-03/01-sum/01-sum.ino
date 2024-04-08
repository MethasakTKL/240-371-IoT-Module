void setup()
{
  Serial.begin(115200);
}

void loop()
{
  int result = 0;

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
  if (n > 0)
  {
    for (int i = 1; i <= n; i++)
    {
      result += i;
    }
    Serial.printf("The sum of 1 to %d is %d\n\n", n, result);
  }
  else if (n <= 0)
  {
    Serial.printf("Please Enter POSITIVE number\n\n");
  }
}