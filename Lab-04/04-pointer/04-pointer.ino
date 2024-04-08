void setup()
{
    Serial.begin(115200);

    int myInteger = 42;
    int *myPointer = &myInteger;

    Serial.print("Direct Value: ");
    Serial.println(myInteger);

    *myPointer = 99;
    Serial.print("Indirect Value through Pointer: ");
    Serial.println(*myPointer);

    Serial.print("Direct Value adter MOD: ");
    Serial.println(myInteger);

}

void loop()
{
    // Nothing to do in the loop for this example
}
