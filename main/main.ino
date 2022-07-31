
// good news

/*~SMART FARM MONITORING SYSTEM
 * 
 * Created by MUSILA JOSEPH
 * SCII/02308/2018
 * TECHNICAL UNIVERSITY OF KENYA
 * Internet of Things final project
 *  2021
 */


#include<SoftwareSerial.h>


#define alertsignal 13
//#define redalertsignal 7//to alert the humidity has gone above the epected value

#define motor 5
#define fan 9
#define pump 6

#define photocellpin A5

int photocellvalue=0;

#define watervaluePower 7
 #define waterValuePin A1
int waterLevel = 0;

//soil moisture
#define soilSensorPower 2
#define soilSensorPin A2
#define DHTTYPE DHT11
#define DHT11_PIN 4
#include "DHT.h"
#define tempPin A0
int sensorInput; //The variable we will use to store the sensor input
double temp; //The variable we will use to store temperature in degrees.
#define DHTPIN 1     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11

SoftwareSerial ArduinoUno(3,2);
DHT dht(DHTPIN, DHT11);


void setup()
{

 
    
  //water level sensor pin
  pinMode(watervaluePower,OUTPUT);
  digitalWrite(watervaluePower,LOW);
  
  
  
  pinMode(alertsignal,OUTPUT);
  pinMode(motor,OUTPUT);
  pinMode(pump,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(soilSensorPower,OUTPUT);
  Serial.begin(9600);
  Serial.println();
  dht.begin();




  //nodemcu pin

  //ArduinoUno.begin(4800);
  
  
  
}

void loop()
{

   startFan();
  
  
  getTemperatureAndHumidity();
   //output water level in tanks
  Serial.print("water level :");
  Serial.print(getWaterLevel());
  Serial.println("\t\% ");
       

    if(getWaterLevel() <20){
//      startPump();
    }else{
//      stopPump();
    }

    

  //get soil moisture Content

  Serial.print("Soil Moisture value :");
  Serial.println(readSoilSensor());
  

  

  //get Light Intensity in the greenHouse
     photocell();
    startPump();
    getTemperature();
   Serial.println("-------------------------------------------------------");
 
                           

}

void getTemperatureAndHumidity(){
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));                                   
  Serial.print(hif);
  Serial.println(F("°F"));
  
}

/*
 * connecting to thingsSPeak.com
 */


void getTemperature(){
//  
//   sensorInput = analogRead(A0); 
//temp = (double)sensorInput / 1024; 
//temp = temp * 5; 
//temp = temp – 0.5; 
//temp = temp * 100; 
//
//Serial.print("Current Temperature: ");
//Serial.println(temp);
}

 void photocell(){
  
  photocellvalue=analogRead(photocellpin);
  Serial.print("Light intensity value: ");
  Serial.println(photocellvalue,DEC);
  delay(1000);
 }

 int getWaterLevel(){
  digitalWrite(watervaluePower,HIGH);
  delay(2000);
  waterLevel =analogRead(waterValuePin);
  digitalWrite(watervaluePower,LOW);

  waterLevel=(waterLevel *100)/250;
  
  return waterLevel;
 }

 void startPump(){
  digitalWrite(pump,HIGH);
  
 }
 void stopPump(){
  digitalWrite(pump,LOW);
  
 }

 int readSoilSensor(){
  digitalWrite(soilSensorPower,HIGH);
  delay(10);
  int moistureValue=analogRead(soilSensorPin);
    digitalWrite(soilSensorPower,HIGH);
  return moistureValue;
 }

 void startFan(){
  digitalWrite(fan,HIGH);
  }

  void stopFan(){
  digitalWrite(fan,LOW);
  }
