/*
  Project 24: Smart Street Light (LDR Sensor + LED + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An automated municipal street lighting system using a Light Dependent Resistor
  (LDR) sensor module. When ambient daylight fades into dusk/night, the comparator
  outputs LOW, prompting the Arduino to turn ON the street light LED on pin 8
  and display "LIGHT ON" & "NIGHT" on the 0.96" SSD1306 OLED screen. During daylight,
  the LED is switched OFF to save municipal energy and the display indicates "DAYLIGHT".

  Connections:
  - LDR Module DO  -> Digital Pin 2
  - LDR Module VCC -> 5V
  - LDR Module GND -> GND
  - Street Light LED (+) -> Digital Pin 8
  - Street Light LED (-) -> GND
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

#define LDR_PIN 2
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
  display.println("SMART STREET");

  display.setTextSize(2);

  // Most LDR modules: LOW = dark
  if (lightState == LOW) {

    digitalWrite(LED_PIN, HIGH);

    display.setCursor(5, 25);
    display.println("LIGHT ON");

    display.setTextSize(1);
    display.setCursor(30, 50);
    display.println("NIGHT");

  } else {

    digitalWrite(LED_PIN, LOW);

    display.setCursor(15, 25);
    display.println("DAYLIGHT");
  }

  display.display();

  delay(200);
}
