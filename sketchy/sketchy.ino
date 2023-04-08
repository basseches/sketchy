#include <TFT_eSPI.h> /* Graphics and font library for ST7735 driver chip */

/* Screen color */
#define TFT_GREY 0x5AEB

/* Establish a certain threshold to move the cursor. */
#define LEFT_THRESHOLD  1300
#define RIGHT_THRESHOLD 2700
#define UP_THRESHOLD    1300
#define DOWN_THRESHOLD  2700

#define RESET          0

#define COMMAND_LEFT   1
#define COMMAND_RIGHT  2
#define COMMAND_UP     4
#define COMMAND_DOWN   8

#define BUTTON_PIN 15

TFT_eSPI tft = TFT_eSPI();
int xyPins[] = {13, 12};

int xVal = 0;
int yVal = 0;
int button = 0;
int command = RESET;

/* Our coordinates, on-screen. */
int x = 0;
int y = 0;

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_GREY);
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  command = RESET;

  xVal = analogRead(xyPins[0]);
  yVal = analogRead(xyPins[1]);
  button = digitalRead(BUTTON_PIN);

  if (xVal < LEFT_THRESHOLD)
    command = command | COMMAND_LEFT;
  else if (xVal > RIGHT_THRESHOLD)
    command = command | COMMAND_RIGHT;

  if (yVal < UP_THRESHOLD)
    command = command | COMMAND_DOWN;
  else if (yVal > DOWN_THRESHOLD)
    command = command | COMMAND_UP;

  if (command & COMMAND_LEFT) {
    Serial.println("COMMAND LEFT");
    x--;
  }

  if (command & COMMAND_RIGHT) {
    Serial.println("COMMAND RIGHT");
    x++;
  }

  if (command & COMMAND_DOWN) {
    Serial.println("COMMAND UP");
    y--;
  }

  if (command & COMMAND_UP) {
    Serial.println("COMMAND DOWN");
    y++;
  }

  if (!button) {
    tft.fillScreen(TFT_GREY);
  }

  /* Draw a "circle," because a pixel is too small. */
  tft.fillCircle(x, y, 1, TFT_BLACK);

  delay(500);
}
