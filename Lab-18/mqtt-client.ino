#include <WiFi.h>
#include <PubSubClient.h>

#define APP_WIFI_SSID  "CoEIoT"
#define APP_WIFI_PASS  "iot.coe.psu.ac.th"

#define APP_MQTT_SERVER  "172.30.81.22"
#define APP_MQTT_PORT    1883

#define LED1_PIN  2
#define LED2_PIN  26
#define LED3_PIN  25

uint8_t LED_PINS[] = {
    LED1_PIN,
    LED2_PIN,
    LED3_PIN,
};

String wifiMac;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setupHardware() {
    Serial.begin(115200);

    for (int i = 0; i < 3; i++) {
        pinMode(LED_PINS[i], OUTPUT);
        digitalWrite(LED_PINS[i], HIGH);
    }
}

void toggleLed(uint8_t ledNumber) {
    if (ledNumber < 1 || ledNumber > 3) {
        Serial.println("Invalid LED number: " + String(ledNumber));
        return;
    }

    uint8_t ledPin = LED_PINS[ledNumber - 1];
    int ledState = !digitalRead(ledPin);
    String ledStatusTopic = "device/" + wifiMac + "/led/" + String(ledNumber) + "/status";
    String ledStateStr = ledState ? "on" : "off";

    Serial.println("Toggling LED " + String(ledNumber) + " to " + ledStateStr);
    digitalWrite(ledPin, ledState);
    mqttClient.publish(ledStatusTopic.c_str(), ledStateStr.c_str(), true); // with retain flag set
}

void setupWiFi() {
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

void mqttCallback(const char *topic, byte *message, unsigned int length) {
    String topicStr(topic);
    String messageStr((uint8_t *)message, length);
    String topicTokens[5];

    Serial.println("MQTT message received on topic: " + topicStr + ", message: " + messageStr);

    for (int i = 0; i < 5; i++) {
        int slashPos = topicStr.indexOf("/");
        topicTokens[i] = topicStr.substring(0, slashPos);
        topicStr = topicStr.substring(slashPos + 1);
        // Serial.println("Slash: " + String(slashPos) + ", Token " + String(i) + ": " + topicTokens[i]);
    }

    unsigned int ledNumber = topicTokens[3].toInt();

    if (
        topicTokens[0] == "device" &&
        topicTokens[1] == wifiMac &&
        topicTokens[2] == "led" &&
        topicTokens[4] == "command" &&
        messageStr == "toggle"
    ) {
        toggleLed(ledNumber);
    }
    else {
        Serial.println("Invalid MQTT message received on topic: " + String(topic));
    }
}

void setupMqttClient() {
    mqttClient.setServer(APP_MQTT_SERVER, APP_MQTT_PORT);
    mqttClient.setCallback(mqttCallback);

    Serial.println("Connecting to MQTT broker " + String(APP_MQTT_SERVER) + ":" + String(APP_MQTT_PORT));

    while(!mqttClient.connected()) {
        if (mqttClient.connect("iot-led")) {
            // device/<MAC_ADDRESS>/led/<LED_NUMBER>/command
            String ledCommandTopic = "device/" + wifiMac + "/led/+/command";

            Serial.println("Connected to MQTT broker");
            Serial.println("Subscribing to command topic: " + ledCommandTopic);

            mqttClient.subscribe(ledCommandTopic.c_str());

            // publish initial LED status
            for (int ledNumber = 1; ledNumber <= 3; ledNumber++) {
                uint8_t ledPin = LED_PINS[ledNumber - 1];
                int ledState = digitalRead(ledPin);
                
                // device/<MAC_ADDRESS>/led/<LED_NUMBER>/status
                String ledStatusTopic = "device/" + wifiMac + "/led/" + String(ledNumber) + "/status";
                String ledStateStr = ledState ? "off" : "on";

                mqttClient.publish(ledStatusTopic.c_str(), ledStateStr.c_str());
            }
        }
        else {
            Serial.println("Failed to connect to MQTT broker, retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void setup() {
    setupHardware();
    setupWiFi();
    setupMqttClient();
}

void loop() {
    mqttClient.loop();
}
