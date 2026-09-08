/*
  Project 07: Buzzer Reaction Game with OLED Display
  IoT Project Kit - Arduino Uno

  Description:
  A reaction speed game using an Arduino Uno, 0.96" SSD1306 OLED display,
  a push button (INPUT_PULLUP), and a piezo buzzer. Measures the user's reaction
  time in milliseconds and penalizes false starts!

  Connections:
  - OLED VCC -> 5V
  - OLED GND -> GND
  - OLED SDA -> Analog Pin A4
  - OLED SCL -> Analog Pin A5
  - Push Button -> Digital Pin 2 -> GND (INPUT_PULLUP, NO external resistor)
  - Piezo Buzzer (+) -> Digital Pin 8
  - Piezo Buzzer (-) -> GND

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define BUTTON_PIN 2
#define BUZZER_PIN 8

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  // Seed random number generator using floating analog pin A0
  randomSeed(analogRead(A0));

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(25, 5);
  display.println("REACTION GAME");

  display.setTextSize(2);
  display.setCursor(20, 25);
  display.println("READY");

  display.display();

  delay(1000);
}

void loop() {
  // Wait for player to press button
  if (digitalRead(BUTTON_PIN) == LOW) {

    delay(50);

    // Wait until button is released
    while (digitalRead(BUTTON_PIN) == LOW);

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(15, 20);
    display.println("WAIT...");

    display.display();

    // Random delay: 2 to 5 seconds
    unsigned long randomDelay = random(2000, 5001);

    unsigned long waitStart = millis();
    bool falseStart = false;

    while (millis() - waitStart < randomDelay) {
      // Player pressed too early
      if (digitalRead(BUTTON_PIN) == LOW) {
        falseStart = true;
        break;
      }
    }

    // False start detection
    if (falseStart) {
      tone(BUZZER_PIN, 400, 300);

      display.clearDisplay();

      display.setTextSize(2);
      display.setCursor(5, 10);
      display.println("FALSE");

      display.setCursor(15, 35);
      display.println("START!");

      display.display();

      while (digitalRead(BUTTON_PIN) == LOW);
      delay(1500);

      return;
    }

    // GO signal tone
    tone(BUZZER_PIN, 2000, 150);

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(40, 20);
    display.println("GO!");

    display.display();

    // Start reaction timer
    unsigned long reactionStart = millis();

    // Wait for player button press
    while (digitalRead(BUTTON_PIN) == HIGH);

    unsigned long reactionTime = millis() - reactionStart;

    // Display result
    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(25, 5);
    display.println("REACTION TIME");

    display.setTextSize(2);
    display.setCursor(15, 25);
    display.print(reactionTime);
    display.println(" ms");

    display.setTextSize(1);
    display.setCursor(20, 50);
    display.println("Press to play");

    display.display();

    delay(500);

    // Wait for release
    while (digitalRead(BUTTON_PIN) == LOW);

    delay(1000);
  }
}
