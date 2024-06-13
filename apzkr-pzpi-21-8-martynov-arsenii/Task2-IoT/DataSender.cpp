// #include "DataSender.h"
// #include <WiFi.h>
// #include <HTTPClient.h>

// void DataSender::sendSensorData(const char* type, float value) {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin("http://ff0b-2a03-7380-238a-357-58e4-1457-7b3a-fd82.ngrok-free.app/api/Measurements");
//         http.addHeader("Content-Type", "application/json");
//         StaticJsonDocument<200> jsonDoc;
//         jsonDoc["DeviceId"] = "ESP32_Device";
//         jsonDoc["MeasurementType"] = type;
//         jsonDoc["Value"] = String(value);
//         String requestBody;
//         serializeJson(jsonDoc, requestBody);
//         int httpResponseCode = http.POST(requestBody);
//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }
//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection");
//     }
// }

// void DataSender::startMeasurement() {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin("http://ff0b-2a03-7380-238a-357-58e4-1457-7b3a-fd82.ngrok-free.app/api/measurements/start");
//         http.addHeader("Authorization", "Bearer your_jwt_token_here"); // Замініть на ваш JWT токен
//         int httpResponseCode = http.POST("");

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection");
//     }
// }

// void DataSender::stopMeasurement() {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin("http://ff0b-2a03-7380-238a-357-58e4-1457-7b3a-fd82.ngrok-free.app/api/measurements/stop");
//         http.addHeader("Authorization", "Bearer your_jwt_token_here"); // Замініть на ваш JWT токен
//         int httpResponseCode = http.POST("");

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection");
//     }
// }


#include "DataSender.h"
#include <WiFi.h>
#include <HTTPClient.h>

// void DataSender::sendSensorData(const char* type, float value) {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin("http://8f9f-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/measurements");
//         http.addHeader("Content-Type", "application/json");
//         StaticJsonDocument<200> jsonDoc;
//         jsonDoc["DeviceId"] = "ESP32_Device";
//         jsonDoc["MeasurementType"] = type;
//         jsonDoc["Value"] = String(value);
//         String requestBody;
//         serializeJson(jsonDoc, requestBody);
//         int httpResponseCode = http.POST(requestBody);
//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }
//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection");
//     }
// }


// #include "DataSender.h"
// #include <WiFi.h>
// #include <HTTPClient.h>

// extern String jwtToken; // Глобальна змінна для токену

// void DataSender::sendSensorData(const char* type, float value) {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin("http://3b24-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/measurements");
//         http.addHeader("Content-Type", "application/json");
//         http.addHeader("Authorization", "Bearer " + jwtToken); // Додавання заголовку авторизації
//         StaticJsonDocument<200> jsonDoc;
//         jsonDoc["DeviceId"] = "ESP32_Device";
//         jsonDoc["MeasurementType"] = type;
//         jsonDoc["Value"] = String(value);
//         String requestBody;
//         serializeJson(jsonDoc, requestBody);
//         int httpResponseCode = http.POST(requestBody);
//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }
//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection");
//     }
// }


// void DataSender::startMeasurement(const char* jwtToken) {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin("http://3b24-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/measurements/start");
//         http.addHeader("Authorization", String("Bearer ") + jwtToken);
//         int httpResponseCode = http.POST("");

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection");
//     }
// }

// void DataSender::stopMeasurement(const char* jwtToken) {
//     if (WiFi.status() == WL_CONNECTED) {
//         HTTPClient http;
//         http.begin("http://3b24-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/measurements/stop");
//         http.addHeader("Authorization", String("Bearer ") + jwtToken);
//         int httpResponseCode = http.POST("");

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection");
//     }
// }


// #include "DataSender.h"
// #include <WiFi.h>
// #include <HTTPClient.h>

// extern String jwtToken; // Глобальна змінна для токену

// void DataSender::sendSensorData(const char* type, float value) {
//     if (WiFi.status() == WL_CONNECTED && jwtToken != "") {
//         HTTPClient http;
//         http.begin("http://3b24-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/measurements");
//         http.addHeader("Content-Type", "application/json");
//         http.addHeader("Authorization", "Bearer " + jwtToken); // Додавання заголовку авторизації
//         StaticJsonDocument<200> jsonDoc;
//         jsonDoc["DeviceId"] = "ESP32_Device";
//         jsonDoc["MeasurementType"] = type;
//         jsonDoc["Value"] = String(value);
//         String requestBody;
//         serializeJson(jsonDoc, requestBody);
//         int httpResponseCode = http.POST(requestBody);
//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }
//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection or JWT token is empty");
//     }
// }

// void DataSender::startMeasurement(const char* jwtToken) {
//     if (WiFi.status() == WL_CONNECTED && jwtToken != "") {
//         HTTPClient http;
//         http.begin("http://3b24-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/measurements/start");
//         http.addHeader("Authorization", String("Bearer ") + jwtToken);
//         int httpResponseCode = http.POST("");

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection or JWT token is empty");
//     }
// }

// void DataSender::stopMeasurement(const char* jwtToken) {
//     if (WiFi.status() == WL_CONNECTED && jwtToken != "") {
//         HTTPClient http;
//         http.begin("http://3b24-2a03-7380-238a-357-502a-fc55-abc4-5831.ngrok-free.app/api/measurements/stop");
//         http.addHeader("Authorization", String("Bearer ") + jwtToken);
//         int httpResponseCode = http.POST("");

//         if (httpResponseCode > 0) {
//             String response = http.getString();
//             Serial.println(httpResponseCode);
//             Serial.println(response);
//         } else {
//             Serial.print("Error on sending POST: ");
//             Serial.println(httpResponseCode);
//         }

//         http.end();
//     } else {
//         Serial.println("Error in WiFi connection or JWT token is empty");
//     }
// }



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


