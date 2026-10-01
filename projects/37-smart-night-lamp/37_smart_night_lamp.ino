/*
  Project 37: Smart Night Lamp (ESP32 + LDR Sensor + LED + OLED)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An automated ambient light sensing and night illumination system built with
  an ESP32 microcontroller, an LDR (Light Dependent Resistor) sensor module with
  an LM393 comparator, a 5mm LED with current-limiting resistor, and a 0.96"
  SSD1306 I2C OLED display.

  The ESP32 reads digital light status from GPIO 4 (D4):
  - In darkness / low ambient light, the LDR module's comparator switches LOW,
    turning ON the illumination LED on GPIO 2 (D2) and displaying "LIGHT ON".
  - In bright / daylight ambient conditions, the comparator switches HIGH,
    turning OFF the LED to conserve energy and displaying "DAYLIGHT".
  - The onboard potentiometer on the LDR module allows fine-tuning the exact
    ambient light threshold for triggering the night lamp.

  Connections:
  - LDR Module VCC    -> ESP32 VIN (5V)
  - LDR Module GND    -> ESP32 GND
  - LDR Module DO     -> ESP32 GPIO 4 (D4)
  - LED Anode (+)     -> ESP32 GPIO 2 (D2)
  - LED Cathode (-)   -> 220 Ohm Resistor -> ESP32 GND
  - OLED VDD / VCC    -> ESP32 VIN (5V) / 3V3
  - OLED GND          -> ESP32 GND
  - OLED SCK / SCL    -> ESP32 GPIO 22 (D22 - Hardware I2C SCL)
  - OLED SDA          -> ESP32 GPIO 21 (D21 - Hardware I2C SDA)

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
  - Wire (built-in)
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LDR_PIN 4
#define LED_PIN 2

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
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {

  int lightState = digitalRead(LDR_PIN);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("SMART NIGHT");

  display.setTextSize(2);

  // Most LDR modules: LOW = dark
  if (lightState == LOW) {
    digitalWrite(LED_PIN, HIGH);

    display.setCursor(5, 28);
    display.println("LIGHT ON");
  }
  else {
    digitalWrite(LED_PIN, LOW);

    display.setCursor(15, 28);
    display.println("DAYLIGHT");
  }

  display.display();

  delay(200);
}
