/* GR-CITRUS Milkcocoa Template V1.00 */

#include <Arduino.h>
#include "ESP8266.h"
#include "Milkcocoa.h"
#include "Client_ESP8266.h"
#include <Servo.h>

#define ESP_Serial      Serial3
/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "...SSID..."
#define WLAN_PASS       "...PASS..."

/************************* Your Milkcocoa Setup *********************************/

#define MILKCOCOA_APP_ID      "...YOUR_MILKCOCOA_APP_ID..."
#define MILKCOCOA_DATASTORE   "...YOUR_MILKCOCOA_DATASTORE..."

/************************* API KEY *********************************/

//#define MILKCOCOA_API_KEY     "...YOUR_MILKCOCOA_API_KEY..."
//#define MILKCOCOA_API_SECRET  "...YOUR_MILKCOCOA_API_SECRET..."

/************* Milkcocoa Setup (you don't need to change this!) ******************/

#define MILKCOCOA_SERVERPORT  1883

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266Client class to connect to the MQTT server.
ESP8266Client wifi;

const char MQTT_SERVER[] PROGMEM    = MILKCOCOA_APP_ID ".mlkcca.com";
const char MQTT_CLIENTID[] PROGMEM  = __TIME__ MILKCOCOA_APP_ID;

#ifndef MILKCOCOA_API_KEY
Milkcocoa milkcocoa = Milkcocoa(&wifi, MQTT_SERVER, MILKCOCOA_SERVERPORT, MILKCOCOA_APP_ID, MQTT_CLIENTID);
#else
Milkcocoa *milkcocoa = Milkcocoa::createWithApiKey(&wifi, MQTT_SERVER, MILKCOCOA_SERVERPORT, MILKCOCOA_APP_ID, MQTT_CLIENTID, MILKCOCOA_API_KEY, MILKCOCOA_API_SECRET);
#endif

int pin = 1;

Servo servo;
int pos = 0;

int dat;

void onpush(DataElement *pelem);

void setup(){
    
    servo.attach(2);
    servo.write(0);
    pinMode(pin, OUTPUT);

    Serial.begin(115200);
    wifi.begin(ESP_Serial, 115200);

    //while(!Serial.available()); // Wait to press any key.
    Serial.read();
    Serial.println("GR-CITRUS start");

    if (wifi.setOprToStation()) {
    Serial.print("to station ok\r\n");
    } else {
    Serial.print("to station err\r\n");
    }

    if (wifi.joinAP(WLAN_SSID, WLAN_PASS)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
    } else {
    Serial.print("Join AP failure\r\n");
    }

    if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
    } else {
    Serial.print("single err\r\n");
    }

#ifndef MILKCOCOA_API_KEY
  if(milkcocoa.on(MILKCOCOA_DATASTORE, "push", onpush)){
#else
  if(milkcocoa->on(MILKCOCOA_DATASTORE, "push", onpush)){
#endif
      Serial.println("milkcocoa on sucesss");
  }
  else {
      Serial.println("milkcocoa on failure");
  }
}

void loop()
{
    Serial.println("in loop");
#ifndef MILKCOCOA_API_KEY
    milkcocoa.loop();
#else
    milkcocoa->loop();
#endif

  DataElement elem = DataElement();

#ifndef MILKCOCOA_API_KEY
  milkcocoa.push(MILKCOCOA_DATASTORE, &elem);
#else
  milkcocoa->push(MILKCOCOA_DATASTORE, &elem);
#endif

}

void onpush(DataElement *pelem) {
    Serial.println("onpush");
    dat = pelem->getInt("t");
    Serial.println(dat);
    
    //bo
    for(pos = 0; pos <= 60; pos += 1){
        servo.write(pos);
        delay(2);
    }
    for(pos = 60; pos >= 0; pos -= 1){
        servo.write(pos);
        delay(2);
    }

    //ku
    for(pos = 0; pos <= 60; pos += 1){
        servo.write(pos);
        delay(2);
    }
    for(pos = 60; pos >= 0; pos -= 1){
        servo.write(pos);
        delay(2);
    }
    
    //no
    for(pos = 0; pos <= 60; pos += 1){
        servo.write(pos);
        delay(2);
    }
    for(pos = 60; pos >= 0; pos -= 1){
        servo.write(pos);
        delay(2);
    }
    
    //ka
    for(pos = 0; pos <= 60; pos += 1){
        servo.write(pos);
        delay(2);
    }
    for(pos = 60; pos >= 0; pos -= 1){
        servo.write(pos);
        delay(2);
    }

    //o
    for(pos = 0; pos <= 60; pos += 1){
        servo.write(pos);
        delay(2);
    }
    for(pos = 60; pos >= 0; pos -= 1){
        servo.write(pos);
        delay(2);
    }
    
    //wo
    for(pos = 0; pos <= 60; pos += 1){
        servo.write(pos);
        delay(2);
    }
    for(pos = 60; pos >= 0; pos -= 1){
        servo.write(pos);
        delay(2);
    }
    
    delay(900);
    
    //o
    for(pos = 0; pos <= 60; pos += 1){
        servo.write(pos);
        delay(3);
    }
    for(pos = 60; pos >= 0; pos -= 1){
        servo.write(pos);
        delay(2);
    }
    
    //ta
    for(pos = 0; pos <= 60; pos += 1){
        servo.write(pos);
        delay(3);
    }
    for(pos = 60; pos >= 0; pos -= 1){
        servo.write(pos);
        delay(2);
    }

    //bee
    for(pos = 0; pos <= 60; pos += 1){
        servo.write(pos);
        delay(3);
    }
    delay(700);
    
    for(pos = 60; pos >= 0; pos -= 1){
        servo.write(pos);
        delay(2);
    }
  
}