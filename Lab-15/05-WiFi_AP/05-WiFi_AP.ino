#include <WiFi.h>

#define SOFTAP_WIFI_SSID  "ESP32-6410110XXX"
#define SOFTAP_WIFI_PASS  "112233445566"

void setup() {
	Serial.begin(115200);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(SOFTAP_WIFI_SSID, SOFTAP_WIFI_PASS);

    String esp32IPAddress = WiFi.softAPIP().toString();

    Serial.println();
    Serial.println("Connect to ESP32 at \"" + String(SOFTAP_WIFI_SSID) + "\" IP: " + esp32IPAddress);
}

void loop() {

}
