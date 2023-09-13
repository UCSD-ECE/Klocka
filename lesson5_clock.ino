#include <Adafruit_SSD1306.h>  // Include the SSD1306 library
#include <Wire.h>  // Include the Wire library for I2C communication

Adafruit_SSD1306 display(128, 32, &Wire, -1);  // Initialize display object

const int buttonPin = 2;  // Pin number for the reset button
int lastButtonState = HIGH;  // Initialize the button state to HIGH

unsigned long previousMillis = 0;
const long interval = 1000;  // 1 second
int seconds = 0;
int minutes = 0;
int hours = 12;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize the display
  display.display();  // Show the splash screen (optional)
  delay(2000);  // Wait for 2 seconds
}

void loop() {
  unsigned long currentMillis = millis();

  // Check for button press to reset time
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(20);  // Debounce
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) {
      hours = 12;
      minutes = 59;
      seconds = 55;
    }
  }
  lastButtonState = buttonState;

  // Update the time every second
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    seconds++;
    if (seconds >= 60) {
      minutes++;
      seconds = 0;
    }
    if (minutes >= 60) {
      hours++;
      minutes = 0;
    }
    if (hours > 12) {
      hours = 1;
    }

    // Clear the display
    display.clearDisplay();
    display.setTextSize(2);  // Increase text size to 2
    display.setTextColor(SSD1306_WHITE);

    // Centering the time on the display
    String timeString = "";
    if (hours < 10) timeString += "0";
    timeString += String(hours) + ":";
    if (minutes < 10) timeString += "0";
    timeString += String(minutes) + ":";
    if (seconds < 10) timeString += "0";
    timeString += String(seconds);

    int textWidth = timeString.length() * 12;  // 12 pixels per character at text size 2
    int cursorX = (display.width() - textWidth) / 2;
    int cursorY = (display.height() - 16) / 2;  // 16 pixels per line at text size 2

    display.setCursor(cursorX, cursorY);
    display.print(timeString);
    display.display();
  }
}
