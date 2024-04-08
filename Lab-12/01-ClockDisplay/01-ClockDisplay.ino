#include <DS3231.h>

#define RTC_SDA 21
#define RTC_SCL 22
#define RTC_SET_FLAG 0xAA
DS3231 rtc(RTC_SDA, RTC_SCL);

const char *dayNames[] = {"Unknown", "Sunday", "Monday", "Tuesday", "Wednesday",
                          "Thursday", "Friday", "Saturday"};

void setup()
{
  Serial.begin(115200);
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
    rtc.writeRam(0,RTC_SET_FLAG);
    Serial.println("successfully set time to" + dtString);
  }
}

void loop()
{
  Time now = rtc.time();
  Serial.print(String(now.yr));
  Serial.print("-");
  printTwoDigits(now.mon);
  Serial.print("-");
  printTwoDigits(now.date);
  Serial.print(" ");
  Serial.print(dayNames[now.day]);
  Serial.print(" ");
  printTwoDigits(now.hr);
  Serial.print(":");
  printTwoDigits(now.min);
  Serial.print(":");
  printTwoDigits(now.sec);
  Serial.println();
  delay(1000);
}

void printTwoDigits(int number)
{
  if (number < 10)
  {
    Serial.print("0");
  }
  Serial.print(String(number));
}
