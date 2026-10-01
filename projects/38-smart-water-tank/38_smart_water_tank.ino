/*
  Project 38: Smart Water Tank (ESP32 + Ultrasonic Sensor + Relay + OLED)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An automated overhead water tank level controller and pump management system
  built with an ESP32 microcontroller, an HC-SR04 ultrasonic distance sensor,
  a 5V optocoupler-isolated relay module driving a water pump, and a 0.96"
  SSD1306 I2C OLED display.

  The HC-SR04 ultrasonic sensor is mounted at the top of the water tank facing downward:
  - It measures distance to the water surface using ultrasonic pulse echo timing.
  - Using the configurable tank depth parameter (default: 30 cm), it computes the
    real-time water level percentage: level = ((TANK_DEPTH - distance) / TANK_DEPTH) * 100.
  - Automatic Inflow Regulation:
    * When water level falls below 30%, the controller energizes the active-LOW relay
      on GPIO 26, turning ON the water pump to refill the tank.
    * When water level reaches 90% or higher, the relay de-energizes, turning OFF
      the pump to prevent tank overflow.
  - The OLED display renders live water percentage and pump status ("PUMP ON" / "PUMP OFF"),
    or "SENSOR ERR" if ultrasonic echo timeout occurs.

  Connections:
  - HC-SR04 VCC       -> ESP32 VIN (5V)
  - HC-SR04 GND       -> ESP32 GND
  - HC-SR04 Trig      -> ESP32 GPIO 5 (D5)
  - HC-SR04 Echo      -> ESP32 GPIO 18 (D18)
  - Relay Module VCC  -> ESP32 VIN (5V)
  - Relay Module GND  -> ESP32 GND
  - Relay Module IN/S -> ESP32 GPIO 26 (D26 - Active LOW)
  - Relay COM / NO    -> Connected in series with Water Pump & External Power Supply
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

#define TRIG_PIN 5
#define ECHO_PIN 18
#define RELAY_PIN 26

// Set this to your tank depth in cm
#define TANK_DEPTH 30

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

bool pumpOn = false;

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
    return -1;

  return duration * 0.0343 / 2.0;
}

void setPump(bool state) {
  pumpOn = state;

  // Most relay modules are active LOW
  digitalWrite(RELAY_PIN, pumpOn ? LOW : HIGH);
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  setPump(false);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {

  float distance = getDistance();

  if (distance > 0 && distance <= TANK_DEPTH) {

    int level = ((TANK_DEPTH - distance) / TANK_DEPTH) * 100;
    level = constrain(level, 0, 100);

    // Automatic pump control
    if (!pumpOn && level < 30) {
      setPump(true);
    }

    if (pumpOn && level >= 90) {
      setPump(false);
    }

    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(25, 5);
    display.println("SMART WATER TANK");

    display.setCursor(10, 20);
    display.print("Level: ");
    display.print(level);
    display.println("%");

    display.setTextSize(2);
    display.setCursor(25, 40);

    if (pumpOn)
      display.println("PUMP ON");
    else
      display.println("PUMP OFF");

  } else {

    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(25, 5);
    display.println("SMART WATER TANK");

    display.setTextSize(2);
    display.setCursor(20, 30);
    display.println("SENSOR ERR");
  }

  display.display();

  delay(1000);
}
