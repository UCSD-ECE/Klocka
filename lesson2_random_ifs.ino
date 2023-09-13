void setup() {

  Serial.begin(9600);
  randomSeed(analogRead(0));

}

void loop() {

  int randomNumber = random(1, 5);  // Random # between 1 & 4

  if (randomNumber == 1) {
    Serial.println("Hello, World!");  // English
  } else if (randomNumber == 2) {
    Serial.println("¡Hola, Mundo!");  // Spanish
  } else if (randomNumber == 3) {
    Serial.println("Bonjour, Monde!");  // French
  } else if (randomNumber == 4) {
    Serial.println("Hallo, Welt!");  // German
  } else {
    Serial.println("Error!");  // This line should never be reached
  }

  delay(2000); 
}
