/*
  Project 14: Touchless Doorbell (Ultrasonic Sensor + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  A hygienic touchless doorbell system using an HC-SR04 Ultrasonic Sensor.
  When a visitor places their hand within 10 cm of the sensor, a pleasant
  doorbell tone (1500 Hz chime) plays through the Piezo Buzzer and "DING! DOORBELL"
  is displayed on the 0.96" SSD1306 OLED screen. When idle, the display shows "READY".

  Connections:
  - HC-SR04 Trig  -> Digital Pin 7
  - HC-SR04 Echo  -> Digital Pin 6
  - HC-SR04 VCC   -> 5V
  - HC-SR04 GND   -> GND
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

#define TRIG_PIN 7
#define ECHO_PIN 6
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
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  float distance = duration * 0.0343 / 2;

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("TOUCHLESS");

  display.setTextSize(2);

  if (distance > 0 && distance <= 10) {

    tone(BUZZER_PIN, 1500, 500);

    display.setCursor(20, 25);
    display.println("DING!");

    display.setCursor(15, 48);
    display.setTextSize(1);
    display.println("DOORBELL");

    delay(1000);

  } else {

    noTone(BUZZER_PIN);

    display.setCursor(30, 28);
    display.println("READY");
  }

  display.display();

  delay(100);
}
