#include <Adafruit_SSD1306.h>  // Include the SSD1306 library
#include <Wire.h>  // Include the Wire library for I2C communication

Adafruit_SSD1306 display(128, 32, &Wire, -1);  // Initialize display object

const int buttonPin = 2;  // Pin number for the button
int lastButtonState = HIGH;  // Initialize the button state to HIGH

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize the display
  display.display();  // Show the splash screen (optional)
  delay(2000);  // Wait for 2 seconds
  randomSeed(analogRead(0));  // Seed the random number generator
}

void loop() {
  int buttonState = digitalRead(buttonPin);  // Read the current button state

  // Check for button press
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Wait for button debounce
    delay(20);
    // Check button state again
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) { // Confirm button is still pressed after debounce

      display.clearDisplay();  // Clear previous text
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);  // Set cursor to top-left

      int randomNumber = random(1, 5);  // Generate a random number between 1 and 4
      if (randomNumber == 1) {
        display.println("Hello, World!");  // English
      } else if (randomNumber == 2) {
        display.println("¡Hola, Mundo!");  // Spanish
      } else if (randomNumber == 3) {
        display.println("Bonjour, Monde!");  // French
      } else if (randomNumber == 4) {
        display.println("Hallo, Welt!");  // German
      } else {
        display.println("Error!");  // This line should never be reached
      }

      display.display();  // Update the display
    }
  }

  // Save the current button state for next iteration
  lastButtonState = buttonState;
}
