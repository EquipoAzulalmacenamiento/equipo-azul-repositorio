#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String server= "";

const char *ssid = "INFINITUMF3RV_2.4";
const char *password = "vfA2QQq39N";
//const char *ssid = "UbeeA3E4-2.4G";
//const char *password = "40BBFCA3E4";

//--------------------------------------
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
   if (WiFi.status() == WL_CONNECTED)
  {
    if (digitalRead(BTN1) == HIGH) {    
          
            if (estado == 0) { 
            Serial.println("BT1-ENCENDIDO");
            post("BT1-ENCENDIDO");
            estado=1;
            estado2=0; 
          }
     }
  else if (digitalRead(BTN1) == LOW){   
         
           if (estado2 == 0) { 
           Serial.println("BT1-APAGADO");
           post("BT1-APAGADO");
           estado=0;
           estado2=1;
         }                  
     }
  if (digitalRead(BTN2) == HIGH) {    
           
          if (estado3 == 0) { 
          Serial.println("BT2-ENCENDIDO");
           post("BT2-ENCENDIDO");
          estado3=1;
          estado4=0;
         }
    
    }
  else if (digitalRead(BTN2) == LOW){  
         
           if (estado4 == 0) { 
            Serial.println("BT2-APAGADO");
            post("BT2-APAGADO");
             estado3=0;
             estado4=1;
           }
           
     }
   delay(1000); 
 }

}

void post(String entrada) {
  Serial.println("Inicio post");
  HTTPClient http;
  String json;
  server ="http://192.168.1.73:3000/api/product";

  StaticJsonDocument<256>doc;
  doc["entrada"]= String(entrada);
  serializeJson(doc, json);
  
  http.begin(server);
  http.addHeader("Content-Type", "application/json");
  http.POST(json);
  http.writeToStream(&Serial);
  http.end();
  Serial.println ("Termino post");
  }
