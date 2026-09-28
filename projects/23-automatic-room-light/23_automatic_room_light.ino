/*
  Project 23: Smart Automatic Room Light (PIR Motion + LDR Sensor + LED + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An intelligent energy-efficient room lighting controller combining motion detection
  and ambient light sensing. The light turns ON only when BOTH conditions are met:
  1) The room is dark (LDR reads LOW)
  2) A person / motion is detected (PIR reads HIGH)
  If the room is already bright or no movement is detected, the light stays OFF.
  The current light condition (DARK / BRIGHT) and room state are shown on the OLED.

  Connections:
  - PIR Sensor OUT -> Digital Pin 2
  - PIR Sensor VCC -> 5V
  - PIR Sensor GND -> GND
  - LDR Module DO  -> Digital Pin 3
  - LDR Module VCC -> 5V
  - LDR Module GND -> GND
  - LED Anode (+)  -> Digital Pin 8
  - LED Cathode (-)-> GND
  - OLED VCC       -> 5V
  - OLED GND       -> GND
  - OLED SDA       -> Analog Pin A4
  - OLED SCL       -> Analog Pin A5

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIR_PIN 2
#define LDR_PIN 3
#define LED_PIN 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {

  int motion = digitalRead(PIR_PIN);
  int light = digitalRead(LDR_PIN);

  // Most LDR modules: LOW = dark
  bool dark = (light == LOW);
  bool personDetected = (motion == HIGH);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(25, 5);
  display.println("ROOM LIGHT");

  display.setTextSize(2);

  if (dark && personDetected) {

    digitalWrite(LED_PIN, HIGH);

    display.setCursor(20, 25);
    display.println("LIGHT ON");

  } else {

    digitalWrite(LED_PIN, LOW);

    display.setCursor(15, 25);
    display.println("LIGHT OFF");
  }

  display.setTextSize(1);
  display.setCursor(25, 50);

  if (dark)
    display.println("DARK");
  else
    display.println("BRIGHT");

  display.display();

  delay(200);
}
