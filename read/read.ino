#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>                                             // firebase library

#define FIREBASE_HOST "codeshastra-round-0.firebaseio.com/users"                         // the project name address from firebase id
#define FIREBASE_AUTH "QvEtcZawoJzJ1VWV6zEB0YENhX5vj7ebCg0gZAYj"                    // the secret key generated from firebase
#define WIFI_SSID "Dev"                                          // input your home or public wifi name 
#define WIFI_PASSWORD "qwertyuiop"                                    //password of wifi ssid
String postStr;

WiFiClient client;
 
void setup() 
{
      // Open serial communications and wait for port to open:
      Serial.begin(9600);
      while (!Serial) 
      {
         ; // wait for serial port to connect. Needed for native USB port only
      }
     
      delay(10);
 
      Serial.println("Connecting to ");
      Serial.println(WIFI_SSID);
 
 
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
 
      while (WiFi.status() != WL_CONNECTED) 
      {
            delay(500);
            Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected");

      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
}
 
void loop() 
{
    String postStr;
    while(Serial.available()) 
    {
       Serial.write(Serial.read());
       postStr += Serial.read();
       Serial.println(postStr);
    }

    Firebase.setString("Data", postStr);                                          //send initial string of led status
    
    Serial.println(postStr);
  
    delay(10000);
}
