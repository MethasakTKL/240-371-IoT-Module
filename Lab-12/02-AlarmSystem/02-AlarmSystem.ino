#include <DS1302.h>

#define RTC_DAT 21
#define RTC_SCL 22
#define RTC_RESET 18
#define RTC_SET_FLAG 0xAA

#define LED 14

DS1302 rtc(RTC_RESET, RTC_DAT, RTC_SCL);

const char *dayNames[] = {"Unknown", "Sunday", "Monday", "Tuesday", "Wednesday",
                          "Thursday", "Friday", "Saturday"};

void setup()
{
    Serial.begin(115200);

    pinMode(LED, OUTPUT);

    rtc.writeProtect(false); // can edit time
    rtc.halt(false);         // stop time if true
    uint8_t flag = rtc.readRam(0);
    if (flag != RTC_SET_FLAG)
    {
        uint16_t yr;
        uint8_t mon, date, hr, min, sec;
        Time::Day day;

        Serial.println();
        Serial.println("RTC time NOT set");
        Serial.println("Enter format yyyy/mm/dd hh:mm:ss weekday");
        while (!Serial.available())
            ;
        String dtString = Serial.readStringUntil('\n');
        sscanf(dtString.c_str(), "%hu/%hhu/%hhu %hhu:%hhu:%hhu %hhu",
               &yr, &mon, &date, &hr, &min, &sec, &day);

        Time now(yr, mon, date, hr, min, sec, day);
        rtc.time(now);
        rtc.writeRam(0, RTC_SET_FLAG);
        Serial.println("successfully set time to" + dtString);
    }
}

void loop()
{
    uint8_t alarm_hr, alarm_min;
    String timeString = Serial.readStringUntil('\n');
    sscanf(timeString.c_str(), "%hhu:%hhu", &alarm_hr, &alarm_min);
    Time now = rtc.time();
    Serial.printf("alarm_hr :%d , alarm_min :%d  --> ", alarm_hr, alarm_min);
    printTwoDigits(now.hr);
    Serial.print(":");
    printTwoDigits(now.min);
    Serial.print(":");
    printTwoDigits(now.sec);
    Serial.println();

    // Set time alarm
    if (now.hr == alarm_hr && now.min == alarm_min)
    {
        digitalWrite(LED, HIGH);
    }
    else
    {
        digitalWrite(LED, LOW);
    }
}
void printTwoDigits(int number)
{
    if (number < 10)
    {
        Serial.print("0");
    }
    Serial.print(String(number));
}
