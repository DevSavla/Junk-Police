#include <WiFi.h>
#include <HTTPClient.h>

int fire_det=0;
int flame_sensor = 33;
int mq135=32;
int mq9=35;
int mq2=34;
int mq6=39;
int sprinkler1=25;
int sprinkler2=27;

float cur_lat=19.108642;
float cur_lon=72.837599;
float flame_detected=0;
float aqi_r=0;
float aqi_p=0;
float co_r=0;
float co_p=0;
float met_but=0;
float lpg_r=0;
int lpg_p=0;
 
const char* ssid = "JG";
const char* password =  "jaygala24";
 
void setup()
{
  Serial.begin(115200);
  pinMode(flame_sensor, INPUT);
  pinMode(mq135, INPUT);
  pinMode(mq9, INPUT);
  pinMode(mq2, INPUT);
  pinMode(mq6, INPUT);
  pinMode(sprinkler1,OUTPUT);
  pinMode(sprinkler2,OUTPUT);
  
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) 
  { 
      Serial.print(".");
      delay(500);
  }
 
  Serial.print("Connected to ");
  Serial.println(ssid);
}
 
void loop() 
{ 
  flame_detected = analogRead(flame_sensor);
  Serial.println(flame_detected);
  
  if (flame_detected < 4095)
  {
    //Serial.println("Flame detected...! take action immediately.");
    fire_det=1;
    digitalWrite(sprinkler1,HIGH);
    digitalWrite(sprinkler2,HIGH);
    delay(10000);
    digitalWrite(sprinkler1,LOW);
    digitalWrite(sprinkler2,LOW);
  }
  else
  {
    //Serial.println("No flame detected. stay cool");
    fire_det=0;
    digitalWrite(sprinkler1,LOW);
    digitalWrite(sprinkler2,LOW);
  }

  aqi_r = analogRead(mq135);
  co_r = analogRead(mq9);
  met_but = analogRead(mq2);
  lpg_r = analogRead(mq6);

  aqi_p=aqi_r/15;
  co_p=co_r/1000;

  if(lpg_r>560)
  {
    lpg_p=1;
  }

  else
  {
    lpg_p=0;
  }

  Serial.print("Fire = ");
  Serial.println(fire_det);
  Serial.print("AQI = ");
  Serial.println(aqi_p);
  Serial.print("CO = ");
  Serial.println(co_p);
  Serial.print("Methane/Butane = ");
  Serial.println(met_but);
  Serial.print("LPG = ");
  Serial.print(lpg_p);
  Serial.println(lpg_r);
  Serial.println();

  HTTPClient http;   
 
  http.begin("http://192.168.43.48:8000/api/save-data/");
    

  String postStr=String(cur_lat)+String("$")+String(cur_lon)+String("$")+String(fire_det)+String("$")+String(aqi_p)+String("$")+String(co_p)+String("$")+String(met_but)+String("$")+String(lpg_p);
 
  int httpResponseCode = http.POST(postStr);  
  String response = http.getString();                      
 
  http.end();

  //delay(2000);
}
