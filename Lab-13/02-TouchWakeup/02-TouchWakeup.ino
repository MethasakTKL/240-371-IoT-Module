#define touch_pin 4
const int Buzzer = 12;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    pinMode(Buzzer, OUTPUT);

    int Threshold = 20;
    touchSleepWakeUpEnable(4, Threshold);
    Serial.println("Morning");
    delay(1000);

    esp_sleep_enable_touchpad_wakeup();
    Serial.println("Going to sleep now");
    delay(1000);
    esp_deep_sleep_start();
    Serial.println("TEST Sleep mode"); // this line NOT show  --> SLEEP MODE
}

void loop()
{
}

void call()
{
}