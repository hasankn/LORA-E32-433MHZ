#include "LoRa_E32.h"
#include <SoftwareSerial.h> 
SoftwareSerial mySerial(2, 3); 
LoRa_E32 e32ttl(&mySerial);
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
} 
void loop() {

    ResponseStructContainer rsc = e32ttl.receiveMessage(sizeof(Signal));
    struct Signal data = *(Signal*) rsc.data;
    Serial.println((data.temp));

    Serial.println((data.pres));

   Serial.println((data.hum));

   Serial.println((data.alt));

   Serial.println((data.str));    

    Serial.println((data.lat1), 6);

    Serial.println((data.lng1), 6);
    rsc.close();
  
}
