struct Person
{
    char name[20];
    int age;
};

bool isOlder(const Person &person1, const Person &person2)
{
    return person1.age > person2.age;
}

void setup()
{
    Serial.begin(115200);

    // Person
    Person personA = {"John", 30};
    Person personB = {"Ohm", 20};



    // Main Function
    if (isOlder(personA, personB))
    {
        Serial.printf("%s is older than %s\n\n", personA.name, personB.name);
    }
    else if (isOlder(personB, personA))
    {
        Serial.printf("%s is older than %s\n\n", personB.name, personA.name);
    }
    else
    {
        Serial.printf("%s has the SAME age as %s\n\n", personA.name, personB.name);
    }
}

void loop()
{
    // Your code here
}
