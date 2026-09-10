/*
  Project 17: Water Leakage Alarm (Water Leak Sensor + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An automated water leakage detection and safety alert system using a
  water droplet/leak sensor module. When water is detected across the sensor
  contacts, the module's digital output switches to LOW, activating the
  Piezo Buzzer alarm and alerting "WATER LEAK!" on the 0.96" SSD1306 OLED screen.
  When dry, the buzzer is silenced and the display shows "NO LEAK".

  Connections:
  - Water Leak Sensor DO -> Digital Pin 2
  - Water Leak Sensor VCC -> 5V
  - Water Leak Sensor GND -> GND
  - Buzzer (+)           -> Digital Pin 8
  - Buzzer (-)           -> GND
  - OLED VCC             -> 5V
  - OLED GND             -> GND
  - OLED SDA             -> Analog Pin A4
  - OLED SCL             -> Analog Pin A5

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SENSOR_PIN 2
#define BUZZER_PIN 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

void setup() {
  pinMode(SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int water = digitalRead(SENSOR_PIN);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("LEAK ALARM");

  display.setTextSize(2);

  // Most modules output LOW when water is detected
  if (water == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);

    display.setCursor(15, 28);
    display.println("WATER");
    display.setCursor(25, 48);
    display.println("LEAK!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);

    display.setCursor(25, 32);
    display.println("NO LEAK");
  }

  display.display();
  delay(200);
}
