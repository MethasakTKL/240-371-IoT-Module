#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 21

MFRC522 rfid(SS_PIN, RST_PIN); // Create an instance of the MFRC522 class

void setup()
{
    Serial.begin(115200);
    SPI.begin();     // Initialize SPI bus
    rfid.PCD_Init(); // Initialize RFID module

    Serial.println("Scan RFID tag to get UID");
}

void loop()
{

    // Look for new RFID cards
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    {
        return;
    }
    rfid.PICC_HaltA();

    Serial.print("UID: ");
    for (int i = 0; i< rfid.uid.size; i++){
        Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0": " ");
        Serial.print(rfid.uid.uidByte[i], HEX);
    }
    Serial.println();
    

}
