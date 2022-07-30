#include<SoftwareSerial.h>

#include "DHT.h"
#define alertsignal 13
#define redalertsignal 7//to alert the humidity has gone above the epected value
#define motor 8 

#define pump 6

#define photocellpin A0

int photocellvalue=0;

#define watervaluePower 7
#define waterValuePin A1
int waterLevel = 0;





SoftwareSerial ArduinoUno(3,2);
DHT dht;

void setup()
{

  
    
  //water level sensor pin
  pinMode(watervaluePower,OUTPUT);
  digitalWrite(watervaluePower,LOW);
  
  
  
  pinMode(alertsignal,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(pump,OUTPUT);
  Serial.begin(9600);
  Serial.println();
  

  dht.setup(12); /* set pin for data communication for the dht11 sensor */

  //nodemcu pin

  ArduinoUno.begin(4800);
  
  
  
}

void loop()
{

//  Serial.println("hello from morning");
//  delay(500);


  delay(dht.getMinimumSamplingPeriod());  /* Delay of amount equal to sampling period */  

  //Serial.println("Status\tHumidity (%)\tTemperature (C)");
   float humidity = dht.getHumidity();     /* Get humidity value */
  float temperature = dht.getTemperature(); 
  Serial.println(temperature);
  Serial.println(humidity);

  
  /*
  //get temperature and humidity of greenhouse
  getTemperatureAndHumidity();

*/
  /*
  
   //output water level in tanks
  Serial.print("water level :");
  Serial.print(getWaterLevel());
  Serial.println("\t\%");
  

  

  //get Light Intensity in the greenHouse
     photocell();
     startPump();
  
  Serial.println("-------------------------------------------------------");
 
  */

}

void getTemperatureAndHumidity(){
  delay(dht.getMinimumSamplingPeriod());  /* Delay of amount equal to sampling period */  

  Serial.println("Status\tHumidity (%)\tTemperature (C)");
   float humidity = dht.getHumidity();     /* Get humidity value */
  float temperature = dht.getTemperature(); /* Get temperature value */
  if(humidity>70){
     digitalWrite(redalertsignal,LOW);
    delay(1000);
    digitalWrite(motor,HIGH);
    digitalWrite(redalertsignal,HIGH);
    delay(1000);
   
    
  }else{
    digitalWrite(motor,LOW);
    digitalWrite(alertsignal,HIGH);
    delay(1000);
    digitalWrite(alertsignal,LOW);
    delay(200);
   
  }
   
  Serial.print(dht.getStatusString());    //  Print status of communication 
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.println(temperature, 1);
  
  
}

/*
 * connecting to thingsSPeak.com
 */

 void photocell(){
  
  photocellvalue=analogRead(photocellpin);
  Serial.print("Light intensity value: ");
  Serial.println(photocellvalue,DEC);
  delay(1000);
 }

 int getWaterLevel(){
  digitalWrite(watervaluePower,HIGH);
  delay(10);
  waterLevel =analogRead(waterValuePin);
  digitalWrite(watervaluePower,LOW);

  waterLevel=(waterLevel *100)/175;
  
  return waterLevel;
 }

 void startPump(){
  digitalWrite(pump,HIGH);
  
  
 }