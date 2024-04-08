void setup()
{
    Serial.begin(115200);
}

void loop()
{
    // Read Input
    Serial.print("ENTER NUMBER 1-7:");

    while (!Serial.available())
    {
        delay(100);
    }

    int n = Serial.parseInt();

    while (Serial.available())
    {
        Serial.read();
    }

    // Main Function
    switch (n)
    {
    case 1:
        Serial.printf("Monday\n");
        break;
    case 2:
        Serial.printf("Tuesday\n");
        break;
    case 3:
        Serial.printf("Wednesday\n");
        break;
    case 4:
        Serial.printf("Thursday\n");
        break;
    case 5:
        Serial.printf("Friday\n");
        break;
    case 6:
        Serial.printf("Saturday\n");
        break;
    case 7:
        Serial.printf("Sunday\n");
        break;
    default:
        Serial.printf("not 1 - 7\n");
        break;
    }
}
