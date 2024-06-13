#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <DHT.h>
#include "DHTesp.h"

// Визначення пінів для датчиків
// const int PHOTOSENSOR_PIN = 35; 
// const int NTC_PIN = 34;         
// const int DHT_PIN = 15;
// const char* ssid = "Wokwi-GUEST"; 
// const char* password = "";
// DHT dht(DHT_PIN, DHT22);
// // Константи для рівняння Стейнхарта-Гарта
// const float BETA = 3950;

// const float GAMMA = 0.7;
// const float RL10 = 50;

// void setup() {
//   Serial.begin(9600); // Установка скорости порта
//   analogReadResolution(10); // Установка разрешения АЦП
//   pinMode(NTC_PIN, INPUT); 
//   pinMode(PHOTOSENSOR_PIN, INPUT);
//   dht.begin();
//   WiFi.begin(ssid, password); // Подключение к Wi-Fi
//   // Чекаємо поки не підключимось до Wi-Fi
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println("Connected to WiFi");
// }
// void loop() {
//   // Вимірювання та відправка освітленості
//   sendLightIntensity();
//   // Вимірювання та відправка температури
//   sendTemperature();
//   sendHumidity();
//   delay(10000); // Пауза між вимірюваннями
// }

// void sendLightIntensity() {
//   int lightValue = analogRead(PHOTOSENSOR_PIN);
//   // Конвертація в освітленість (прикладна формула, потрібна калібрування)
//   float voltage = lightValue / 1024. * 5; 
//   float resistance = 2000 * voltage / (1 - voltage / 5);
//   float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
//   if (isnan(lux)) {
//     lux = 0;
//   }
//   Serial.print("Lux: ");
//   Serial.println(lux);
//   sendSensorData("LightIntensity", lux);
// }

// void sendTemperature() {
//   int adcValue = analogRead(NTC_PIN);
//   Serial.print("ADC Value: ");
//   Serial.println(adcValue);
//   if (adcValue <= 1) {
//     Serial.println("NTC read error");
//     return;
//   }
//   // Расчет температуры без промежуточного расчета сопротивления
//   float celsius = 1 / (log(1 / (1023.0 / adcValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
//   if (isnan(celsius)) {
//     Serial.println("Failed to read from NTC sensor!");
//     return;
//   }
//   Serial.print("Temperature: ");
//   Serial.print(celsius);
//   Serial.println(" ℃");
//   sendSensorData("Temperature", celsius);
// }

// void sendHumidity() {
//   float humidity = dht.readHumidity();
//   if (isnan(humidity)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }
//   sendSensorData("Humidity", humidity);
// }

// void sendSensorData(const char* type, float value) {
//   if (WiFi.status() == WL_CONNECTED) {
//     HTTPClient http;
//     http.begin("http://5b56-2a03-7380-238a-357-4d41-19e9-3416-fed.ngrok-free.app/api/Measurements");
//     http.addHeader("Content-Type", "application/json");
//     StaticJsonDocument<200> jsonDoc;
//     jsonDoc["DeviceId"] = "ESP32_Device";
//     jsonDoc["MeasurementType"] = type;
//     jsonDoc["Value"] = String(value); // Конвертація числа в рядок
//     String requestBody;
//     serializeJson(jsonDoc, requestBody);
//     int httpResponseCode = http.POST(requestBody);
//     if (httpResponseCode > 0) {
//       String response = http.getString();
//       Serial.println(httpResponseCode);
//       Serial.println(response);
//     } else {
//       Serial.print("Error on sending POST: ");
//       Serial.println(httpResponseCode);
//     }
//     http.end();
//   } else {
//     Serial.println("Error in WiFi connection");
//   }
// }


// #include <Arduino.h>
// #include "WiFiManager.h"
// #include "SensorManager.h"
// #include "DataSender.h"
// #include "Config.h"

// const char* ssid = "Wokwi-GUEST";
// const char* password = "";

// SensorManager sensorManager;
// DataSender dataSender;

// void setup() {
//     Serial.begin(9600);
//     WiFiManager::connect(ssid, password);
// }

// void loop() {
//     float lux = sensorManager.readLightIntensity();
//     Serial.print("Lux: ");
//     Serial.println(lux);
//     dataSender.sendSensorData("LightIntensity", lux);

//     float temp = sensorManager.readTemperature();
//     if (!isnan(temp)) {
//         Serial.print("Temperature: ");
//         Serial.print(temp);
//         Serial.println(" ℃");
//         dataSender.sendSensorData("Temperature", temp);
//     }

//     float humidity = sensorManager.readHumidity();
//     if (!isnan(humidity)) {
//         Serial.print("Humidity: ");
//         Serial.println(humidity);
//         dataSender.sendSensorData("Humidity", humidity);
//     }

//     delay(10000);
// }


// #include <Arduino.h>
// #include "WiFiManager.h"
// #include "SensorManager.h"
// #include "DataSender.h"
// #include "Config.h"
// #include "DebugManager.h"

// const char* ssid = "Wokwi-GUEST";
// const char* password = "";

// SensorManager sensorManager;
// DataSender dataSender;
// DebugManager debugManager;

// void setup() {
//     Serial.begin(9600);
//     WiFiManager::connect(ssid, password);
//     debugManager.begin();
// }

// void loop() {
//     debugManager.logStatus("Starting new measurement cycle");

//     float lux = sensorManager.readLightIntensity();
//     if (!isnan(lux)) {
//         Serial.print("Lux: ");
//         Serial.println(lux);
//         dataSender.sendSensorData("LightIntensity", lux);
//         debugManager.logData("LightIntensity", lux);
//     } else {
//         debugManager.logError("Failed to read light intensity");
//     }

//     float temp = sensorManager.readTemperature();
//     if (!isnan(temp)) {
//         Serial.print("Temperature: ");
//         Serial.print(temp);
//         Serial.println(" ℃");
//         dataSender.sendSensorData("Temperature", temp);
//         debugManager.logData("Temperature", temp);
//     } else {
//         debugManager.logError("Failed to read temperature");
//     }

//     float humidity = sensorManager.readHumidity();
//     if (!isnan(humidity)) {
//         Serial.print("Humidity: ");
//         Serial.println(humidity);
//         dataSender.sendSensorData("Humidity", humidity);
//         debugManager.logData("Humidity", humidity);
//     } else {
//         debugManager.logError("Failed to read humidity");
//     }

//     debugManager.logStatus("Finished measurement cycle");
//     delay(10000);
// }


// #include <Arduino.h>
// #include "WiFiManager.h"
// #include "SensorManager.h"
// #include "DataSender.h"
// #include "Config.h"
// #include "DebugManager.h"

// const char* ssid = "Wokwi-GUEST";
// const char* password = "";

// SensorManager sensorManager;
// DataSender dataSender;
// DebugManager debugManager;

// bool isMeasuring = false;

// void setup() {
//     Serial.begin(9600);
//     WiFiManager::connect(ssid, password);
//     debugManager.begin();
// }

// void loop() {
//     if (isMeasuring) {
//         debugManager.logStatus("Starting new measurement cycle");

//         float lux = sensorManager.readLightIntensity();
//         if (!isnan(lux)) {
//             Serial.print("Lux: ");
//             Serial.println(lux);
//             dataSender.sendSensorData("LightIntensity", lux);
//             debugManager.logData("LightIntensity", lux);
//         } else {
//             debugManager.logError("Failed to read light intensity");
//         }

//         float temp = sensorManager.readTemperature();
//         if (!isnan(temp)) {
//             Serial.print("Temperature: ");
//             Serial.print(temp);
//             Serial.println(" ℃");
//             dataSender.sendSensorData("Temperature", temp);
//             debugManager.logData("Temperature", temp);
//         } else {
//             debugManager.logError("Failed to read temperature");
//         }

//         float humidity = sensorManager.readHumidity();
//         if (!isnan(humidity)) {
//             Serial.print("Humidity: ");
//             Serial.println(humidity);
//             dataSender.sendSensorData("Humidity", humidity);
//             debugManager.logData("Humidity", humidity);
//         } else {
//             debugManager.logError("Failed to read humidity");
//         }

//         debugManager.logStatus("Finished measurement cycle");
//         delay(10000);
//     } else {
//         dataSender.startMeasurement();
//         isMeasuring = true;
//         delay(5000); // Чекаємо 5 секунд перед початком вимірювань
//     }
// }


// #include <Arduino.h>
// #include "WiFiManager.h"
// #include "SensorManager.h"
// #include "DataSender.h"
// #include "Config.h"
// #include "DebugManager.h"

// const char* ssid = "Wokwi-GUEST";
// const char* password = "";
// const char* jwtToken = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiJDbGltYXRlQWRtaW4iLCJodHRwOi8vc2NoZW1hcy54bWxzb2FwLm9yZy93cy8yMDA1LzA1L2lkZW50aXR5L2NsYWltcy9uYW1lIjoiQ2xpbWF0ZUFkbWluIiwiaHR0cDovL3NjaGVtYXMubWljcm9zb2Z0LmNvbS93cy8yMDA4LzA2L2lkZW50aXR5L2NsYWltcy9yb2xlIjoiYWRtaW4iLCJleHAiOjE3MTc1NzU4NDcsImlzcyI6IllvdXJJc3N1ZXIiLCJhdWQiOiJZb3VyQXVkaWVuY2UifQ.SO0tqi93YbsKfWQextkvI6KwqhZFrJPe1A3HBQEO9fY"; // Замініть на ваш JWT токен

// SensorManager sensorManager;
// DataSender dataSender;
// DebugManager debugManager;

// bool isMeasuring = false;

// void setup() {
//     Serial.begin(9600);
//     WiFiManager::connect(ssid, password);
//     debugManager.begin();
//     checkMeasurementStatus();  // Перевірка статусу вимірювань при запуску
// }

// void loop() {
//     if (isMeasuring) {
//         debugManager.logStatus("Starting new measurement cycle");

//         float lux = sensorManager.readLightIntensity();
//         if (!isnan(lux)) {
//             Serial.print("Lux: ");
//             Serial.println(lux);
//             dataSender.sendSensorData("LightIntensity", lux);
//             debugManager.logData("LightIntensity", lux);
//         } else {
//             debugManager.logError("Failed to read light intensity");
//         }

//         float temp = sensorManager.readTemperature();
//         if (!isnan(temp)) {
//             Serial.print("Temperature: ");
//             Serial.print(temp);
//             Serial.println(" ℃");
//             dataSender.sendSensorData("Temperature", temp);
//             debugManager.logData("Temperature", temp);
//         } else {
//             debugManager.logError("Failed to read temperature");
//         }

//         float humidity = sensorManager.readHumidity();
//         if (!isnan(humidity)) {
//             Serial.print("Humidity: ");
//             Serial.println(humidity);
//             dataSender.sendSensorData("Humidity", humidity);
//             debugManager.logData("Humidity", humidity);
//         } else {
//             debugManager.logError("Failed to read humidity");
//         }

//         debugManager.logStatus("Finished measurement cycle");
//         delay(10000);
//     } else {
//         checkMeasurementStatus();  // Перевірка статусу вимірювань
//         delay(5000); // Чекаємо 5 секунд перед повторною перевіркою
//     }
// }

// void checkMeasurementStatus() {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin("http://8f9f-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/measurements/status");
//         int httpResponseCode = http.GET();

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);

//             StaticJsonDocument<200> jsonDoc;
//             deserializeJson(jsonDoc, response);
//             isMeasuring = jsonDoc["IsMeasuring"];
//         } else {
//             Serial.print("Error on getting status: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection");
//     }
// }


// #include <Arduino.h>
// #include <WiFi.h>
// #include <WebServer.h>
// #include "WiFiManager.h"
// #include "SensorManager.h"
// #include "DataSender.h"
// #include "Config.h"
// #include "DebugManager.h"

// const char* ssid = "Wokwi-GUEST";
// const char* password = "";
// String jwtToken = ""; // Глобальна змінна для зберігання токену

// SensorManager sensorManager;
// DataSender dataSender;
// DebugManager debugManager;
// WebServer server(80);

// bool isMeasuring = false;

// void handleToken() {
//     if (server.hasArg("token")) {
//         jwtToken = server.arg("token");
//         server.send(200, "text/plain", "Token received");
//         Serial.println("Received token: " + jwtToken);
//     } else {
//         server.send(400, "text/plain", "Token not received");
//     }
// }

// void setup() {
//     Serial.begin(9600);
//     WiFiManager::connect(ssid, password);
//     debugManager.begin();

//     server.on("/token", handleToken); // Додавання маршруту для обробки токену
//     server.begin();
//     Serial.println("HTTP server started");

//     // Отримуємо токен при запуску
//     getToken();
// }

// void loop() {
//     server.handleClient(); // Обробка клієнтів
//     if (jwtToken != "") {
//         // Якщо вимірювання включено, виконуємо вимірювання
//         if (isMeasuring) {
//             performMeasurements();
//             delay(10000); // Чекаємо 10 секунд перед наступним вимірюванням
//         } else {
//             checkMeasurementStatus();  // Перевірка статусу вимірювань
//             delay(5000); // Чекаємо 5 секунд перед повторною перевіркою статусу
//         }
//     } else {
//         Serial.println("JWT token is empty, trying to get a new one...");
//         getToken();
//     }
// }

// void performMeasurements() {
//     debugManager.logStatus("Starting new measurement cycle");

//     float lux = sensorManager.readLightIntensity();
//     if (!isnan(lux)) {
//         Serial.print("Lux: ");
//         Serial.println(lux);
//         dataSender.sendSensorData("LightIntensity", lux);
//         debugManager.logData("LightIntensity", lux);
//     } else {
//         debugManager.logError("Failed to read light intensity");
//     }

//     float temp = sensorManager.readTemperature();
//     if (!isnan(temp)) {
//         Serial.print("Temperature: ");
//         Serial.print(temp);
//         Serial.println(" ℃");
//         dataSender.sendSensorData("Temperature", temp);
//         debugManager.logData("Temperature", temp);
//     } else {
//         debugManager.logError("Failed to read temperature");
//     }

//     float humidity = sensorManager.readHumidity();
//     if (!isnan(humidity)) {
//         Serial.print("Humidity: ");
//         Serial.println(humidity);
//         dataSender.sendSensorData("Humidity", humidity);
//         debugManager.logData("Humidity", humidity);
//     } else {
//         debugManager.logError("Failed to read humidity");
//     }

//     debugManager.logStatus("Finished measurement cycle");
// }

// void getToken() {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin("http://3b24-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/admin/login"); // URL для отримання токену
//         http.addHeader("Content-Type", "application/json");

//         // Створюємо JSON для авторизації
//         String requestBody = "{\"username\":\"ClimateAdmin\",\"password\":\"climateadmin123\"}";
//         int httpResponseCode = http.POST(requestBody);

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);

//             StaticJsonDocument<200> jsonDoc;
//             deserializeJson(jsonDoc, response);
//             jwtToken = jsonDoc["token"].as<String>();
//             Serial.println("JWT Token: " + jwtToken);
//         } else {
//             Serial.print("Error on getting token: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection");
//     }
// }

// void checkMeasurementStatus() {
//     Serial.println("Checking measurement status...");
//     Serial.println("WiFi status: " + String(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected"));
//     Serial.println("JWT Token: " + jwtToken);

//     if (WiFi.status() == WL_CONNECTED && jwtToken != "") {
//         HTTPClient http;
//         http.begin("http://3b24-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/measurements/status");
//         http.addHeader("Authorization", "Bearer " + jwtToken); // Додавання заголовку авторизації
//         int httpResponseCode = http.GET();

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);

//             StaticJsonDocument<200> jsonDoc;
//             deserializeJson(jsonDoc, response);
//             bool newIsMeasuring = jsonDoc["IsMeasuring"];
            
//             if (isMeasuring != newIsMeasuring) {
//                 isMeasuring = newIsMeasuring;
//                 if (isMeasuring) {
//                     Serial.println("Measurement started");
//                 } else {
//                     Serial.println("Measurement stopped");
//                 }
//             }
//         } else {
//             Serial.print("Error on getting status: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection or JWT token is empty");
//     }
// }


#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "WiFiManager.h"
#include "SensorManager.h"
#include "DataSender.h"
#include "Config.h"
#include "DebugManager.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
String jwtToken = ""; // Глобальна змінна для зберігання токену

SensorManager sensorManager;
DataSender dataSender;
DebugManager debugManager;
WebServer server(80);

bool isMeasuring = false; // Переменная для измерений
bool isMeasuringInitialized = false; // Переменная для отслеживания инициализации

void handleToken() {
    if (server.hasArg("token")) {
        jwtToken = server.arg("token");
        server.send(200, "text/plain", "Token received");
        Serial.println("Received token: " + jwtToken);
    } else {
        server.send(400, "text/plain", "Token not received");
    }
}

void setup() {
    Serial.begin(9600);
    WiFiManager::connect(ssid, password);
    debugManager.begin();

    server.on("/token", handleToken); // Додавання маршруту для обробки токену
    server.begin();
    Serial.println("HTTP server started");

    // Отримуємо токен при запуску
    getToken();
}

void loop() {
    server.handleClient(); // Обробка клієнтів
    if (jwtToken != "") {
        checkMeasurementStatus(); // Перевірка статусу вимірювань
        // Якщо вимірювання включено, виконуємо вимірювання
        if (isMeasuringInitialized && isMeasuring) {
            performMeasurements();
            delay(10000); // Чекаємо 10 секунд перед наступним вимірюванням
        } else {
            Serial.println("Measurement is not active.");
            delay(5000); // Чекаємо 5 секунд перед повторною перевіркою статусу
        }
    } else {
        Serial.println("JWT token is empty, trying to get a new one...");
        getToken();
    }
}

void performMeasurements() {
    debugManager.logStatus("Starting new measurement cycle");

    float lux = sensorManager.readLightIntensity();
    if (!isnan(lux)) {
        Serial.print("Lux: ");
        Serial.println(lux);
        dataSender.sendSensorData("LightIntensity", lux);
        debugManager.logData("LightIntensity", lux);
    } else {
        debugManager.logError("Failed to read light intensity");
    }

    float temp = sensorManager.readTemperature();
    if (!isnan(temp)) {
        Serial.print("Temperature: ");
        Serial.print(temp);
        Serial.println(" ℃");
        dataSender.sendSensorData("Temperature", temp);
        debugManager.logData("Temperature", temp);
    } else {
        debugManager.logError("Failed to read temperature");
    }

    float humidity = sensorManager.readHumidity();
    if (!isnan(humidity)) {
        Serial.print("Humidity: ");
        Serial.println(humidity);
        dataSender.sendSensorData("Humidity", humidity);
        debugManager.logData("Humidity", humidity);
    } else {
        debugManager.logError("Failed to read humidity");
    }

    debugManager.logStatus("Finished measurement cycle");
}

void getToken() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin("http://2524-2a03-7380-238a-357-906c-3064-56c5-c549.ngrok-free.app/api/admin/login"); // URL для отримання токену
        http.addHeader("Content-Type", "application/json");

        // Створюємо JSON для авторизації
        String requestBody = "{\"username\":\"ClimateAdmin\",\"password\":\"climateadmin123\"}";
        int httpResponseCode = http.POST(requestBody);

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);

            StaticJsonDocument<200> jsonDoc;
            deserializeJson(jsonDoc, response);
            jwtToken = jsonDoc["token"].as<String>();
            Serial.println("JWT Token: " + jwtToken);
        } else {
            Serial.print("Error on getting token: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    } else {
        Serial.println("Error in WiFi connection");
    }
}

void checkMeasurementStatus() {
    Serial.println("Checking measurement status...");
    Serial.println("WiFi status: " + String(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected"));
    Serial.println("JWT Token: " + jwtToken);

    if (WiFi.status() == WL_CONNECTED && jwtToken != "") {
        HTTPClient http;
        http.begin("http://2524-2a03-7380-238a-357-906c-3064-56c5-c549.ngrok-free.app/api/admin/status");
        http.addHeader("Authorization", "Bearer " + jwtToken); // Додавання заголовку авторизації
        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);

            StaticJsonDocument<200> jsonDoc;
            deserializeJson(jsonDoc, response);
            bool newIsMeasuring = jsonDoc["isMeasuring"]; // Используем правильное поле JSON
            
            // Обновление переменной isMeasuring на основе ответа сервера
            isMeasuring = newIsMeasuring;
            isMeasuringInitialized = true; // <-- Обозначаем, что переменная инициализирована
            if (isMeasuring) {
                Serial.println("Measurement started");
            } else {
                Serial.println("Measurement stopped");
            }
        } else {
            Serial.print("Error on getting status: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    } else {
        Serial.println("Error in WiFi connection or JWT token is empty");
    }
}




