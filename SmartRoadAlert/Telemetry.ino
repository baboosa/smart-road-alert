#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <TinyGPS++.h>
#include "Config.ino"

class Telemetry {
private:
    Adafruit_MPU6050 mpu;
    TinyGPSPlus gps;

public:
    bool begin() {
        Serial2.begin(115200, SERIAL_8N1, PIN_GPS_RX, PIN_GPS_TX);
        return mpu.begin();
    }

    void updateGPS() {
        while (Serial2.available() > 0) {
            gps.encode(Serial2.read());
        }
    }

    float getVerticalAcceleration() {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        return a.acceleration.z;
    }

    float getLatitude() {
        return gps.location.isValid() ? gps.location.lat() : 0.0;
    }

    float getLongitude() {
        return gps.location.isValid() ? gps.location.lng() : 0.0;
    }
};

#endif
