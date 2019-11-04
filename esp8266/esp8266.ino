#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include "fauxmoESP.h"

#define VELOCIDAD_PUERTO_SERIE 115200

/* Network credentials */
#define WIFI_SSID "SSID"
#define WIFI_PASS "Password"    

fauxmoESP fauxmo;

bool estadoDispositivos[13]= {false, false, false, false, false, false, false, false, false, false, false, false, false};

#define PIN_1 D0
#define PIN_2 D1
#define PIN_3 D2
#define PIN_4 D3
#define PIN_5 D4
#define PIN_6 D5
#define PIN_7 D6
#define PIN_8 D7
#define PIN_9 D8

#define DISPOSITIVO_1 "Luz del pasillo"
#define DISPOSITIVO_2 "Luz del salon uno"
#define DISPOSITIVO_3 "Luz del salon dos"
#define DISPOSITIVO_4 "Luz del salon tres"
#define DISPOSITIVO_5 "Luz del laboratorio oriente"
#define DISPOSITIVO_6 "Luz del laboratorio poniente"
#define DISPOSITIVO_7 "Luz de los cubiculos"
#define DISPOSITIVO_8 "Luz de celdas"
#define DISPOSITIVO_9 "Television"
#define GRUPO_1 "Luces"
#define TODO "TODO"
#define LABORATORIOS "Luces de los laboratorios"
#define SALONES "Luces de los salones"

void setup() {
  // Iniciamos puerto serie
  Serial.begin(VELOCIDAD_PUERTO_SERIE);

  // Iniciamos wifi
  wifiSetup();

  // Configuramos como pines de salida
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
  pinMode(PIN_5, OUTPUT);
  pinMode(PIN_6, OUTPUT);
  pinMode(PIN_7, OUTPUT);
  pinMode(PIN_8, OUTPUT);
  pinMode(PIN_9, OUTPUT);
  // Habilitamos la librería para el descubrimiento y cambio de estado
  // de los dispositivos
  fauxmo.enable(true);  

  // Damos de alta los diferentes dispositivos y grupos
  fauxmo.addDevice(DISPOSITIVO_1);   //ID0
  fauxmo.addDevice(DISPOSITIVO_2);   //ID1
  fauxmo.addDevice(DISPOSITIVO_3);   //ID2
  fauxmo.addDevice(DISPOSITIVO_4);   //ID3
  fauxmo.addDevice(DISPOSITIVO_5);   //ID4
  fauxmo.addDevice(DISPOSITIVO_6);   //ID5
  fauxmo.addDevice(DISPOSITIVO_7);   //ID6
  fauxmo.addDevice(DISPOSITIVO_8);   //ID7
  fauxmo.addDevice(DISPOSITIVO_9);   //ID8
  fauxmo.addDevice(GRUPO_1);         //ID9
  fauxmo.addDevice(TODO);            //ID10
  fauxmo.addDevice(LABORATORIOS);    //ID11
  fauxmo.addDevice(SALONES);         //ID12
  // Decimos cuales van a ser nuestras funciones para obtener estado
  // y para establecerlo...
  fauxmo.onSetState(establecerEstado);
  fauxmo.onGetState(obtenerEstado);
}


void loop() {
  // Nos quedamos esperando peticiones todo el tiempo...
  fauxmo.handle();
}

void establecerEstado(unsigned char idDispositivo, const char * nombreDispositivo, bool estado){
    Serial.printf("Dispositivo #%d (%s) estado: %s\n", idDispositivo, nombreDispositivo, estado ? "encendido" : "apagado");
    
    // Establecemos el estado del dispositivo concreto
    estadoDispositivos[idDispositivo] = estado;
    
    // En función del dispositivo recibido...
    switch (idDispositivo) {
      case 0:
        {
          digitalWrite(PIN_1, (estado));
        }
        break;
      case 1:
        {
          digitalWrite(PIN_2, (estado));
        }
        break;
      case 2:
        {
          digitalWrite(PIN_3, (estado));
        }
        break;
      case 3:
        {
          digitalWrite(PIN_4, (estado));
        }
        break;
      case 4:
        {
          digitalWrite(PIN_5, (estado));
        }
        break;
      case 5:
        {
          digitalWrite(PIN_6, (estado));
        }
        break;
      case 6:
        {
          digitalWrite(PIN_7, (estado));
        }
        break;
      case 7:
        {
          digitalWrite(PIN_8, (estado));
        }
        break;
      case 8:
        {
          digitalWrite(PIN_9, (estado));
        }
        break;
      case 9:
        {
          digitalWrite(PIN_1, (estado));
          digitalWrite(PIN_2, (estado));
          digitalWrite(PIN_3, (estado));
          digitalWrite(PIN_4, (estado));
          digitalWrite(PIN_5, (estado));
          digitalWrite(PIN_6, (estado));
          digitalWrite(PIN_7, (estado));
          digitalWrite(PIN_8, (estado));
        }
        break;
      case 10:
        {
          digitalWrite(PIN_1, (estado));
          digitalWrite(PIN_2, (estado));
          digitalWrite(PIN_3, (estado));
          digitalWrite(PIN_4, (estado));
          digitalWrite(PIN_5, (estado));
          digitalWrite(PIN_6, (estado));
          digitalWrite(PIN_7, (estado));
          digitalWrite(PIN_8, (estado));
          digitalWrite(PIN_9, (estado));
        }
        break;
      case 11:
        {
          digitalWrite(PIN_5, (estado));
          digitalWrite(PIN_6, (estado));
        }
        break;
      case 12:
        {
          digitalWrite(PIN_2, (estado));
          digitalWrite(PIN_3, (estado));
          digitalWrite(PIN_4, (estado));
        }
        break;
    }
  delay(50);
 }

bool obtenerEstado(unsigned char idDispositivo, const char * nombreDispositivo){
  return estadoDispositivos[idDispositivo];
}

void wifiSetup() {
  // Configuramos modo de wifi (estación)
   WiFi.mode(WIFI_STA);

   // Realizamos la conexión
   Serial.println ();
   Serial.printf("[WIFI] Conectando con %s ", WIFI_SSID);
   Serial.println();
   WiFi.begin(WIFI_SSID, WIFI_PASS);

   // Esperamos a que la conexión esté lista
   while (WiFi.status() != WL_CONNECTED) 
   {
      Serial.print(".");
      delay(100);
   }

   // Conexión realizada
   Serial.println(" [WIFI] Conexión realizada con éxito" );
   Serial.println();
   Serial.printf("[WIFI] Modo estación, SSID: %s, Dirección IP asignada: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
   Serial.println();
}
