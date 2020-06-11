#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

int full_pin=D1;
int dustbin_full=0;

const char *ssid = "JG";
const char *password = "jaygala24";
const char *host = "http://192.168.43.48:8000/api/bin/";

void setup()
{
    pinMode(full_pin,INPUT);

    WiFi.begin(ssid, password);
  
    Serial.begin(115200);
    
    while(WiFi.status() != WL_CONNECTED) 
    {
      Serial.print(".");
      delay(500);
    }
  
    Serial.println("");

    Serial.print("Connected to ");
    Serial.println(ssid);
}

void loop()
{   
    dustbin_full=digitalRead(full_pin);
    if(dustbin_full!=1)
    {
        dustbin_full=1;
        Serial.println("Full");
    }

    else
    {
        dustbin_full=0;
        Serial.println("Empty");
    }

    HTTPClient http;
    
    http.begin(host);
    
    String str_post = String(dustbin_full);
    int httpCode = http.POST(str_post);
    String payload = http.getString();

    http.end();
}
