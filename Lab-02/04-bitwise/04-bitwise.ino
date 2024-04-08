void setup()
{
  // Start serial communication
  Serial.begin(115200);

  byte A = B11011010;
  byte B = B11110000;

  byte resultAND = A & B;
  byte resultOR = A | B;
  byte resultXOR = A ^ B;

  byte resultLeftShift_A = A << 2;
  byte resultRightShift_A = A >> 2;

  byte resultLeftShift_B = B << 2;
  byte resultRightShift_B = B >> 2;

  // Output the results
  Serial.println("");
  Serial.println("A Binary:   " + toBinaryString(A));
  Serial.println("B Binary:   " + toBinaryString(B));
  Serial.println("");
  Serial.println("AND : " + toBinaryString(resultAND));
  Serial.println("OR  : " + toBinaryString(resultOR));
  Serial.println("XOR : " + toBinaryString(resultXOR));
  Serial.println("");
  Serial.println("Left Shift by 2  (A):    " + toBinaryString(resultLeftShift_A));
  Serial.println("Right Shift by 2 (A):   " + toBinaryString(resultRightShift_A));
  Serial.println("Left Shift by 2  (B):    " + toBinaryString(resultLeftShift_B));
  Serial.println("Right Shift by 2 (B):   " + toBinaryString(resultRightShift_B));
}

void loop()
{
}

String toBinaryString(byte value)
{
  String binaryString = "";
  for (int i = 7; i >= 0; --i)
  {
    binaryString += bitRead(value, i);
  }
  return binaryString;
}
