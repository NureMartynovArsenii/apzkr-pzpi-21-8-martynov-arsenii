#ifndef DATASENDER_H
#define DATASENDER_H

#include <ArduinoJson.h>

class DataSender {
public:
    void sendSensorData(const char* type, float value);
};

#endif // DATASENDER_H
