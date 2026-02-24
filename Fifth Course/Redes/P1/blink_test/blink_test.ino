void setup() {
  // Configura el pin 0 com a sortida
  pinMode(0, OUTPUT);
}

void loop() {
  // Posar el pin 0 a HIGH (encès)
  digitalWrite(0, HIGH);
  // Esperar 500 mil·lisegons (0.5 segons)
  delay(500);
  // Posar el pin 0 a LOW (apagat)
  digitalWrite(0, LOW);
  // Esperar altres 500 mil·lisegons (0.5 segons)
  delay(500);
}
