// #ifndef DATASENDER_H
// #define DATASENDER_H

// #include <ArduinoJson.h>

// class DataSender {
// public:
//     void sendSensorData(const char* type, float value);
//     void startMeasurement(const char* jwtToken);
//     void stopMeasurement(const char* jwtToken);
// };

// #endif // DATASENDER_H

#ifndef DATASENDER_H
#define DATASENDER_H

#include <ArduinoJson.h>

class DataSender {
public:
    void sendSensorData(const char* type, float value);
};

#endif // DATASENDER_H
