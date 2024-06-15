#include <DHT.h>
#include "DHTesp.h"
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




