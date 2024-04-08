#include <BluetoothSerial.h>
#define touchpin 4

BluetoothSerial SerialBT;

void setup()
{
    Serial.begin(115200);
    SerialBT.begin("ESP32-429");
}

void loop()
{
    // static unsigned int counter = 0;
    int touchValue = 4095;

    // counter++;
    Serial.println("UART, Counter: " + String(touchValue));
    SerialBT.println("Bluetooth, Counter: " + String(touchValue));
    delay(1000);
}
