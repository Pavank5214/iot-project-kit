/*
  Project 06: Digital Stopwatch with OLED Display & 3 Buttons
  IoT Project Kit - Arduino Uno

  Description:
  A digital stopwatch with Lap timer function using an I2C SSD1306 128x64 OLED display
  and 3 tactile push buttons wired using Arduino's internal INPUT_PULLUP resistors.

  Button Pin Mapping (Same as Project 03):
  - Button 1 (Pin 2) -> Start / Pause
  - Button 2 (Pin 3) -> Lap Split
  - Button 3 (Pin 4) -> Reset

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

// Button Pin Definitions (INPUT_PULLUP)
const int startStopButton = 2; // Pin 2: Start / Pause
const int lapButton       = 3; // Pin 3: Record Lap
const int resetButton     = 4; // Pin 4: Reset Timer

// Stopwatch State Variables
bool isRunning = false;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long pausedTime = 0;

// Lap Timer Variables
unsigned long lastLapTime = 0;
int lapCount = 0;
char lapBuffer[20] = "Lap --: 00:00.0";

// Button Debounce Variables
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 200; // 200ms debounce delay

void updateDisplay();
void formatTime(unsigned long ms, char* buffer);

void setup() {
  pinMode(startStopButton, INPUT_PULLUP);
  pinMode(lapButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);

  Serial.begin(115200);

  // Initialize OLED display (I2C address 0x3C)
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 OLED allocation failed"));
    while (true); // Halt execution if display fails
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  
  // Welcome Splash Screen
  display.setTextSize(1);
  display.setCursor(15, 15);
  display.println("DIGITAL STOPWATCH");
  display.setCursor(20, 35);
  display.println("IoT Project Kit");
  display.display();
  delay(1500);

  updateDisplay();
}

void loop() {
  unsigned long currentMillis = millis();

  // Update total elapsed time if stopwatch is active
  if (isRunning) {
    elapsedTime = pausedTime + (currentMillis - startTime);
  }

  // Check Button 1: Start / Pause (Pin 2)
  if (digitalRead(startStopButton) == LOW && (currentMillis - lastDebounceTime > debounceDelay)) {
    lastDebounceTime = currentMillis;

    if (!isRunning) {
      // Start or Resume
      isRunning = true;
      startTime = millis();
    } else {
      // Pause
      isRunning = false;
      pausedTime = elapsedTime;
    }
  }

  // Check Button 2: Lap Split (Pin 3)
  if (digitalRead(lapButton) == LOW && (currentMillis - lastDebounceTime > debounceDelay)) {
    lastDebounceTime = currentMillis;

    if (isRunning && elapsedTime > 0) {
      lapCount++;
      unsigned long currentLap = elapsedTime - lastLapTime;
      lastLapTime = elapsedTime;

      char lapTimeStr[12];
      formatTime(currentLap, lapTimeStr);
      sprintf(lapBuffer, "Lap %d: %s", lapCount, lapTimeStr);
    }
  }

  // Check Button 3: Reset (Pin 4)
  if (digitalRead(resetButton) == LOW && (currentMillis - lastDebounceTime > debounceDelay)) {
    lastDebounceTime = currentMillis;

    isRunning = false;
    startTime = 0;
    elapsedTime = 0;
    pausedTime = 0;
    lastLapTime = 0;
    lapCount = 0;
    sprintf(lapBuffer, "Lap --: 00:00.0");
  }

  // Redraw screen
  updateDisplay();
}

// Renders Stopwatch UI onto SSD1306 OLED
void updateDisplay() {
  display.clearDisplay();
  display.setTextColor(WHITE);

  // Title & Status Header
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("STOPWATCH");

  display.setCursor(75, 0);
  if (isRunning) {
    display.println("[RUN]");
  } else if (elapsedTime > 0) {
    display.println("[PAUSE]");
  } else {
    display.println("[READY]");
  }

  display.drawLine(0, 10, 128, 10, WHITE);

  // Main Elapsed Time Display (Large Font)
  char mainTimeStr[12];
  formatTime(elapsedTime, mainTimeStr);

  display.setTextSize(2);
  display.setCursor(10, 18);
  display.println(mainTimeStr);

  display.drawLine(0, 38, 128, 38, WHITE);

  // Lap Info & Control Legend
  display.setTextSize(1);
  display.setCursor(0, 43);
  display.println(lapBuffer);

  display.setCursor(0, 55);
  display.println("D2:St/Sp D3:Lap D4:Rst");

  display.display();
}

// Converts milliseconds to "MM:SS.d" string format
void formatTime(unsigned long ms, char* buffer) {
  unsigned long seconds = ms / 1000;
  unsigned int minutes = seconds / 60;
  seconds = seconds % 60;
  unsigned int tenths = (ms % 1000) / 100; // Tenths of a second

  sprintf(buffer, "%02u:%02lu.%1u", minutes, seconds, tenths);
}
