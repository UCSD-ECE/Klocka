#include <Adafruit_SSD1306.h>
#include <Wire.h>

Adafruit_SSD1306 display(128, 32, &Wire, -1);

const int buttonPin = 2;
int lastButtonState = HIGH;
bool isPaused = true;  // Timer state: paused or running
bool isWork = true;  // true for work time, false for break time

unsigned long previousMillis = 0;  // Stores last updated time
const long interval = 1000;  // Update interval (1 second)

int seconds = 0;
int minutes = 25;  // Start with 25 minutes for work

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.clearDisplay();
  showState();  // Show the initial state "Work"
}

void loop() {
  unsigned long currentMillis = millis();  // Current time
  
  int buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(20);
    buttonState = digitalRead(buttonPin);
    if (buttonState == LOW) {
      isPaused = !isPaused;  // Toggle pause state
      if (isPaused) {
        showState();  // Show the current state ("Work" or "Break")
      }
    }
  }
  lastButtonState = buttonState;

  // Update timer every second if not paused
  if (!isPaused && currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    seconds--;
    if (seconds < 0) {
      minutes--;
      seconds = 59;
    }

    // Handle the end of a work/break cycle
    if (minutes < 0) {
      isPaused = true;
      isWork = !isWork;  // Switch between work and break
      minutes = isWork ? 25 : 5;  // Set new minutes based on state
      seconds = 0;
      showState();
    } else {
      showTime();  // Show remaining time
    }
  }
}

// Display the remaining time on the OLED
void showTime() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  
  String timeString = "";
  if (minutes < 10) timeString += "0";
  timeString += String(minutes) + ":";
  if (seconds < 10) timeString += "0";
  timeString += String(seconds);

  int textWidth = timeString.length() * 12;
  int cursorX = (display.width() - textWidth) / 2;
  int cursorY = (display.height() - 16) / 2;

  display.setCursor(cursorX, cursorY);
  display.print(timeString);
  display.display();
}

// Display the current state ("Work" or "Break") on the OLED
void showState() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
 String stateString = isWork ? "Work" : "Break";

  int textWidth = stateString.length() * 12;
  int cursorX = (display.width() - textWidth) / 2;
  int cursorY = (display.height() - 16) / 2;

  display.setCursor(cursorX, cursorY);
  display.print(stateString);
  display.display();
}
