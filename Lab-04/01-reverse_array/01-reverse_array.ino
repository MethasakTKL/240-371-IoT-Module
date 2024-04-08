void setup()
{
    Serial.begin(115200);

    int myArray[] = {1, 2, 3, 4, 5};
    int size = sizeof(myArray) / sizeof(myArray[0]);

    // Original
    Serial.print("Original Array: ");
    for (int i = 0; i < size; i++)
    {
        Serial.print(myArray[i]);
        Serial.print(" ");
    }
    Serial.println();

    // เรียกใช้ฟังก์ชัน ReverseArray
    reverseArray(myArray, size);

    // After reversing
    Serial.print("Reversed Array: ");
    for (int i = 0; i < size; i++)
    {
        Serial.print(myArray[i]);
        Serial.print(" ");
    }
    Serial.println();
}

void loop()
{

}

void reverseArray(int arr[], int size) {
    for (int start = 0, end = size - 1; start < end; start++, end--) {
        
        // สลับค่าระหว่างตำแหน่งที่ start และ end
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
    }
}