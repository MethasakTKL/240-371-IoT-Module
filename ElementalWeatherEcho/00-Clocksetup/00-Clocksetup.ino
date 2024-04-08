#include <Wire.h>
#include <RTClib.h>

int buttonPin = 12;
unsigned long pressStartTime = 0;
bool holding = false;

RTC_DS3231 rtc;

void checkSetRTCButton()
{
    int buttonState = digitalRead(buttonPin);

    if (buttonState == LOW)
    {
        delay(100);
        if (!holding)
        {
            pressStartTime = millis(); // เก็บเวลาเริ่มต้นที่กด
            Serial.println("Set timeButton is Pressed , Hold 5 sec. to set Time");
            holding = true;
        }

        if (millis() - pressStartTime >= 5000) // ถ้าผ่านไป 5 วินาที
        {
            uint16_t yr;
            uint8_t mon, date, hr, min, sec;
            Serial.println("Set RTC Mode *************************");
            Serial.println("DD/MM/YYYY HH:MM:SS");

            while (!Serial.available())
                ;
            String dtString = Serial.readStringUntil('\n');
            sscanf(dtString.c_str(), "%hhu/%hhu/%hu %hhu:%hhu:%hhu",
                   &date, &mon, &yr, &hr, &min, &sec);
            rtc.adjust(DateTime(yr, mon, date, hr, min, sec));
            Serial.printf("Set Time ************** %d/%d/%d %d:%d:%d ", date, mon, yr, hr, min, sec);
            pressStartTime = millis();
        }
    }
    else
    {
        holding = false; // รีเซ็ตค่าเมื่อปล่อยปุ่ม
    }
}

String addLeadingZero(int number)
{
    if (number < 10)
    {
        return "0" + String(number);
    }
    else
    {
        return String(number);
    }
}

void setup()
{
    Serial.begin(115200);
    pinMode(buttonPin, INPUT_PULLUP);

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1)
            ;
    }

    // ตรวจสอบว่า RTC ได้หายไปเวลาหรือไม่
    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, let's set the time!");
        // rtc.adjust(DateTime(yr, mon, date, hr, min, sec));
        rtc.adjust(DateTime(2024, 1, 1, 1, 0, 0)); // หรือสามารถกำหนดค่าเวลาเองได้
    }
}

void loop()
{
    checkSetRTCButton();
    DateTime now = rtc.now();

    String year = String(now.year());
    String month = addLeadingZero(now.month());
    String day = addLeadingZero(now.day());
    String hour = addLeadingZero(now.hour());
    String minute = addLeadingZero(now.minute());
    String second = addLeadingZero(now.second());

    Serial.println(year + "/" + month + "/" + day + " " + hour + ":" + minute + ":" + second);

    delay(1000);
}
