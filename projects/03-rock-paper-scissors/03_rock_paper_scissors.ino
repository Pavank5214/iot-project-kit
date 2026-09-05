/*
  Project 03: Rock Paper Scissors OLED Game (Internal Pull-up Version)
  IoT Project Kit - Arduino Uno

  Description:
  An interactive Rock-Paper-Scissors game using an I2C SSD1306 128x64 OLED Display
  and 3 push buttons using Arduino's internal INPUT_PULLUP resistors.
  NO external pull-down/pull-up resistors required!

  Button Connections:
  - Rock Button    -> Digital Pin 2 -> Button -> GND
  - Paper Button   -> Digital Pin 3 -> Button -> GND
  - Scissor Button -> Digital Pin 4 -> Button -> GND

  OLED SSD1306 I2C:
  - VCC -> 5V
  - GND -> GND
  - SCL -> Analog Pin A5
  - SDA -> Analog Pin A4

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED display instance
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Button pins
const int RockButton = 2;
const int PaperButton = 3;
const int ScissorButton = 4;

// Game choices
int playerChoice;
int computerChoice;

void setup() {
  // Enable Arduino's internal pull-up resistors (NO external resistors needed)
  pinMode(RockButton, INPUT_PULLUP);
  pinMode(PaperButton, INPUT_PULLUP);
  pinMode(ScissorButton, INPUT_PULLUP);

  Serial.begin(115200);

  // Seed random number generator with floating analog pin A0
  randomSeed(analogRead(A0));

  // Initialize OLED (I2C address 0x3C)
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true) {
      // Stop if OLED initialization fails
    }
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(1);
  display.setCursor(20, 25);
  display.println("Rock Paper");
  display.setCursor(35, 40);
  display.println("Scissors!");
  display.display();

  delay(2000);
}

void loop() {
  playerChoice = 0;
  computerChoice = 0;

  // -----------------------------
  // MAIN MENU
  // -----------------------------
  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(10, 0);
  display.println("Lets Play!");

  display.setCursor(25, 12);
  display.println("Choose One");

  display.setCursor(5, 28);
  display.println("ROCK   PAPER   SCISSOR");

  display.setCursor(5, 45);
  display.println(" D2      D3       D4");

  display.display();

  // -----------------------------
  // WAIT FOR PLAYER INPUT
  // -----------------------------
  while (playerChoice == 0) {
    // INPUT_PULLUP logic:
    // Button NOT pressed = HIGH
    // Button pressed     = LOW

    if (digitalRead(RockButton) == LOW) {
      playerChoice = 1;

      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(25, 10);
      display.println("YOU");
      display.setCursor(20, 35);
      display.println("ROCK");
      display.display();

      delay(500);
    }
    else if (digitalRead(PaperButton) == LOW) {
      playerChoice = 2;

      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(25, 10);
      display.println("YOU");
      display.setCursor(15, 35);
      display.println("PAPER");
      display.display();

      delay(500);
    }
    else if (digitalRead(ScissorButton) == LOW) {
      playerChoice = 3;

      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(15, 10);
      display.println("YOU");
      display.setCursor(5, 35);
      display.println("SCISSOR");
      display.display();

      delay(500);
    }
  }

  // -----------------------------
  // COMPUTER CHOICE & DISPLAY
  // -----------------------------
  computerChoice = random(1, 4);

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("YOU");

  display.setCursor(70, 0);
  display.println("COMPUTER");

  display.drawLine(64, 0, 64, 30, WHITE);
  display.drawLine(0, 30, 128, 30, WHITE);

  // Display player's choice
  display.setCursor(5, 15);
  if (playerChoice == 1) {
    display.println("ROCK");
  } else if (playerChoice == 2) {
    display.println("PAPER");
  } else {
    display.println("SCISSOR");
  }

  // Display computer's choice
  display.setCursor(70, 15);
  if (computerChoice == 1) {
    display.println("ROCK");
  } else if (computerChoice == 2) {
    display.println("PAPER");
  } else {
    display.println("SCISSOR");
  }

  display.display();
  delay(1500);

  // -----------------------------
  // DETERMINE WINNER
  // -----------------------------
  display.clearDisplay();
  display.setTextSize(2);

  if (playerChoice == computerChoice) {
    display.setCursor(25, 25);
    display.println("TIE!");
  } else if (
    (playerChoice == 1 && computerChoice == 3) ||
    (playerChoice == 2 && computerChoice == 1) ||
    (playerChoice == 3 && computerChoice == 2)
  ) {
    display.setCursor(15, 25);
    display.println("YOU WIN!");
  } else {
    display.setCursor(5, 25);
    display.println("COMP WINS!");
  }

  display.display();
  delay(2000);

  // Return to main menu
  display.clearDisplay();
  display.display();
  delay(300);
}
