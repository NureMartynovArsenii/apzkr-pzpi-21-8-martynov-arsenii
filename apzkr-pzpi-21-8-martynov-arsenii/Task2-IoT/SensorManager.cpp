#include "SensorManager.h"
#include "Config.h"
#include <ArduinoJson.h>
#include <DHT.h>
#include <math.h>

DHT dht(DHT_PIN, DHT22);

SensorManager::SensorManager() {
    analogReadResolution(10);
    pinMode(NTC_PIN, INPUT);
    pinMode(PHOTOSENSOR_PIN, INPUT);
    dht.begin();
}

float SensorManager::readLightIntensity() {
    int lightValue = analogRead(PHOTOSENSOR_PIN);
    float voltage = lightValue / 1024.0 * 5.0;
    float resistance = 2000 * voltage / (1 - voltage / 5.0);
    float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
    return isnan(lux) ? 0 : lux;
}

float SensorManager::readTemperature() {
    int adcValue = analogRead(NTC_PIN);
    if (adcValue <= 1) {
        Serial.println("NTC read error");
        return NAN;
    }
    float celsius = 1 / (log(1 / (1023.0 / adcValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
    return isnan(celsius) ? NAN : celsius;
}

float SensorManager::readHumidity() {
    float humidity = dht.readHumidity();
    return isnan(humidity) ? NAN : humidity;
}
