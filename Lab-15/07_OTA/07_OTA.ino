#include <WiFi.h>
#include <ElegantOTA.h>
#include <WebServer.h>

#define WIFI_SSID "CoEIoT"
#define WIFI_PASS "iot.coe.psu.ac.th"

WebServer serverEle(80);

void setup()
{
    Serial.begin(115200);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    Serial.print("Connecting ");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    String esp32IPAddress = WiFi.localIP().toString();
    Serial.println("\nWiFi connected, IP: " + esp32IPAddress);

    serverEle.begin();
    ElegantOTA.begin(&serverEle);
}

void loop()
{
    serverEle.handleClient();
    ElegantOTA.loop();
}
