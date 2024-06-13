#include "DebugManager.h"

void DebugManager::begin() {
  Serial.println("Debug Manager Initialized");
}

void DebugManager::logStatus(const char* message) {
  Serial.print("[STATUS] ");
  Serial.println(message);
}

void DebugManager::logData(const char* type, float value) {
  Serial.print("[DATA] ");
  Serial.print(type);
  Serial.print(": ");
  Serial.println(value);
}

void DebugManager::logError(const char* message) {
  Serial.print("[ERROR] ");
  Serial.println(message);
}
