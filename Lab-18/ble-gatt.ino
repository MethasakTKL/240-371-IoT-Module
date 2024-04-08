#include <BLEDevice.h>

BLEAdvertising *bleAdv;
BLEServer *bleServer;
BLEService *envService;
BLECharacteristic *tempChar;

BLEUUID envServiceUUID((uint16_t)ESP_GATT_UUID_ENVIRONMENTAL_SENSING_SVC);
BLEUUID tempCharUUID((uint16_t)0x2A6E);

// BLE Service 0x180A: Device Information
// BLE Characteristic 0x2A28: Software Revision String

using namespace std;

string readTemperature() {
    float temperature = 20 + (float)random(20000) / 1000.0;
    string tempString = to_string(temperature);
    return tempString;
}

void setup() {
	Serial.begin(115200);
    randomSeed(analogRead(0));

    BLEDevice::init(string("ESP32 6410110XXX"));

    // create BLE Server
    bleAdv = BLEDevice::getAdvertising();
    bleServer = BLEDevice::createServer();

    // create Environmental Sensing service
    bleAdv->addServiceUUID(envServiceUUID);
    envService = bleServer->createService(envServiceUUID);

    // create Temperature characteristic
    tempChar = envService->createCharacteristic(
        tempCharUUID,
        BLECharacteristic::PROPERTY_READ);

    envService->start();
}

void loop() {
    string temperature = readTemperature();

    Serial.println("Temperature: " + String(temperature.c_str()));
    tempChar->setValue(temperature);

    // start advertising
    BLEDevice::startAdvertising();

    delay(5000);
}
