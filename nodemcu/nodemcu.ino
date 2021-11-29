
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>



char auth[] = "t7423lMKjtWKsu5cuUbJpJ9wBcomQDF2";

char ssid[] = "DIR-825";
char pass[] = "81652075";
 
BlynkTimer timerr;
 
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
 
int firstVal, secondVal,thirdVal; // sensors 

void myTimerEvent()
{
  Blynk.virtualWrite(V0, millis() / 1000);
  
}
 
 
 
void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
 
    timerr.setInterval(1000L,sensorvalue1); 
     timerr.setInterval(1000L,sensorvalue2); 
     timerr.setInterval(1000L,sensorvalue3);
 
}
 
void loop()
{
   if (Serial.available() == 0 ) 
   {
  Blynk.run();
  timerr.run(); // Initiates BlynkTimer
   }
   
  if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    myString = myString+ rdata; 
   Serial.print(rdata);
    if( rdata == '\n')
    {
   
// new code
String l = getValue(myString, ',', 0);
String m = getValue(myString, ',', 1);
String n = getValue(myString, ',', 2); 
 
 
firstVal = l.toFloat();
secondVal = m.toFloat();
thirdVal = n.toFloat();
 
  myString = "";

    }
  }
 
}
 
void sensorvalue1()
{
int sdata = firstVal;
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, sdata);
 
}
void sensorvalue2()
{
int sdata = secondVal;
  
  Blynk.virtualWrite(V2, sdata);
 
}
void sensorvalue3()
{
int sdata = thirdVal;
  
  Blynk.virtualWrite(V3, sdata);
 
}
 
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
