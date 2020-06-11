#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "JG";
const char* password =  "jaygala24";
 
void setup()
{
   Serial.begin(9600);
   WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) 
  { 
      Serial.println(".");
  }
 
  Serial.print("Connected to ");
  Serial.println(ssid);
}
 
void loop() 
{
   HTTPClient http;   
 
   http.begin("http://192.168.43.48:8000/api/save-data/");  

   String postStr="Hi";
 
   int httpResponseCode = http.POST(postStr);  
   String response = http.getString();                      
 
   http.end();  //Free resources
}
