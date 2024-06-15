#include "DataSender.h"
#include <WiFi.h>
#include <HTTPClient.h>

extern String jwtToken; // Глобальна змінна для токену

void DataSender::sendSensorData(const char* type, float value) {
    if (WiFi.status() == WL_CONNECTED && jwtToken != "") {
        HTTPClient http;
        http.begin("http://2524-2a03-7380-238a-357-906c-3064-56c5-c549.ngrok-free.app/api/measurements");
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer " + jwtToken); // Додавання заголовку авторизації

        StaticJsonDocument<200> jsonDoc; // Увеличен размер буфера
        jsonDoc["DeviceId"] = "ESP32_Device";
        jsonDoc["MeasurementType"] = type;
        jsonDoc["Value"] = String(value); // Преобразование в строку для соответствия типу данных на сервере
        String requestBody;
        serializeJson(jsonDoc, requestBody);

        Serial.println("Request Body: " + requestBody); // Вывод тела запроса

        int httpResponseCode = http.POST(requestBody);
        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
            Serial.println(http.errorToString(httpResponseCode)); // Печать текста ошибки
        }
        http.end();
    } else {
        Serial.println("Error in WiFi connection or JWT token is empty");
    }
}


