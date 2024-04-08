#include <BLEDevice.h>

#define BLE_SCAN_INTERVAL  200
#define BLE_SCAN_WINDOW    100
#define BLE_SCAN_DURATION  2

BLEScan *scan;

using namespace std;

void onBLEScanComplete(BLEScanResults results) {
    int deviceCount = results.getCount();
    
    for (int i = 0; i < deviceCount; i++) {
        BLEAdvertisedDevice device = results.getDevice(i);

        string devName = device.getName();
        int serviceDataCount = device.getServiceDataCount();

        Serial.println();
        Serial.println("Found device: " + String(device.getAddress().toString().c_str()));
        Serial.println("  Name: " + String(devName.c_str()) + " (" + String(device.getRSSI()) + " dBm)");

        for (int i = 0 ; i < serviceDataCount; i++) {
            BLEUUID serviceDataUUID = device.getServiceDataUUID(i);
            string serviceData = device.getServiceData(i);

            Serial.println("  Service: " + String(serviceDataUUID.toString().c_str()) + " = " + String(serviceData.c_str()));
        }
    }
}

void setup() {
	Serial.begin(115200);

    scan = BLEDevice::getScan();
    scan->setInterval(BLE_SCAN_INTERVAL);
    scan->setWindow(BLE_SCAN_WINDOW);
    scan->setActiveScan(true);
}

void loop() {
    Serial.println("\nScanning...");
    scan->start(BLE_SCAN_DURATION, onBLEScanComplete, false);
    delay(5000);
}
