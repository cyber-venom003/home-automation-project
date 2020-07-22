#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const size_t capacity = JSON_OBJECT_SIZE(2) + 40;
DynamicJsonDocument doc(capacity);

void setup() {
  Serial.begin(115200);
  WiFi.begin("sonji", "OngBak$3118");
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");
  }
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin("http://192.168.43.253:3000/");
    int status_code = http.GET();
    String response = http.getString();
    Serial.println(status_code);
//    Serial.println(response);
    deserializeJson(doc, response);
    Serial.println(doc["name"].as<String>());
    http.end();
  }
  delay(10000);
}
