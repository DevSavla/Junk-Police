#include "U8glib.h"
#define USE_ARDUINO_INTERRUPTS true    // Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
//#include<SoftwareSerial.h>

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 
//SoftwareSerial Serial1(2,3);

//  Variables
int myBPM=78,spike=0;
int preBPM=myBPM;
String str;
const int PulseWire = A1;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
int Threshold = 450;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

U8GLIB_SH1106_128X64 u8g(10, 9, 12, 11, 13);  // D0=13, D1=11, CS=10, DC=9, Reset=8

void setup(void) {
  Serial.begin(9600);
  //Serial1.begin(9600);
   //setSyncProvider( requestSync);  //set function to call when sync required
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   

  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
  }
}

void loop(void)
{
   u8g.firstPage();  
  do {
    //draw();
    u8g.setFont(u8g_font_unifont);  // select font
  u8g.drawStr(5, 15, "Time:03:15:00");  // put string of display at position X, Y
  u8g.drawStr(5, 30, "Date:26/01/2020");
  u8g.drawStr(5, 45, "BPM:");
  myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                               // "myBPM" hold this BPM value now. 
  myBPM=myBPM;

if (pulseSensor.sawStartOfBeat()){   
  // Constantly test to see if "a beat happened". 
  if(myBPM>0 && myBPM<150)
  {
 Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
 Serial.print("BPM: ");                        // Print phrase "BPM:" 
 Serial.println(myBPM);                        // Print the value inside of myBPM. 
  }

  if(myBPM>preBPM+60)
  {
    spike=1;
  }
}
  u8g.setPrintPos(45, 45);  // set position
  u8g.print(myBPM);  // display temperature from DHT11  
  if(spike==1)
  {
  u8g.setPrintPos(5, 60);  // set position
  u8g.print("Please chill");  // display temperature from DHT11  
  delay(2000);
  spike=0;
  }
  
  else
  {
    u8g.setPrintPos(5, 60);  // set position
  u8g.print("Hustle time");  // display temperature from DHT11
  }
  } while( u8g.nextPage() );
  
  //delay(5000);  // Delay of 5sec before accessing DHT11 (min - 2sec)
  String str=String(";")+String(myBPM)+String(";");
  //Serial.println(str);
  //Serial1.println(str);
}
