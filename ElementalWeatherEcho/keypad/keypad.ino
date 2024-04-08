#include <LiquidCrystal_I2C.h>
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>

#define I2CADDR 0x20
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1, 0};


LiquidCrystal_I2C lcd(0x27, 20, 4); // Module IIC/I2C Interface บางรุ่นอาจจะใช้ 0x3f
Keypad_I2C keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR);
String keyinputDate = "";
String keyinputTime = "";

byte keyindexDate = 0;
byte keyindexTime = 0;

String ModeState = "A";
int LineState = 0;

void setup()
{
    Serial.begin(115200);

    Wire.begin();
    keypad.begin();
    lcd.begin();
    lcd.backlight(); // เปิด backlight

    lcd.setCursor(5, 1);
    lcd.print("Masternode");
    delay(2000);
    lcd.clear();
}

void loop()
{
    int i;
    char key = keypad.getKey();
    if (key != NO_KEY)
    {
        if (key == 'A')
        {
            lcd.clear();
            ModeState = "A";
            lcd.setCursor(7, 1);
            lcd.print("Display");
            lcd.setCursor(8, 2);
            lcd.print("Mode");
            delay(1000);
            lcd.clear();
        }
        else if (key == 'B' && ModeState == "A")
        {
            lcd.clear();
            //! In Mode B always Input = ""
            keyinputDate = "";
            keyinputTime = "";
            /////////////////////////
            ModeState = "B";
            lcd.setCursor(7, 1);
            lcd.print("Set RTC");
            lcd.setCursor(8, 2);
            lcd.print("Mode");
            delay(1000);
            lcd.clear();
            LineState = 0;
        }
        //////////////////////////////////////////////////////////////////
        if (ModeState == "B")
        {
            if (isdigit(key))
            { // ตรวจสอบว่าเป็นตัวเลขหรือไม่
                lcd.setCursor(19, 2);
                lcd.print(key);
                if (LineState == 1)
                {
                    keyinputDate += key;
                    keyindexDate++;
                    lcd.setCursor(1, 0);
                    lcd.print(keyinputDate);
                }
                else if (LineState == 2)
                {
                    keyinputTime += key;
                    keyindexTime++;
                    lcd.setCursor(1, 1);
                    lcd.print(keyinputTime);
                }
            }
            else if (key == 'B')
            {
                if (LineState == 0)
                {
                    Serial.println("Line 1");
                    LineState = 1;
                }
                else if (LineState == 1)
                {
                    Serial.println("Line 2");
                    LineState = 2;
                }
                else if (LineState == 2)
                {
                    Serial.println("Line 1");
                    LineState = 1;
                }
            }
            else if (key == 'C')
            {
                if (LineState == 1)
                {
                    keyinputDate += ",";
                    keyindexDate++;
                    lcd.setCursor(1, 0);
                    lcd.print(keyinputDate);
                }
                else if (LineState == 2)
                {
                    keyinputTime += ",";
                    keyindexTime++;
                    lcd.setCursor(1, 1);
                    lcd.print(keyinputTime);
                }
            }
            else if (key == 'D')
            {
                if (LineState == 1 && keyindexDate > 0)
                {
                    keyinputDate.remove(keyinputDate.length() - 1);
                    keyindexDate--;
                    lcd.clear();
                    lcd.setCursor(1, 0);
                    lcd.print(keyinputDate);
                }
                else if (LineState == 2 && keyindexTime > 0)
                {
                    keyinputTime.remove(keyinputTime.length() - 1);
                    keyindexTime--;
                    lcd.clear();
                    lcd.setCursor(1, 1);
                    lcd.print(keyinputTime);
                }
            }
            else if (key == '*')
            {
                lcd.clear();
                lcd.setCursor(7, 1);
                lcd.print("Clear");
                keyinputDate = "";
                keyinputTime = "";
                delay(500);
                lcd.clear();
            }
            else if (key == '#')
            {
                lcd.clear();
                lcd.setCursor(6, 1);
                lcd.print("Sent Time");
                delay(1500);
                lcd.clear();
                ModeState = "A";
                Serial.println("0x137," + keyinputDate + "," + keyinputTime);
                Serial.println("0x429," + keyinputDate + "," + keyinputTime);
            }
        }
    }
    // todo Display Data //////////////////////////////////////////////////////////////////////////////////
    if (ModeState == "A")
    {
        lcd.setCursor(0, 0);
        lcd.print("Display Data");
    }
    if (ModeState == "B")
    {
        if (LineState == 1)
        {
            lcd.setCursor(0, 0);
            lcd.print(">");
            lcd.setCursor(0, 1);
            lcd.print(" ");
        }
        else if (LineState == 2)
        {
            lcd.setCursor(0, 0);
            lcd.print(" ");
            lcd.setCursor(0, 1);
            lcd.print(">");
        }
        //////////////////////////////
        lcd.setCursor(1, 0);
        lcd.print(keyinputDate);
        lcd.setCursor(1, 1);
        lcd.print(keyinputTime);
        /////////////////////
        lcd.setCursor(0, 2);
        lcd.print("D Back");
        lcd.setCursor(13, 2);
        lcd.print("Input ");
        lcd.setCursor(0, 3);
        lcd.print("* Cancel");
        lcd.setCursor(13, 3);
        lcd.print("# Save");
    }
    lcd.setCursor(19, 0);
    lcd.print(ModeState);
}
