int flame_sensor = 33;
int mq135=32;
int mq9=35;
int mq2=34;
int mq6=39;

float flame_detected=0;
float aqi=0;
float co=0;
float met_but=0;
float lpg_but=0;

void setup()
{
  Serial.begin(115200);
  pinMode(flame_sensor, INPUT);
  pinMode(mq135, INPUT);
  pinMode(mq9, INPUT);
  pinMode(mq2, INPUT);
  pinMode(mq6, INPUT);
}

void loop()
{
  flame_detected = analogRead(flame_sensor);
  Serial.println(flame_detected);
  if (flame_detected < 2000)
  {
    Serial.println("Flame detected...! take action immediately.");
  }
  else
  {
    Serial.println("No flame detected. stay cool");
  }

  aqi = analogRead(mq135);
  co = analogRead(mq9);
  met_but = analogRead(mq2);
  lpg_but = analogRead(mq6);

  Serial.print("AQI = ");
  Serial.println(aqi);
  Serial.print("CO = ");
  Serial.println(co);
  Serial.print("Methane/Butane = ");
  Serial.println(met_but);
  Serial.print("LPG/Butane = ");
  Serial.println(lpg_but);
}
