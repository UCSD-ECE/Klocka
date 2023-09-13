const int buttonPin = 2;  // Pin number for the button
int lastButtonState = HIGH;  // Previous state of the button, HIGH because the button is pulled up

void setup() {
  // Set button pin as input with internal pull-up enabled
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  // Read the current button state
  int buttonState = digitalRead(buttonPin);
  // Check for button press
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Wait for button debounce
    delay(20);
    // Check button state again
    buttonState = digitalRead(buttonPin);
   // Check button is still pressed after debounce
    if (buttonState == LOW) {
      int randomNumber = random(1, 5);
      if (randomNumber == 1) {
        Serial.println("Hello, World!");
      } else if (randomNumber == 2) {
        Serial.println("¡Hola, Mundo!");
      } else if (randomNumber == 3) {
        Serial.println("Bonjour, Monde!");
      } else if (randomNumber == 4) {
        Serial.println("Hallo, Welt!");
      } else {
        Serial.println("Error!");
      }
    }
  }
  // Save the current button state for next iteration
  lastButtonState = buttonState;
}
