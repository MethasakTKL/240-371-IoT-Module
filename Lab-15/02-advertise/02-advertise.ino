#include <BLEDevice.h>
#include <DHT.h>

#define DHTPIN 12     // กำหนดหมายเลขพอร์ตที่เซ็นเซอร์ DHT11 ต่อกับ Arduino
#define DHTTYPE DHT11 // เลือกประเภทของเซ็นเซอร์ (DHT11, DHT21, DHT22)
DHT dht(DHTPIN, DHTTYPE);

// 0x181A
BLEUUID envSensingUUID((uint16_t)ESP_GATT_UUID_ENVIRONMENTAL_SENSING_SVC);

using namespace std;

string readTemperature()
{
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor!");
    }
    string tempString = "Temp"+to_string(temperature)+" Hud:"+to_string(humidity);

    return tempString;
}

void setup()
{
    Serial.begin(115200);
    BLEDevice::init("ESP32 Temperture Sensor-429");
}

void loop()
{
    BLEAdvertising *adv = BLEDevice::getAdvertising();
    BLEAdvertisementData data = BLEAdvertisementData();
    string temperature = readTemperature();

    data.setServiceData(envSensingUUID, temperature);
    adv->setAdvertisementData(data);
    adv->start();

    delay(5000);
}
