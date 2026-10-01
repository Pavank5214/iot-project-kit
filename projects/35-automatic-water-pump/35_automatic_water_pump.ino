/*
  Project 35: Automatic Plant Watering System / Smart Water Pump
  IoT Project Kit - ESP32 Dev Module

  Description:
  An automated soil hydration and irrigation control system built with an ESP32
  microcontroller, a resistive soil moisture sensor probe, a 5V relay module driving
  a submersible DC mini water pump, and a 0.96" SSD1306 I2C OLED display.

  The ESP32 reads analog soil moisture from GPIO 34 (ADC1_CH6) and maps the 12-bit
  ADC reading to a calibrated moisture percentage (0 - 100%).
  - When moisture drops below 30%, the system triggers the active-LOW relay on GPIO 26,
    energizing the water pump to irrigate the plant.
  - Hysteresis is implemented: the pump continues running until moisture reaches 50%
    or above, preventing rapid oscillatory toggling.
  - Real-time soil moisture percentage and current pump operational status ("PUMP ON"
    or "PUMP OFF") are continuously rendered on the OLED display.

  Connections:
  - Soil Sensor Probe  -> Comparator Board 2-pin probe header
  - Soil Sensor VCC    -> ESP32 VIN (5V)
  - Soil Sensor GND    -> ESP32 GND
  - Soil Sensor AO     -> ESP32 GPIO 34 (ADC1_CH6 - Input Only)
  - Relay Module VCC   -> ESP32 VIN (5V)
  - Relay Module GND   -> ESP32 GND
  - Relay Module IN/S  -> ESP32 GPIO 26 (D26)
  - Relay COM / NO     -> Connected in series with DC Mini Water Pump & 5V Power Supply
  - OLED VDD / VCC     -> ESP32 VIN (5V) / 3V3
  - OLED GND           -> ESP32 GND
  - OLED SCK / SCL     -> ESP32 GPIO 22 (D22 - Hardware I2C SCL)
  - OLED SDA           -> ESP32 GPIO 21 (D21 - Hardware I2C SDA)

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
  - Wire (built-in)
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SOIL_PIN 34
#define RELAY_PIN 26

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

bool pumpOn = false;

void setup() {
  pinMode(RELAY_PIN, OUTPUT);

  // Most relay modules are active LOW
  digitalWrite(RELAY_PIN, HIGH);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int sensorValue = analogRead(SOIL_PIN);

  // Calibrate these values for your sensor
  int moisture = map(sensorValue, 4095, 1500, 0, 100);
  moisture = constrain(moisture, 0, 100);

  // Start watering when soil is dry
  if (!pumpOn && moisture < 30) {
    pumpOn = true;
  }

  // Stop watering when sufficiently moist
  if (pumpOn && moisture >= 50) {
    pumpOn = false;
  }

  // Active-LOW relay
  digitalWrite(RELAY_PIN, pumpOn ? LOW : HIGH);

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(22, 5);
  display.println("AUTO WATERING");

  display.setCursor(10, 22);
  display.print("Moisture: ");
  display.print(moisture);
  display.println("%");

  display.setTextSize(2);
  display.setCursor(25, 42);

  if (pumpOn)
    display.println("PUMP ON");
  else
    display.println("PUMP OFF");

  display.display();

  delay(1000);
}
