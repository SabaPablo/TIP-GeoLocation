#include <FirebaseESP8266.h>
#include <FirebaseESP8266HTTPClient.h>

#include <ESP8266WiFi.h>

#define WIFI_SSID "RedSaba"
#define WIFI_PASSWORD "Unq1234567"
#define FIREBASE_HOST "https://petheroes-f1676.firebaseio.com/"
#define FIREBASE_AUTH "cNGpXUryyD8hVg9Wz1tm6aZVrmaz6CW9iOrHnpaV"

//3. Declare the Firebase Data object in global scope
FirebaseData firebaseData;

String pet_id = "aa3432dde";

void setup()
{
Serial.begin(115200);

  delay(2000);
  Serial.println('\n');
  
  wifiConnect();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  delay(10);
}

void loop() { 
 // set value 
String jsonData = "{\"pulse\":160, \"location\":{\"long\":123.456,\"lat\":52.332}}";

Firebase.setJSON(firebaseData, "/pets/"+ pet_id, jsonData);


 delay(1000); 
 // update value 
 Firebase.setFloat(firebaseData,"number", 43.0); 

 delay(1000); 
 
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
