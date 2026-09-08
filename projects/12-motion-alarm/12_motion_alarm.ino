/*
  Project 12: Motion Alarm (PIR Motion Sensor + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  Detects human or animal motion using a HC-SR501 PIR Motion Sensor.
  When motion is detected (`PIR_PIN == HIGH`), a warning alarm sounds via a
  Piezo Buzzer and "MOTION!" flashes on the 0.96" SSD1306 OLED display.

  Connections:
  - PIR Sensor OUT -> Digital Pin 2
  - PIR Sensor VCC -> 5V
  - PIR Sensor GND -> GND
  - Buzzer (+)    -> Digital Pin 8
  - Buzzer (-)    -> GND
  - OLED VCC      -> 5V
  - OLED GND      -> GND
  - OLED SDA      -> Analog Pin A4
  - OLED SCL      -> Analog Pin A5

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIR_PIN 2
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
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("MOTION ALARM");

  display.setTextSize(2);
  display.setCursor(30, 30);
  display.println("READY");

  display.display();
  delay(1500);
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("MOTION ALARM");

  display.setTextSize(2);

  if (motion == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);

    display.setCursor(20, 30);
    display.println("MOTION!");
  }
  else {
    digitalWrite(BUZZER_PIN, LOW);

    display.setCursor(10, 30);
    display.println("NO MOTION");
  }

  display.display();

  delay(100);
}
