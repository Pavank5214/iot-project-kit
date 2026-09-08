/*
  Project 13: Door Alarm (Magnetic Reed Switch + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  Security door alarm system using a Magnetic Reed Switch Sensor.
  When the door is opened (magnet moves away from the sensor, digital pin reads HIGH),
  the piezo buzzer sounds an alert and the OLED display shows "DOOR OPEN".
  When the door is closed (magnet is close, digital pin reads LOW),
  the buzzer stays silent and the OLED display shows "DOOR CLOSED".

  Connections:
  - Reed Switch DO  -> Digital Pin 2
  - Reed Switch VCC -> 5V
  - Reed Switch GND -> GND
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

#define REED_PIN 2
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
  pinMode(REED_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {

  int reedState = digitalRead(REED_PIN);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("DOOR ALARM");

  display.setTextSize(2);

  if (reedState == HIGH) {
    // Door open
    digitalWrite(BUZZER_PIN, HIGH);

    display.setCursor(10, 28);
    display.println("DOOR OPEN");
  }
  else {
    // Door closed
    digitalWrite(BUZZER_PIN, LOW);

    display.setCursor(5, 28);
    display.println("DOOR CLOSED");
  }

  display.display();

  delay(100);
}
