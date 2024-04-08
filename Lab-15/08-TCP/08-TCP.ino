#include <WiFi.h>

#define APP_WIFI_SSID  "CoEIoT"
#define APP_WIFI_PASS  "iot.coe.psu.ac.th"

void setupWiFi() {
    Serial.println("Connecting to " + String(APP_WIFI_SSID) + " ...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(APP_WIFI_SSID, APP_WIFI_PASS);

    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Failed to connect to the Wi-Fi network, restarting...");
        delay(2000);
        ESP.restart();
    }

    Serial.println("Wi-Fi connected, IP address: " + WiFi.localIP().toString());
}

#define TCP_SERVER_PORT  23

WiFiServer server;
WiFiClient client;

void setupTCPServer() {
    server.begin(TCP_SERVER_PORT);
    Serial.println("TCP Server started, connect serial monitor to " + WiFi.localIP().toString() + ":" + String(TCP_SERVER_PORT));
}

void tcpPrintln(const String &message) {
    if (server.hasClient()) {
        if (!client.connected()) {
            client.stop();
            client = server.available();
            Serial.println("New Client Connected");
        }
    }

    if (client.connected()) {
        client.println(message);
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println();

    setupWiFi();
    setupTCPServer();
}

void loop() {
    tcpPrintln("Hello from ESP32");
    delay(1000);
}
