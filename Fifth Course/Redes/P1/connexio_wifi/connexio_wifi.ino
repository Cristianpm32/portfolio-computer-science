#include "ESP8266WiFi.h"

// Variables globals
String ssid = "";           // Per emmagatzemar el nom de la xarxa
String password = "";       // Per emmagatzemar la contrasenya
int contador = 0;           // Comptador per timeout de connexió
char* c_ssid;              // SSID en format char* per la llibreria WiFi
char* c_pwd;               // Password en format char* per la llibreria WiFi

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);      // Mode station (client WiFi)
  WiFi.disconnect();        // Desconnectar de qualsevol xarxa prèvia
  delay(2000);
  Serial.println("Setup done");
}

// Converteix String a char* i reserva memòria
void strToChar(String txt, char* &c){
  if(WiFi.status() != WL_CONNECTED){
    int len = txt.length()+1;
    Serial.println("*****************");
    c = (char*)malloc(len);  // Reservar memòria dinàmica
    for(int i = 0; i<len-1; i++){
      c[i] = txt[i];        // Copiar caràcter per caràcter
    }
    c[len-1] = '\0';        // Acabar string amb null
  }
}

// Selecció de xarxa WiFi per consola sèrie
void wifiNetworkSelection(void) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("SSID? >");
    
    // Esperar entrada de l'usuari
    while (!Serial.available()) {
      delay(100);
    }
    ssid = Serial.readString();
    ssid.trim();  // Netejar caràcters extres
    
    Serial.print("SSID selected > ");
    Serial.println(ssid);
    delay(1000);
    strToChar(ssid,c_ssid);  // Convertir a char*

    // Demanar contrasenya
    Serial.print("Password? >");
    while (!Serial.available()) {
      delay(100);
    }
    password = Serial.readString();
    password.trim();
    Serial.println(password);
    delay(1000);
    strToChar(password,c_pwd);  // Convertir a char*
  }
}

// Connectar a la xarxa WiFi
void connectToWiFi(void) {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(c_ssid, c_pwd);
    contador = 0;
    
    Serial.println("Connecting to WiFi...");
    
    // Intentar connexió amb timeout
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      contador++;
      
      if (contador >= 15) {  // Timeout després de 15 segons
        Serial.println("\nTimeout - Could not connect!");
        return;
      }
    }
    
    Serial.println("\nConnected! IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  // Escanejar xarxes WiFi disponibles
  Serial.println("Scanning networks...");
  int n = WiFi.scanNetworks();
  
  if (n == 0) {
    Serial.println("No networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found:");
    
    // Llistar totes les xarxes trobades
    for (int i = 0; i < n; i++) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));  // Intensitat de senyal
      Serial.print(" dBm) ");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "Open" : "Secured*");
    }
  }
  
  Serial.println("\n----------------------------");
  
  // Cada 30 segons o en el primer escaneig, demanar connexió
  static unsigned long lastConnectTime = 0;
  static bool firstScan = true;
  
  if (firstScan || millis() - lastConnectTime > 30000) {
    firstScan = false;
    lastConnectTime = millis();
    
    wifiNetworkSelection();
    connectToWiFi();
  }
  
  // Mostrar estat actual de la connexió
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("Connected to: ");
    Serial.print(ssid);
    Serial.print(" | RSSI: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
  } else {
    Serial.println("Not connected to WiFi");
  }
  
  delay(10000);  // Esperar 10 segons entre escaneigs
}