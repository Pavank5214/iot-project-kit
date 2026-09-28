/*
  Project 29: Tilt Alarm (Ball Tilt Sensor + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An anti-tamper and tilt detection security alarm using an SW-520D ball tilt
  switch sensor module, an active 5V piezo buzzer, and a 0.96" SSD1306 I2C OLED display.
  When the sensor module is tilted beyond its horizontal equilibrium point, the internal
  metal rolling ball breaks/makes contact, pulling the digital output LOW. The Arduino
  detects this change, triggers the buzzer alarm, and displays "TILT DETECTED!" on
  the OLED display. When returned to a level position, the buzzer silences and the
  screen displays "NORMAL".

  Connections:
  - Tilt Sensor Module VCC -> 5V
  - Tilt Sensor Module GND -> GND
  - Tilt Sensor Module DO  -> Digital Pin 2
  - Active Buzzer (+)      -> Digital Pin 8
  - Active Buzzer (-)      -> GND
  - OLED VCC               -> 5V
  - OLED GND               -> GND
  - OLED SDA               -> Analog Pin A4
  - OLED SCL               -> Analog Pin A5

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
  - Wire (built-in)
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TILT_PIN 2
#define BUZZER_PIN 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

void setup() {
  pinMode(TILT_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {

  int tilt = digitalRead(TILT_PIN);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(35, 5);
  display.println("TILT ALARM");

  display.setTextSize(2);

  // Most tilt modules output LOW when tilted
  if (tilt == LOW) {

    digitalWrite(BUZZER_PIN, HIGH);

    display.setCursor(5, 28);
    display.println("TILT");
    display.setCursor(5, 48);
    display.println("DETECTED!");

  } else {

    digitalWrite(BUZZER_PIN, LOW);

    display.setCursor(30, 32);
    display.println("NORMAL");
  }

  display.display();

  delay(200);
}
