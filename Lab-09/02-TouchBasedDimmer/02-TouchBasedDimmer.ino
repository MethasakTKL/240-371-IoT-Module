const int touchPin = 4;
const int ledPin = 13;

void setup()
{
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
}

void loop()
{
    // Read Touch sensor
    int touchValue = touchRead(touchPin);
    Serial.print("Touch Sensor Value: ");
    Serial.println(touchValue);

    // Mapping
    int brightness = map(touchValue, 20, 76, 255, 0);
    analogWrite(ledPin, brightness);
    
    // Show Brightness
    Serial.print("LED Brightness: ");
    Serial.println(brightness);

    delay(500);
}
