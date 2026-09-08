/*
  Project 10: Digital Distance Meter (HC-SR04 + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  Measures distance to target objects using an HC-SR04 Ultrasonic sensor
  and displays live readings in both centimeters (cm) and inches (inch) on a
  0.96" SSD1306 OLED display.

  Connections:
  - HC-SR04 TRIG -> Digital Pin 7
  - HC-SR04 ECHO -> Digital Pin 6
  - HC-SR04 VCC  -> 5V
  - HC-SR04 GND  -> GND
  - OLED VCC     -> 5V
  - OLED GND     -> GND
  - OLED SDA     -> Analog Pin A4
  - OLED SCL     -> Analog Pin A5

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

#define TRIG_PIN 7
#define ECHO_PIN 6

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    while (true); // Stop if OLED fails
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("DIGITAL");

  display.setCursor(25, 18);
  display.println("DISTANCE");

  display.setTextSize(2);
  display.setCursor(30, 38);
  display.println("METER");

  display.display();

  delay(1500);
}

void loop() {
  // Send 10-microsecond ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo pulse width (timeout 30ms)
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // Speed of sound = 0.0343 cm/µs; Distance = (duration * 0.0343) / 2
  float distanceCm = duration * 0.0343 / 2.0;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Title Header
  display.setTextSize(1);
  display.setCursor(25, 0);
  display.println("DIGITAL DISTANCE");

  // Out of range check (2cm to 400cm effective range)
  if (duration == 0 || distanceCm > 400 || distanceCm < 2) {
    display.setTextSize(2);
    display.setCursor(20, 25);
    display.println("OUT OF");

    display.setCursor(25, 45);
    display.println("RANGE");
  }
  else {
    float distanceInch = distanceCm / 2.54;

    display.setTextSize(1);
    display.setCursor(5, 18);
    display.println("Distance:");

    display.setTextSize(2);
    display.setCursor(15, 30);
    display.print(distanceCm, 1);
    display.print(" cm");

    display.setTextSize(1);
    display.setCursor(25, 52);
    display.print(distanceInch, 1);
    display.println(" inch");
  }

  display.display();

  delay(200);
}
