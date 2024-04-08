#include <WiFi.h>
#include <PubSubClient.h>

#define APP_WIFI_SSID  "CoEIoT"
#define APP_WIFI_PASS  "iot.coe.psu.ac.th"

#define APP_MQTT_SERVER  "172.30.81.141"
#define APP_MQTT_PORT    1883

String wifiMac;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setupWiFi() {
    Serial.begin(115200);

    Serial.println("Connecting to " + String(APP_WIFI_SSID) + " ...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(APP_WIFI_SSID, APP_WIFI_PASS);

    if (WiFi.waitForConnectResult() == WL_CONNECTED) {
        wifiMac = WiFi.macAddress();
        wifiMac.replace(":", "");
        wifiMac.toLowerCase();

        Serial.println("Wi-Fi connected, IP address: " + WiFi.localIP().toString());
    }
    else {
        Serial.println("Failed to connect to the Wi-Fi network, restarting...");
        delay(2000);
        ESP.restart();
    }
}

void setupMqttClient() {
    mqttClient.setServer(APP_MQTT_SERVER, APP_MQTT_PORT);

    Serial.println("Connecting to MQTT broker " + String(APP_MQTT_SERVER) + ":" + String(APP_MQTT_PORT));

    while (!mqttClient.connected()) {
        if (mqttClient.connect("iot-led")) {
            Serial.println("Connected to MQTT broker");

            // Send the string "10,20,30,40,50" to the MQTT server
            mqttClient.publish("topic/to/publish", "10,20,30,40,50");
        }
        else {
            Serial.println("Failed to connect to MQTT broker, retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void setup() {
    setupWiFi();
    setupMqttClient();
}

void loop() {
    mqttClient.loop();
}
