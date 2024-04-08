#include <WiFi.h>
#include <WebServer.h>

#define APP_WIFI_SSID  "CoEIoT"
#define APP_WIFI_PASS  "iot.coe.psu.ac.th"

WebServer webServer(80);
unsigned int counter = 0;
unsigned long previousMillis = 0;

const char *index_html PROGMEM = R"(
<!DOCTYPE html>
<head>
    <meta charset=\UTF-8\>
    <title>ESP32 Web Server</title>
</head>
<body>
    <h1>Hello from ESP32!</h1>
    <p>Counter: %d</p>
</body>
</html>
)";

void setupWiFi() {
    Serial.println();
    Serial.println("Connecting to " + String(APP_WIFI_SSID) + " ...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(APP_WIFI_SSID, APP_WIFI_PASS);

    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Failed to connect to the Wi-Fi network, restarting...");
        delay(2000);
        ESP.restart();
    }

    Serial.println("Wi-Fi connected, browse to http://" + WiFi.localIP().toString());
}

void setupWebServer() {
    webServer.on("/", HTTP_GET, []() {
        char rendered[256];
        sprintf(rendered, index_html, counter);
        webServer.send(200, "text/html", rendered);
    });

    webServer.begin();
}

void setup() {
	Serial.begin(115200);
    setupWiFi();
    setupWebServer();
}

void loop() {
    if (millis() - previousMillis > 1000) {
        previousMillis = millis();
        counter++;
    }

    webServer.handleClient();
}
