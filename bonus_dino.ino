#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_PIN 2

const uint8_t ground_data[] = {
  B11111111, B11111111, B11111111, B11111111,
  B00000000, B00000000, B00000000, B00000000
};


/*
const uint8_t dino_data[] = {
  B00111100,
  B01111110,
  B11111110,
  B11111111,
  B01111110,
  B11011011,
  B10000001
};
*/

const unsigned char dino_data[] PROGMEM = {
  0x00, 0x00, 0x00, 0xbc, 0x01, 0xfc, 0x01, 0xfc, 0x01, 0xe0, 0x01, 0xe0, 0x01, 0xc0, 0x47, 0xe0, 
  0x6f, 0xc0, 0x7f, 0xc0, 0x7f, 0x80, 0x3f, 0x80, 0x0f, 0x00, 0x09, 0x00, 0x09, 0x00, 0x09, 0x80
};

const unsigned char obstacle_data [] PROGMEM = {
  0x30, 0x30, 0x34, 0xb4, 0xf4, 0xbc, 0xb8, 0x70, 0x30, 0x30, 0x30, 0x30
};

/*
const uint8_t obstacle_data[] = {
  B11111111,
  B11111111,
  B11111111
};
*/

bool gameRunning = false;
int dino_y = 16;
bool jump = false;
int jump_height = 0;
int obstacle_x = 120;
int score = 0;
int obstacle_spawn_offset = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  if (!gameRunning) {
    displayStartScreen();
    if (!digitalRead(BUTTON_PIN)) {
      gameRunning = true;
      delay(200);
    }
  } else {
    if (!digitalRead(BUTTON_PIN) && !jump) {
      jump = true;
    }

    if (jump) {
      if (jump_height < 8) {
        dino_y -= 2;
        jump_height++;
      } else if (jump_height < 16) {
        dino_y += 2;
        jump_height++;
      } else {
        jump_height = 0;
        jump = false;
      }
    }

    obstacle_x -= 4;
    
    /*
    if (obstacle_x <= -8) {
      obstacle_x = 120;
      score++;
    }
    */

    if (obstacle_x <= -8) {
  obstacle_x = 120 + obstacle_spawn_offset;
  obstacle_spawn_offset = random(0, 60); // Randomize the spawn offset between 0 and 60 pixels
  score++;
}

    

    displayGameScreen();

    if (collision()) {
      gameOver();
    }

    delay(50);
  }
}

bool collision() {
  return (dino_y >= 16) && (obstacle_x >= 13) && (obstacle_x <= (13 + 8));
}

void displayStartScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(25, 5);
  display.println("Another Dino Game");
  display.setCursor(31, 20);
  display.println("Press to Start");
  display.display();
}

void displayGameScreen() {
  display.clearDisplay();

  display.drawBitmap(0, 24, ground_data, 128, 4, WHITE);

  //display.drawBitmap(13, dino_y, dino_data, 8, 7, WHITE);

  display.drawBitmap(13, dino_y, dino_data, 15, 16, WHITE);

  //display.drawBitmap(obstacle_x, 19, obstacle_data, 8, 8, WHITE);
  display.drawBitmap(obstacle_x, 19, obstacle_data, 7, 12, WHITE);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(100, 0);
  display.print(score);

  display.display();
}

void gameOver() {
  gameRunning = false;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(35, 5);
  display.println("Game Over!");
  display.setCursor(30, 15);
  display.print("Score: ");
  display.print(score);
  display.setCursor(15, 25);
  display.println("Press to Restart");
  display.display();
  delay(2000);

  while (digitalRead(BUTTON_PIN)) {
    // Wait for button press
  }
  delay(200);
  resetGame();
}

void resetGame() {
  dino_y = 16;
  jump = false;
  jump_height = 0;
  obstacle_x = 120;
  score = 0;
}
