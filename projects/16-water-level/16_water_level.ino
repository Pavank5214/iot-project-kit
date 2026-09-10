/*
  Project 16: Water Level Indicator (Water Level Sensor + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  Measures water depth/level using an analog water level sensor module
  and displays the percentage (0 - 100%) and water category (LOW, MEDIUM,
  HIGH, VERY HIGH, FULL) on a 0.96" SSD1306 OLED screen.

  Connections:
  - Water Level Sensor Signal (S) -> Analog Pin A0
  - Water Level Sensor VCC (+)    -> 5V
  - Water Level Sensor GND (-)    -> GND
  - OLED VCC                      -> 5V
  - OLED GND                      -> GND
  - OLED SDA                      -> Analog Pin A4
  - OLED SCL                      -> Analog Pin A5

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SENSOR A0

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int value = analogRead(SENSOR);

  int level = map(value, 0, 1023, 0, 100);
  level = constrain(level, 0, 100);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("WATER LEVEL");

  display.setTextSize(2);
  display.setCursor(35, 22);
  display.print(level);
  display.println("%");

  display.setTextSize(1);
  display.setCursor(35, 48);

  if (level < 25)
    display.println("LOW");
  else if (level < 50)
    display.println("MEDIUM");
  else if (level < 75)
    display.println("HIGH");
  else if (level < 90)
    display.println("VERY HIGH");
  else
    display.println("FULL");

  display.display();

  delay(500);
}
