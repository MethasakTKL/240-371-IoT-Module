const int potPin = 36;
const int ledPin = 12;

void setup()
{
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop()
{
    int potValue = analogRead(potPin);
    Serial.println(potValue);

    int brightness = map(potValue, 0, 4095, 0, 255);
    analogWrite(ledPin, brightness);
    delay(100);
}
