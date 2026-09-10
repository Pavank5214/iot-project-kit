/*
  Project 19: Flame Alarm (IR Flame Sensor + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An optical fire and flame detection safety system using an Infrared (IR)
  Flame Sensor. The sensor is sensitive to light wavelengths emitted by fire
  (760nm - 1100nm). When a flame is detected, the comparator outputs LOW,
  which triggers the Piezo Buzzer alarm and displays "FLAME DETECTED!" on
  the 0.96" SSD1306 OLED display. In normal conditions, the buzzer stays
  off and the screen displays "NO FLAME".

  Connections:
  - Flame Sensor DO  -> Digital Pin 2
  - Flame Sensor VCC -> 5V
  - Flame Sensor GND -> GND
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

#define FLAME_PIN 2
#define BUZZER_PIN 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

void setup() {
  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int flame = digitalRead(FLAME_PIN);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(35, 5);
  display.println("FLAME ALARM");

  display.setTextSize(2);

  // Most flame modules output LOW when flame is detected
  if (flame == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);

    display.setCursor(5, 28);
    display.println("FLAME");
    display.setCursor(5, 48);
    display.println("DETECTED!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);

    display.setCursor(25, 32);
    display.println("NO FLAME");
  }

  display.display();
  delay(200);
}
