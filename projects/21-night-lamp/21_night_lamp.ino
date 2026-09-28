/*
  Project 21: Automatic Night Lamp (LDR Sensor + LED + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An automated light control and smart street light system using a Light Dependent
  Resistor (LDR) sensor module. When ambient light drops below the configured threshold
  (night / darkness), the module's digital output switches to LOW. The Arduino detects
  this, turns ON the LED, and displays "NIGHT" & "LIGHT ON" on the 0.96" SSD1306 OLED screen.
  During daylight, the LED turns OFF and the screen displays "DAYLIGHT".

  Connections:
  - LDR Module DO  -> Digital Pin 2
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
  display.setCursor(25, 5);
  display.println("AUTOMATIC LIGHT");

  display.setTextSize(2);

  // Most LDR modules give LOW in darkness
  if (lightState == LOW) {

    digitalWrite(LED_PIN, HIGH);

    display.setCursor(5, 28);
    display.println("NIGHT");

    display.setCursor(5, 48);
    display.println("LIGHT ON");

  } else {

    digitalWrite(LED_PIN, LOW);

    display.setCursor(15, 35);
    display.println("DAYLIGHT");
  }

  display.display();

  delay(200);
}
