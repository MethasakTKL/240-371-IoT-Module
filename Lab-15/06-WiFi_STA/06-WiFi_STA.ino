#include <WiFi.h>

#define WIFI_SSID  "CoEIoT"
#define WIFI_PASS  "iot.coe.psu.ac.th"

void setup() {
	Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("Connecting ");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    String esp32IPAddress = WiFi.localIP().toString();
    Serial.println("\nWiFi connected, IP: " + esp32IPAddress);
}

void loop() {

}
