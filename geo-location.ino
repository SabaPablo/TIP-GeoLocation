#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>

#include <ESP8266WiFi.h>
#include <string>
#include <sstream>
#include <TinyGPS++.h>           // Include TinyGPS++ library
#include <SoftwareSerial.h>      // Include software serial library

#define WIFI_SSID "RedSaba"
#define WIFI_PASSWORD "Unq1234567"
#define FIREBASE_HOST "https://petheroes-f1676.firebaseio.com/"
#define FIREBASE_AUTH "cNGpXUryyD8hVg9Wz1tm6aZVrmaz6CW9iOrHnpaV"

TinyGPSPlus gps;
 
#define S_RX    D6                // Define software serial RX pin
#define S_TX    D7                // Define software serial TX pin
//3. Declare the Firebase Data object in global scope

FirebaseData firebaseData;



SoftwareSerial SoftSerial(S_RX, S_TX);    // Configure SoftSerial library


String pet_id = "aa3432dde";
int count = 61;

void setup() {
  Serial.begin(115200);
  SoftSerial.begin(9600);  

  delay(2000);
  Serial.println('\n');
  
  wifiConnect();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  delay(10);
}

void loop() { 
 // set value 


 delay(1000); 
 // update value 
 while(1){
 location();
 }
 Firebase.setFloat(firebaseData,"number", 43.0); 

 delay(1000); 
 
} 

std::string doubleToString(double val)
{  
  String SerialData="";
  SerialData = String(val,6);
  return SerialData.c_str();
}


void wifiConnect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); Serial.println(" ...");

  int teller = 0;
  while (WiFi.status() != WL_CONNECTED)
  {                                       // Wait for the W#include <FirebaseCloudMessaging.h>
    delay(1000);
    Serial.print(++teller); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}


void location() {
 
  while (SoftSerial.available() > 0) {
 
    if (gps.encode(SoftSerial.read())) {

       if (gps.location.isValid() && gps.altitude.isValid() && gps.speed.isValid() && gps.date.isValid() && gps.satellites.isValid()) {
        
        if(count != gps.time.minute()){
          
          std::string s;
          
          s.append("{\"pulse\":160, \"location\":{\"long\": \"");
          
          s.append(doubleToString(gps.location.lng()));
          s.append("\" ,\"lat\": \"");
          s.append(doubleToString(gps.location.lat()));
          s.append("\" ,\"alt\": \"");
          s.append(doubleToString(gps.altitude.meters()));
          s.append("\" ,\"speed\": \"");
          s.append(doubleToString(gps.speed.kmph()));
          s.append("\"}}");
          Serial.print(s.c_str());
          Firebase.setJSON(firebaseData, "/pets/"+ pet_id, s.c_str());
          Serial.print("Send Json to Firebase");
          
        }
        count = gps.time.minute();
       }
       
      if (gps.location.isValid()) {
        Serial.print("Latitude   = ");
        Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude  = ");
        Serial.println(gps.location.lng(), 6);
      }
      else
        Serial.println("Location Invalid");
 
      if (gps.altitude.isValid()) {
        Serial.print("Altitude   = ");
        Serial.print(gps.altitude.meters());
        Serial.println(" meters");
      }
      else
        Serial.println("Altitude Invalid");
 
      if (gps.speed.isValid()) {
        Serial.print("Speed      = ");
        Serial.print(gps.speed.kmph());
        Serial.println(" kmph");
      }
      else
        Serial.println("Speed Invalid");
 
      if (gps.time.isValid()) {
        Serial.print("Time (GMT) : ");
        if(gps.time.hour() < 10)     Serial.print("0");
        Serial.print(gps.time.hour());
        Serial.print(":");
        if(gps.time.minute() < 10)   Serial.print("0");
        Serial.print(gps.time.minute());
        Serial.print(":");
        if(gps.time.second() < 10)   Serial.print("0");
        Serial.println(gps.time.second());
      }
      else
        Serial.println("Time Invalid");
 
      if (gps.date.isValid()) {
        Serial.print("Date       : ");
        if(gps.date.day() < 10)      Serial.print("0");
        Serial.print(gps.date.day());
        Serial.print("/");
        if(gps.date.month() < 10)    Serial.print("0");
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.println(gps.date.year());
      }
      else
        Serial.println("Date Invalid");
 
      if (gps.satellites.isValid()) {
        Serial.print("Satellites = ");
        Serial.println(gps.satellites.value());
      }
      else
        Serial.println("Satellites Invalid");
 
    }
 
  }
 
}
