
/* Automatic Control Parameters Definition */
#define DRY_SOIL      66
#define WET_SOIL      85
#define COLD_TEMP     12
#define HOT_TEMP      22
#define TIME_PUMP_ON  15
#define TIME_LAMP_ON  15

/* TIMER */
#define READ_BUTTONS_TM   1L  // definitions in seconds
#define READ_SOIL_TEMP_TM 2L
#define READ_SOIL_HUM_TM  10L
#define READ_AIR_DATA_TM  2L
#define SEND_UP_DATA_TM   10L
#define AUTO_CTRL_TM      60L  


/* OLED */
boolean turnOffOLED = 1;
#define SHOW_SET_UP   30


/* DHT22*/
#define DHTPIN D5
#define DHTTYPE DHT11
float airTemp=0;
float airHum=0;

/* Soil Moister */
#define soilMoisterPin A0
#define soilMoisterVcc D3
int soilMoister = 0;

/* DS18B20 Temperature Sensor */
#define ONE_WIRE_BUS 5//D1
float soilTemp;



//relays
#define PUMP_PIN D2              //PUMP (Red LED)
#define LAMP_PIN D8 //LAMP (YELLOW LED)
boolean pumpStatus = 0;
boolean lampStatus = 0;


// Buttons 
#define PUMP_ON_BUTTON D4       //push-button PUMP (Red)
#define LAMP_ON_BUTTON D7       //push-button LAMP (Green)
#define SENSORS_READ_BUTTON D6   //push-button SENSOR (yellow)*/
