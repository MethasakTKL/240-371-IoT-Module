#include <Preferences.h>

Preferences pref;
int bootCount = 0;

void setup()
{
    Serial.begin(115200);

    pref.begin("iot-app", false);

    // Clear boot count Value
    // pref.remove("bootCount");
    // Serial.println("Boot count cleared.");
    // Serial.println(bootCount);

    // boot count = 0 (initial)
    bootCount = pref.getInt("bootCount", 0);
    // Increase boot counter
    bootCount++;
    Serial.printf("Reboot Counter: %d\n", bootCount);
    pref.putInt("bootCount", bootCount); // Save the updated boot count to NVS
}

void loop()
{
}
