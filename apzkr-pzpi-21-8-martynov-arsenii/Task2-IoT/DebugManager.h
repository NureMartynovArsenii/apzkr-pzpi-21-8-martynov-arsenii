#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <Arduino.h>

class DebugManager {
public:
  void begin();
  void logStatus(const char* message);
  void logData(const char* type, float value);
  void logError(const char* message);
};

#endif
