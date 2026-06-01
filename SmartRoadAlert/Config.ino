#ifndef CONFIG_H
#define CONFIG_H

// --- Network and Cloud Credentials ---
const char* const WIFI_SSID = "YOUR_WIFI_SSID";
const char* const WIFI_PASS = "YOUR_WIFI_PASSWORD";

const char* const MQTT_SERVER = "YOUR_CLUSTER.hivemq.cloud";
const char* const MQTT_USER   = "YOUR_HIVEMQ_USER";
const char* const MQTT_PASS   = "YOUR_HIVEMQ_PASSWORD";
const int MQTT_PORT = 8883;

// --- Hardware Pin Mapping ---
const int PIN_BUZZER = 23;
const int PIN_GPS_RX = 16;  // ESP32 RX2 (connected to GPS TX)
const int PIN_GPS_TX = 17;  // ESP32 TX2 (connected to GPS RX)

// --- Calibration Parameters ---
const float IMPACT_THRESHOLD = 15.0;        // m/s² (vertical Z acceleration)
const unsigned long DEBOUNCE_TIME = 2000;   // 2-second lock after pothole detection

#endif