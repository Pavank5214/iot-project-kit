/*
  Project 11: Smart Parking Indicator (HC-SR04 + LEDs + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  Simulates a smart automotive reverse parking assistance system:
  - Distance > 50 cm: SAFE (Green LED ON, No Beep)
  - 20 cm <= Distance <= 50 cm: CAUTION (Yellow LED ON, Slow Beep every 1s)
  - Distance < 20 cm: STOP! (Red LED ON, Rapid Beep every 250ms)

  Connections:
  - HC-SR04 TRIG -> Digital Pin 7
  - HC-SR04 ECHO -> Digital Pin 6
  - Green LED     -> Digital Pin 3
  - Yellow LED    -> Digital Pin 4
  - Red LED       -> Digital Pin 5
  - Piezo Buzzer  -> Digital Pin 8
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

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TRIG 7
#define ECHO 6

#define GREEN 3
#define YELLOW 4
#define RED 5
#define BUZZER 8

unsigned long lastBeep = 0;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // Send 10µs pulse
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH, 30000);
  float distance = duration * 0.0343 / 2.0;

  // Turn off all status LEDs
  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(25, 0);
  display.println("PARKING INDICATOR");

  display.setTextSize(2);
  display.setCursor(15, 20);

  // Range Evaluation & Parking Zone Logic
  if (duration == 0 || distance > 400) {
    display.println("NO OBJECT");
    digitalWrite(GREEN, HIGH);
    noTone(BUZZER);
  } 
  else if (distance > 50) {
    digitalWrite(GREEN, HIGH);
    display.println("SAFE");
    noTone(BUZZER);
  } 
  else if (distance >= 20) {
    digitalWrite(YELLOW, HIGH);
    display.println("CAUTION");

    // Slow beep (1000ms interval)
    if (millis() - lastBeep >= 1000) {
      tone(BUZZER, 1000, 150);
      lastBeep = millis();
    }
  } 
  else {
    digitalWrite(RED, HIGH);
    display.println("STOP!");

    // Fast beep (250ms interval)
    if (millis() - lastBeep >= 250) {
      tone(BUZZER, 1500, 100);
      lastBeep = millis();
    }
  }

  display.setTextSize(1);
  display.setCursor(35, 48);

  if (duration != 0 && distance <= 400) {
    display.print(distance, 1);
    display.println(" cm");
  }

  display.display();

  delay(50);
}
