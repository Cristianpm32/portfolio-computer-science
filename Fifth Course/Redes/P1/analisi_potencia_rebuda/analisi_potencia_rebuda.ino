#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);      // Mode station (client WiFi)
  WiFi.disconnect();        // Desconnectar de qualsevol xarxa prèvia
  delay(2000);
  Serial.println("Setup done");
}

void loop() {
  // Escanejar xarxes WiFi disponibles
  Serial.println("Scan start");

  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
    Serial.println("No networks found");
  } else {
 
    // Llista totes les xarxes trobades
    for (int i = 0; i < n; i++) {
      // Imprimeix el SSID i RSSI de cada xarxa trobada
      Serial.print(i + 1);
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));  // Intensitat de senyal
      Serial.print(" dBm) ");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "Open" : "Secured*");
      delay(10);
    }
  }
  
  Serial.println("**************************");
  // Esperem 5 segons entre escaneigs
  delay(5000);  

}