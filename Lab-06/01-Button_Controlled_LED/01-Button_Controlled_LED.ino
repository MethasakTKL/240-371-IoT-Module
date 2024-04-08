int ledPin = 23;
int buttonPin = 19;

int ledState = LOW;

void setup()
{
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW)
  {
    delay(200);
    ledState = !ledState;
    Serial.print("Button Pressed ");
    while (digitalRead(buttonPin) == LOW)
    {
      Serial.println("Button is holding ");
    }

    Serial.print("ledState =");
    Serial.println(ledState);

    digitalWrite(ledPin, ledState);
  }
}
