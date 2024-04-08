void setup()
{
    Serial.begin(115200);
}

void loop()
{
    // Main Function
    int n;

    do
    {
        // Read Input
        Serial.print("Enter a positive number: ");

        while (!Serial.available())
        {
            delay(100);
        }

        n = Serial.parseInt();

        while (Serial.available())
        {
            Serial.read();
        }

        if (n <= 0)
        {
            Serial.printf("Invalid input. Please enter a positive number.\n\n");
        }
        else
        {
            Serial.printf("You entered the positive number: %d\n\n", n);
        }

    } while (n > 0);
}
