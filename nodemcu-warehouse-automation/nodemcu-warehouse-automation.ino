#include <ArduinoJson.h>

#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "sonji"
#define WIFI_PASSWORD "OngBak$3118"

#define FIREBASE_HOST "warehouse-automation-2aa73.firebaseio.com"
#define FIREBASE_AUTH "Dhq2rvNkXNXQKPVn1N8JBG3HUColzV96fkb6UIHg"

void setup() {
 WiFi.begin(WIFI_SSID , WIFI_PASSWORD);
 Serial.begin(115200);
 Serial.print("Connecting");
 while (WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(500); 
 }
 Serial.println();
 Serial.print("connected:");
 Serial.println(WiFi.localIP());
 Firebase.begin(FIREBASE_HOST , FIREBASE_AUTH);
 pinMode(4 , OUTPUT);
}

void loop() {
  delay(1000);
  Firebase.stream("device1");
  delay(1000);
  if(Firebase.available()){
    int i = Firebase.getInt("device1");
    Serial.println(i);
    switch(i){
      case 1: digitalWrite(4 , HIGH);
        break;
      case 2: digitalWrite(4 , LOW);
        break;
    }
  }
}
