#ifndef IOT_SERVICE_H
#define IOT_SERVICE_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "Config.ino"

class IotService {
private:
    WiFiClientSecure espClient;
    PubSubClient mqttClient;

public:
    IotService() : mqttClient(espClient) {}

    void begin() {
        espClient.setInsecure(); // TLS without strict certificate validation
        mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
        connectWiFi();
    }

    void connectWiFi() {
        if (WiFi.status() == WL_CONNECTED) return;

        Serial.print("Connecting to Wi-Fi...");
        WiFi.begin(WIFI_SSID, WIFI_PASS);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nWi-Fi connected!");
    }

    void keepAlive() {
        connectWiFi();
        if (!mqttClient.connected()) {
            reconnectMQTT();
        }
        mqttClient.loop();
    }

    void reconnectMQTT() {
        while (!mqttClient.connected()) {
            Serial.print("Connecting to HiveMQ MQTT broker...");
            if (mqttClient.connect("ESP32_Pothole_Client", MQTT_USER, MQTT_PASS)) {
                Serial.println("Connected!");
            } else {
                Serial.print("Failed, rc=");
                Serial.print(mqttClient.state());
                Serial.println(" Retrying in 2 seconds...");
                delay(2000);
            }
        }
    }

    bool publishEvent(float lat, float lng, float force) {
        if (!mqttClient.connected()) return false;

        String payload = "{\"latitude\":" + String(lat, 6) +
                         ",\"longitude\":" + String(lng, 6) +
                         ",\"impact\":" + String(force, 2) + "}";

        return mqttClient.publish("urban/potholes", payload.c_str());
    }
};

#endif
