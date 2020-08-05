//#include <ArduinoJson.h>
#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "sonji"
#define WIFI_PASSWORD "OngBak$3118"

#define FIREBASE_HOST "warehouse-automation-2aa73.firebaseio.com"
#define FIREBASE_AUTH "Dhq2rvNkXNXQKPVn1N8JBG3HUColzV96fkb6UIHg"

void setup() {
 WiFi.begin(WIFI_SSID , WIFI_PASSWORD);
 Serial.begin(9600);
 Serial.print("Connecting");
 while (WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(500); 
 }
 Serial.println();
 Serial.print("connected:");
 Serial.println(WiFi.localIP());
 Firebase.begin(FIREBASE_HOST , FIREBASE_AUTH);
 pinMode(15 , OUTPUT);
 pinMode(13 , OUTPUT);
 pinMode(12 , OUTPUT);
}

void loop() {
  delay(1000);
  Firebase.stream("devices");
  delay(1000);
  if(Firebase.available()){
    boolean d1Status = Firebase.getBool("devices/device1");
    deviceControl(d1Status , 15);
    boolean d2Status = Firebase.getBool("devices/device2");
    deviceControl(d2Status , 13);
    boolean d3Status = Firebase.getBool("devices/device3");
    deviceControl(d3Status , 12);
    Serial.print("Device 1 Status: ");
    Serial.println(d1Status);
    Serial.print("Device 2 Status: ");
    Serial.println(d2Status);
    Serial.print("Device 3 Status: ");
    Serial.println(d3Status);
  }
}

void deviceControl(boolean stat , int devicePin){
  switch(stat){
      case 0: digitalWrite(devicePin , LOW);
        break;
      case 1: digitalWrite(devicePin , HIGH);
        break;
    }
}
