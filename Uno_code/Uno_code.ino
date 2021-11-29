

#include <SoftwareSerial.h>

SoftwareSerial nodemcu(0,1);

float phsensor=0;
float turb_sensor=0;
float rate_sensor=0;

String blynkmessage;

//ph sensor
#define phPin A2          
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp;

//turbidity
int turb_Pin = A1;

// rate of flow
int X;
int Y;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;
const int rateinput = A0;

void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  //ph
  pinMode(13,OUTPUT);
  
  //turbidity
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  //rate of flow
   delay(1000);
   pinMode(rateinput,INPUT);
}

float ph(){
 for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(phPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  
  digitalWrite(13, HIGH); 
  delay(800);      
  digitalWrite(13, LOW); 
  return phValue;
 }

void loop() {
  
    
    
    //rate of flow
    X = pulseIn(rateinput, HIGH);
    Y = pulseIn(rateinput, LOW);
    TIME = X + Y;
    FREQUENCY = 1000000/TIME;
    WATER = FREQUENCY/7.5;
    delay(1000);
    
    
    //turbidity
    int sensorValue = analogRead(turb_Pin);
    int turbidity = map(sensorValue, 0, 750, 100, 0);
   
    phsensor = ph();
    turb_sensor = turbidity;
    if(WATER>0 and WATER<100){
    rate_sensor = WATER;}
    else{
      rate_sensor=0.00;}

    blynkmessage = blynkmessage+phsensor +","+turb_sensor+","+rate_sensor+",";
    Serial.println(blynkmessage);
    nodemcu.println(blynkmessage);
    
    delay(1000);
    blynkmessage = "";
    
}
