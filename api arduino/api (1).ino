#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "DHT.h"

String server= "";

const char *ssid = "INFINITUMF3RV_2.4";
const char *password = "vfA2QQq39N";
//const char *ssid = "UbeeA3E4-2.4G";
//const char *password = "40BBFCA3E4";

//--------------------------------------

int pin=2;
DHT dht(pin, DHT11);

#define BTN1  5//D2
#define BTN2 4//D3

 int estado=0;
 int estado2=0;
 int estado3=0;
 int estado4=0;
 

void setup()
{

   Serial.begin(9600);
   
  pinMode(BTN1, INPUT);
   pinMode(BTN2, INPUT);

 dht.begin();   

Serial.println("WiFi connected");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{

float t = dht.readTemperature();
  
   if (WiFi.status() == WL_CONNECTED)
  {
    if (digitalRead(BTN1) == HIGH) {    
          
            if (estado == 0) { 
            Serial.println("BT1-ENCENDIDO");        
            Serial.print("Temperatura: ");
            Serial.print(t);
            post("BT1-ENCENDIDO", t);
            estado=1;
            estado2=0; 
          }
     }
  else if (digitalRead(BTN1) == LOW){   
         
           if (estado2 == 0) { 
           Serial.println("BT1-APAGADO");
           Serial.print("Temperatura: ");
           Serial.print(t);
           post("BT1-APAGADO", t);
           estado=0;
           estado2=1;
         }                  
     }
  if (digitalRead(BTN2) == HIGH) {    
           
          if (estado3 == 0) { 
          Serial.println("BT2-ENCENDIDO");
          Serial.print("Temperatura: ");
          Serial.print(t);
           post("BT2-ENCENDIDO", t);
          estado3=1;
          estado4=0;
         }
    
    }
  else if (digitalRead(BTN2) == LOW){  
         
           if (estado4 == 0) { 
            Serial.println("BT2-APAGADO");
            Serial.print("Temperatura: ");
           Serial.print(t);
            post("BT2-APAGADO", t);
             estado3=0;
             estado4=1;
           }
           
     }
   delay(1000); 
 }

}

void post(String estado, float temperatura) {
  Serial.println("Inicio post");
  HTTPClient http;
  String json;
  server ="http://144.202.34.148:3011/api/product";

  StaticJsonDocument<256>doc;
  doc["estado"]= String(estado);
  doc["temperatura"]= String(temperatura);
  serializeJson(doc, json);
  
  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println ("Termino post");
  }
