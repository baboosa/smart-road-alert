#include "Config.ino"
#include "Telemetry.ino"
#include "IotService.ino"

Telemetry telemetry;
IotService iot;

unsigned long lastDetectionTime = 0;

void setup() {
    Serial.begin(115200);
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);

    if (!telemetry.begin()) {
        Serial.println("Critical error: failed to initialize sensors!");
        while (1);
    }
    Serial.println("Sensors initialized.");

    iot.begin();
    Serial.println("System ready for urban road monitoring.");
}

void loop() {
    iot.keepAlive();
    telemetry.updateGPS();

    float currentG = telemetry.getVerticalAcceleration();
    unsigned long currentTime = millis();

    if (currentG > IMPACT_THRESHOLD && (currentTime - lastDetectionTime > DEBOUNCE_TIME)) {
        lastDetectionTime = currentTime;

        digitalWrite(PIN_BUZZER, HIGH);

        float lat = telemetry.getLatitude();
        float lng = telemetry.getLongitude();

        if (iot.publishEvent(lat, lng, currentG)) {
            Serial.printf("POTHOLE DETECTED! Lat: %f | Lng: %f | Force: %f m/s² -> Published to HiveMQ!\n", lat, lng, currentG);
        } else {
            Serial.println("Failed to publish event to broker.");
        }

        delay(400);
        digitalWrite(PIN_BUZZER, LOW);
    }
}
