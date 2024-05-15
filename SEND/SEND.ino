#include "LoRa_E32.h"
#include <SoftwareSerial.h>
#include <TinyGPS++.h>           
#include <SoftwareSerial.h>  
SoftwareSerial mySerial(52, 51); // Arduino RX <-- e32 TX, Arduino TX --> e32 RX
LoRa_E32 e32ttl(&mySerial);
TinyGPSPlus gps;
#define S_RX    11                
#define S_TX    10                
SoftwareSerial SoftSerial(S_RX, S_TX);  
//bme baş
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
//bme son
// load cell baş
#include "HX711.h"  
#define DOUT 5
#define CLK 4 
#define kalibrasyon_faktoru -480 
HX711 scale(DOUT, CLK);
// load cell son  
    struct Signal  {
      float lng1 ;
      float lat1;
      float temp;
      float pres;
      float hum;
      float alt;
      float str;      
    } data;
 
void setup() {
  Serial.begin(9600);
  e32ttl.begin();
   SoftSerial.begin(9600); 
   //bme
    if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
    }
scale.tare(); // Ölçek sıfırlandı
scale.set_scale(kalibrasyon_faktoru); // Ölçek ayarlandı
}
void loop() {
        delay(50);
     ResponseStatus rs = e32ttl.sendFixedMessage(0, 63, 31, &data, sizeof(Signal));

  while (SoftSerial.available() > 0) {

    while (gps.encode(SoftSerial.read())) { 
    (data.lng1) = (gps.location.lng());
    (data.lat1) = (gps.location.lat());
    (data.temp) =(bme.readTemperature());
    (data.pres) =(bme.readPressure() / 100.0F);
    (data.hum) =(bme.readHumidity());
    (data.alt) =(bme.readAltitude(SEALEVELPRESSURE_HPA));
    (data.str) =(scale.get_units());     


    }  
  } 
  
}
 
