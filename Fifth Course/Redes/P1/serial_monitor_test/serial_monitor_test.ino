//#include "ESP8266WiFi.h"  

String incomingData;        // Variable per emmagatzemar les dades rebudes
boolean TransmisioCompleta = false; // Variable per indicar si la transmissió ha acabat (incompleta)

void setup() {
  // Aquí va el codi d'configuració, s'executa un cop al iniciar
  Serial.begin(9600);      // Inicialitza la comunicació sèrie a 9600 bauds
  delay(1000);             // Espera 1 segon per estabilitzar
  Serial.println("Hello World");  // Envia missatge de prova al monitor sèrie
}

void loop() {
  // Codi principal que s'executa repetidament
  if(Serial.available()){          // Comprova si hi ha dades disponibles al port sèrie
    Serial.print(" > ");           // Mostra un prefix per a les dades rebudes
    Serial.println(Serial.readString());  // Llegeix i mostra la cadena rebuda
    //serialEvent();               
  }
}
