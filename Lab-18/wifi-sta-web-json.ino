#include <ArduinoJson.h>
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

    <form action="/setName" method="POST">
        <p>Name: <input type="text" name="name"></p>
        <input type="submit" value="Set Name">
    </form>
</body>
</html>
)";

const char *sensor_html PROGMEM = R"(
<!DOCTYPE html>
<head>
    <meta charset=\UTF-8\>
    <title>ESP32 Sensor</title>
</head>
<body>
    <h1>ESP32 Sensor</h1>
    <p>The current counter is <span id="counter">N/A</span></p>
    <script>
        setInterval(async () => {
            const response = await fetch("/getSensorData");
            const data = await response.json();

            document.getElementById("counter").innerHTML = data.counter;
        }, 1000);
    </script>
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
        webServer.send(200, "text/html", index_html);
    });

    // -------------------- Sensor Display --------------------

    webServer.on("/sensor", HTTP_GET, []() {
        webServer.send(200, "text/html", sensor_html);
    });

    webServer.on("/getSensorData", HTTP_GET, []() {
        StaticJsonDocument<200> doc;
        doc["counter"] = counter;

        String json;
        serializeJson(doc, json);

        webServer.send(200, "application/json", json);
    });

    // -------------------- HTTP Form POST --------------------

    webServer.on("/setName", HTTP_POST, []() {
        String name = webServer.arg("name");
        Serial.println("Hello, " + name);
        webServer.send(200, "text/plain", "Name set to: " + name);
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
