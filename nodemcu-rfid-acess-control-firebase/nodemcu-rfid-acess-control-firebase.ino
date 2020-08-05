#include <FirebaseArduino.h> //Use this with ArduinoJson version around 5.13.0
#include <ESP8266WiFi.h>

char tag[] ="0B00288BFA52";
char input[12];
int count = 0;        
boolean flag = 0;
boolean RFIDAuth;

void setup() {
  WiFi.begin("sonji" , "OngBak$3118");
  Serial.begin(9600);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500); 
  }
  Serial.println();
  Serial.print("connected:");
  Serial.println(WiFi.localIP());
  Firebase.begin("warehouse-automation-2aa73.firebaseio.com" , "Dhq2rvNkXNXQKPVn1N8JBG3HUColzV96fkb6UIHg");
  pinMode(15 , OUTPUT); //FAN_PIN
  pinMode(13 , OUTPUT); //TUBE_PIN
}

void loop() {
  delay(1000);
  Firebase.stream("users/1TSep17jVaUurEXdShyMb90EKk42");
  delay(1000);
  if(Firebase.available()){
      RFIDAuth = Firebase.getBool("users/1TSep17jVaUurEXdShyMb90EKk42/isAuthenticated");
      if(RFIDAuth == 0){
        checkRFIDAuth();
        delay(1000);
      }
      else{
       boolean fanStatus = Firebase.getBool("users/1TSep17jVaUurEXdShyMb90EKk42/devices/Fan");
       deviceControl(fanStatus , 15);
       boolean tubeStatus = Firebase.getBool("users/1TSep17jVaUurEXdShyMb90EKk42/devices/Bulb");
       deviceControl(tubeStatus, 13);
       Serial.print("Fan Status: ");
       Serial.println(fanStatus);
       Serial.print("Tube Status: ");
       Serial.println(tubeStatus); 
      }
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

void checkRFIDAuth(){
  if(Serial.available())// Check if there is incoming data in the RFID Reader Serial Buffer.
  {
    count = 0; // Reset the counter to zero
    /* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is empty 
       or till 12 Bytes (the ID size of our Tag) is read */
    while(Serial.available() && count < 12) 
    {
      input[count] = Serial.read(); // Read 1 Byte of data and store it in the input[] variable
      count++; // increment counter
      delay(5);
    }
    /* When the counter reaches 12 (the size of the ID) we stop and compare each value 
        of the input[] to the corresponding stored value */
    if(count == 12) // 
    {
      count =0; // reset counter varibale to 0
      flag = 1;
      /* Iterate through each value and compare till either the 12 values are 
         all matching or till the first mistmatch occurs */
      while(count<12 && flag !=0)  
      {
        if(input[count]==tag[count])
        flag = 1; // everytime the values match, we set the flag variable to 1
        else
        flag= 0; 
                               /* if the ID values don't match, set flag variable to 0 and 
                                  stop comparing by exiting the while loop */
        count++; // increment i
      }
    }
    if(flag == 1) // If flag variable is 1, then it means the tags match
    {
      Serial.println("Access Allowed!");
      for(count=0; count<12; count++) 
      {
        input[count]= 'F';
      }
      count = 0;
      Firebase.setBool("users/1TSep17jVaUurEXdShyMb90EKk42/isAuthenticated" , true);
    }
    else
    {
      Serial.println("Access Denied"); // Incorrect Tag Message
      for(count=0; count<12; count++) 
      {
        input[count]= 'F';
      }
      count = 0;
    }
    /* Fill the input variable array with a fixed value 'F' to overwrite 
    all values getting it empty for the next read cycle */
     // Reset counter variable
  }
}
