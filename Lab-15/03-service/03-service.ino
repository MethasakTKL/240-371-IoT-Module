#include <BLEDevice.h>
#include <DHT.h>

#define DHTPIN 12     // กำหนดหมายเลขพอร์ตที่เซ็นเซอร์ DHT11 ต่อกับ Arduino
#define DHTTYPE DHT11 // เลือกประเภทของเซ็นเซอร์ (DHT11, DHT21, DHT22)
DHT dht(DHTPIN, DHTTYPE);

#define BLE_GATT_UUID_TEMPERATURE 0x2A6E

BLEServer *bleServer;
BLEService *envService;
BLECharacteristic *tempChar;

using namespace std;

void setup()
{
    Serial.begin(115200);
    randomSeed(analogRead(0));
    dht.begin();

    BLEDevice::init(string("ESP32 (GATT) - 429"));
    BLEAddress bleAddr = BLEDevice::getAddress();
    Serial.println("\nBLE initialized. Address: " + String(bleAddr.toString().c_str()));
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor!");
    }

    // create BLE Server
    bleServer = BLEDevice::createServer();

    // create environmental sensing service
    envService = bleServer->createService(BLEUUID((uint16_t)ESP_GATT_UUID_ENVIRONMENTAL_SENSING_SVC));

    tempChar = envService->createCharacteristic(
        BLEUUID((uint16_t)BLE_GATT_UUID_TEMPERATURE),
        BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);

    envService->start();
}

void loop()
{
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    string tempString = "Temp:" + to_string(temperature) + " Hudi:" + to_string(humidity);

    Serial.println(String(tempString.c_str()));

    // update value and notify
    tempChar->setValue(tempString);
    tempChar->notify();

    // start advertising
    BLEDevice::startAdvertising();

    delay(5000);
}
