void addition(int a, int b)
{
  int result = a + b;
  Serial.printf("%d + %d = %d\n\n", a, b, result);
}

void subtraction(int a, int b)
{
  int result = a - b;
  Serial.printf("%d - %d = %d\n\n", a, b, result);
}

void multiplication(int a, int b)
{
  int result = a * b;
  Serial.printf("%d x %d = %d\n\n", a, b, result);
}

void division(int a, int b)
{
  if (b != 0)
  {
    int result = a / b;
    Serial.printf("%d / %d = %d\n\n", a, b, result);
  }
  else
  {
    Serial.println("Error: Division by zero.\n");
  }
}

void processInput(String input)
{
  int a, b;
  char op;

  // Parse the input
  if (sscanf(input.c_str(), "%d %c %d", &a, &op, &b) == 3)
  {
    // Perform the corresponding operation
    switch (op)
    {
    case '+':
      addition(a, b);
      break;
    case '-':
      subtraction(a, b);
      break;
    case '*':
      multiplication(a, b);
      break;
    case '/':
      division(a, b);
      break;
    default:
      Serial.println("Error: Invalid operator.\n");
      break;
    }
  }
  else
  {
    Serial.println("Error: Invalid input format.\n");
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Enter an equation: ");
}

void loop()
{
  if (Serial.available() > 0)
  {
    String input = Serial.readStringUntil('\n\n');
    processInput(input);
    Serial.println("Enter an equation: ");
  }
}
