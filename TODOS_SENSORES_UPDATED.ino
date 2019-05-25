#include "stationDefines.h" 


/* TIMER */
#include <SimpleTimer.h>
SimpleTimer timer;
/* DHT22*/
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SimpleDHT.h>

/* DS18B20 Temperature Sensor */
#include <DallasTemperature.h>
#include <OneWire.h>

/* DHT22*/
DHT dht (DHTPIN, DHTTYPE);

/* DS18B20 Temperature Sensor */
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);


void setup() {
  Serial.begin (9600);
  delay(10);
  Serial.println("ArduFarmBot 2");
  Serial.println(".... Starting Setup");
  Serial.println(" ");

  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(PUMP_ON_BUTTON, INPUT_PULLUP);
  pinMode(LAMP_ON_BUTTON, INPUT_PULLUP);
  pinMode(SENSORS_READ_BUTTON, INPUT_PULLUP);
  pinMode(soilMoisterVcc, OUTPUT);

  
  dht.begin();
  DS18B20.begin();

  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(LAMP_PIN, LOW);
  digitalWrite (soilMoisterVcc, LOW);
  
  waitButtonPress (SHOW_SET_UP);
  startTimers();
}

void loop()
{
  timer.run(); // Initiates SimpleTimer
}


/****************************************************************
* Read local commands (Pump and Lamp buttons are normally "HIGH"):
****************************************************************/
void readLocalCmd() 
{  
  boolean digiValue = debounce(PUMP_ON_BUTTON);
  if (!digiValue) 
  {
    pumpStatus = !pumpStatus;
    aplyCmd();
  }

  digiValue = debounce(LAMP_ON_BUTTON);
  if (!digiValue) 
  {
    lampStatus = !lampStatus;
    aplyCmd();
  }

  digiValue = debounce(SENSORS_READ_BUTTON);
  if (!digiValue) 
  {
    turnOffOLED = !turnOffOLED;
    if (!turnOffOLED){
      getDhtData();
      getSoilMoisterData();
      getSoilTempData();
      displayData();
    }
  }
}

void displayData(){

  Serial.print ("Temperatura: ");
  Serial.print (airTemp);
  Serial.print ("°C");
  Serial.println(" ");


  Serial.print ("Soil moisture: ");
  Serial.print (soilMoister);
  Serial.print ("%");
  Serial.println(" ");
  
  
  Serial.print ("Humedad ");
  Serial.print (airHum);
  Serial.print ("%");
  Serial.println(" ");

  Serial.print("Temperature soil is: ");
  Serial.print(soilTemp);   
  Serial.println();

  String pumpStatusStr;
  String lampStatusStr;
  if (pumpStatus == 1) pumpStatusStr = "on ";
  if (pumpStatus == 0) pumpStatusStr = "off";
  if (lampStatus == 1) lampStatusStr = "on ";
  if (lampStatus == 0) lampStatusStr = "off";


  Serial.print("PMP "); 
  Serial.println(pumpStatusStr);
  Serial.print("LMP "); 
  Serial.print(lampStatusStr);
  }

/***************************************************
* Receive Commands and act on actuators
****************************************************/
void aplyCmd()
{
  if (pumpStatus == 1) 
  {
    digitalWrite(PUMP_PIN, HIGH);
    if (!turnOffOLED) displayData(); 
  }
  else
      {
        digitalWrite(PUMP_PIN, LOW);
        if (!turnOffOLED) displayData();
      }
  
  if (lampStatus == 1) 
  {
    digitalWrite(LAMP_PIN, HIGH);
    if (!turnOffOLED) displayData();
  }
  else
      {
        digitalWrite(LAMP_PIN, LOW);
        if (!turnOffOLED) displayData();
      }
}



/***************************************************
* Automatically Control the Plantation based on sensors reading
****************************************************/
void autoControlPlantation(void)
{ 
  if (soilMoister < DRY_SOIL) 
  {
    turnPumpOn(); 
  }

  if (airTemp < COLD_TEMP) 
  {
    turnLampOn();
  }
}


/***************************************************
* Turn Pump On for a certain amount of time
****************************************************/
void turnPumpOn()
{
  pumpStatus = 1;
  aplyCmd();
  delay (TIME_PUMP_ON*1000);
  pumpStatus = 0;
  aplyCmd();
}


/***************************************************
* Turn Lamp On for a certain amount of time 
****************************************************/
void turnLampOn()
{
  lampStatus = 1;
  aplyCmd();
  delay (TIME_LAMP_ON*1000);
  lampStatus = 0;
  aplyCmd();
}


/* 
void loop() {
 
getDhtData();
getSoilMoisterData();
getSoilTempData();




 //Imprime los datos
  Serial.print ("Temperatura: ");
  Serial.print (airTemp);
  Serial.print ("°C");
  Serial.println(" ");


  Serial.print ("Soil moisture: ");
  Serial.print (soilMoister);
  Serial.print ("%");
  Serial.println(" ");
  
  
  Serial.print ("Humedad ");
  Serial.print (airHum);
  Serial.print ("%");
  Serial.println(" ");

  Serial.print("Temperature soil is: ");
  Serial.print(soilTemp);   
  Serial.println();


 

  delay(5000); //Tiempo de espera de impresión
}*/


 
