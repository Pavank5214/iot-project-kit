/*
  Project 18: Soil Moisture Meter (Soil Moisture Sensor + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  Monitors soil volumetric water content using a resistive Soil Moisture Sensor.
  As soil dries, resistance increases (higher analog value). The Arduino maps
  the analog reading into a 0 - 100% moisture scale and categorizes the soil
  hydration level as "DRY", "MOIST", or "WET" on a 0.96" SSD1306 OLED screen.

  Connections:
  - Soil Sensor AO   -> Analog Pin A0
  - Soil Sensor VCC  -> 5V
  - Soil Sensor GND  -> GND
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

  // Most sensors: higher reading = drier soil
  int moisture = map(value, 1023, 0, 0, 100);
  moisture = constrain(moisture, 0, 100);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(28, 5);
  display.println("SOIL MOISTURE");

  display.setTextSize(2);
  display.setCursor(35, 22);
  display.print(moisture);
  display.println("%");

  display.setTextSize(1);
  display.setCursor(40, 48);

  if (moisture < 30)
    display.println("DRY");
  else if (moisture < 70)
    display.println("MOIST");
  else
    display.println("WET");

  display.display();

  delay(500);
}
