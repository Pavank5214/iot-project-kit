/*
  Project 15: Rain Alarm (Raindrop Sensor + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An automated rain detection and alert system using a Raindrop Sensor Module.
  When rainwater bridges the conductive traces on the sensing plate, the comparator
  drives the digital output LOW. The Arduino detects this state, triggers the
  Piezo Buzzer alarm, and displays "RAIN DETECTED!" on the 0.96" SSD1306 OLED screen.
  When the sensor is dry, the buzzer remains off and the display shows "NO RAIN".

  Connections:
  - Rain Sensor DO  -> Digital Pin 2
  - Rain Sensor VCC -> 5V
  - Rain Sensor GND -> GND
  - Buzzer (+)      -> Digital Pin 8
  - Buzzer (-)      -> GND
  - OLED VCC        -> 5V
  - OLED GND        -> GND
  - OLED SDA        -> Analog Pin A4
  - OLED SCL        -> Analog Pin A5

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define RAIN_PIN 2
#define BUZZER_PIN 8

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
  pinMode(RAIN_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {

  int rainState = digitalRead(RAIN_PIN);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("RAIN ALARM");

  display.setTextSize(2);

  // Most rain sensor modules give LOW when rain is detected
  if (rainState == LOW) {

    digitalWrite(BUZZER_PIN, HIGH);

    display.setCursor(5, 25);
    display.println("RAIN");

    display.setCursor(5, 45);
    display.println("DETECTED!");

  } else {

    digitalWrite(BUZZER_PIN, LOW);

    display.setCursor(20, 30);
    display.println("NO RAIN");
  }

  display.display();

  delay(200);
}
