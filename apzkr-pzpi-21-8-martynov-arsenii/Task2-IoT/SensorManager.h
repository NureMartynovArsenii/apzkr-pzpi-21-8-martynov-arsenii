#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

class SensorManager {
public:
    SensorManager();
    float readLightIntensity();
    float readTemperature();
    float readHumidity();
};

#endif // SENSORMANAGER_H
