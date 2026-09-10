/*
  Project 20: Gas & Smoke Alarm (MQ-2 Gas Sensor + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An environmental hazardous gas and smoke detection system using an MQ-2
  gas sensor module. The internal SnO2 heating coil reacts to LPG, smoke,
  methane, propane, and alcohol. When gas concentration exceeds the configured
  threshold, the comparator pulls the digital output LOW, driving the Piezo Buzzer
  to sound an alarm and displaying "GAS DETECTED!" on the 0.96" SSD1306 OLED screen.
  When air is clean, the buzzer turns off and the screen displays "SAFE".

  Connections:
  - Gas Sensor DO    -> Digital Pin 2
  - Gas Sensor VCC   -> 5V
  - Gas Sensor GND   -> GND
  - Buzzer (+)       -> Digital Pin 8
  - Buzzer (-)       -> GND
  - OLED VCC         -> 5V
  - OLED GND         -> GND
  - OLED SDA         -> Analog Pin A4
  - OLED SCL         -> Analog Pin A5

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define GAS_PIN 2
#define BUZZER_PIN 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

void setup() {
  pinMode(GAS_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int gas = digitalRead(GAS_PIN);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(35, 5);
  display.println("GAS ALARM");

  display.setTextSize(2);

  // Most MQ-2 modules output LOW when gas exceeds threshold
  if (gas == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);

    display.setCursor(5, 28);
    display.println("GAS");
    display.setCursor(5, 48);
    display.println("DETECTED!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);

    display.setCursor(35, 32);
    display.println("SAFE");
  }

  display.display();
  delay(200);
}
