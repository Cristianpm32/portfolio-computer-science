#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// --- 1. DEFINICIÓ DE CONSTANTS  ---
const char* WIFI_SSID = "MOVISTAR_3B58";       // <--- POSA EL TEU WIFI
const char* WIFI_PASSWORD = "Mates-Info.909173@Cpc"; // <--- POSA LA CLAU WIFI
const char* MQTT_BROKER_HOST = "192.168.1.163";      // <--- POSA LA IP DEL TEU MAC
const int   MQTT_BROKER_PORT = 1883;

const char* MQTT_CLIENT_ID = "Huzzah_Subscriptor";
const char* MQTT_SUBSCRIBE_TOPIC = "board/led";

// Credencials que hem configurat:
const char* MQTT_USER = "cristianprado";
const char* MQTT_PASSWORD = "Cristianpm32";

// --- 2. INICIALITZACIÓ D'OBJECTES ---
WiFiClient wifi_client;
PubSubClient client(wifi_client); 

// --- 3. CALLBACK  ---
// Funció que s'executa quan rebem un missatge
void OnMessageReceived(char* topic, byte* payload, unsigned int length) {
  Serial.print("[");
  Serial.print(topic);
  Serial.print("] New message: "); 
  String missatge = "";
  for (int i = 0; i < length; i++) {
    missatge += (char)payload[i]; 
  }
  Serial.println(missatge);

  int valor = missatge.toInt();
  if(valor < 28){
    Serial.println(" -> Valor < 28. ENCENENT LED.");
    // NOTA: A l'ESP8266, sovint LOW encén el LED i HIGH l'apaga (funcionament invers)
    digitalWrite(BUILTIN_LED, LOW);
  }
  else{
    Serial.println(" -> Valor >= 28. APAGANT LED.");
    digitalWrite(BUILTIN_LED, HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);     // Preparem el LED 
  digitalWrite(BUILTIN_LED, HIGH);  // L'apaguem d'entrada (a l'ESP8266 HIGH sol ser apagat)
  delay(10);

  // --- CONFIGURACIÓ WIFI ---
  WiFi.mode(WIFI_STA); 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connectant al WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connectat");
  Serial.println(WiFi.localIP());

  // --- CONFIGURACIÓ MQTT ---
  client.setServer(MQTT_BROKER_HOST, MQTT_BROKER_PORT);
  client.setCallback(OnMessageReceived); 
}

void reconnect() {
  // Bucle fins a connectar
  while (!client.connected()) {
    Serial.print("Intentant connexió MQTT...");
    // Connectem amb ID, Usuari i Contrasenya
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) { 
      Serial.println("connectat!");
      client.subscribe(MQTT_SUBSCRIBE_TOPIC); 
    } else {
      Serial.print("fallat, rc=");
      Serial.print(client.state());
      Serial.println(" intentant de nou en 5 segons");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 
}