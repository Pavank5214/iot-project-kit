/*
  Project 08: Weather Monitor (DHT11 + OLED Display)
  IoT Project Kit - Arduino Uno

  Description:
  Reads ambient temperature (°C) and relative humidity (%) from a DHT11 sensor
  and renders the values continuously on a 0.96" SSD1306 OLED display.

  Connections:
  - DHT11 Data Pin -> Digital Pin 2
  - DHT11 VCC      -> 5V
  - DHT11 GND      -> GND
  - OLED VCC       -> 5V
  - OLED GND       -> GND
  - OLED SDA       -> Analog Pin A4
  - OLED SCL       -> Analog Pin A5

  Required Libraries:
  - DHT sensor library by Adafruit
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

#define DHT_PIN 2
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    while (true); // Stop if OLED initialization fails
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(25, 5);
  display.println("WEATHER MONITOR");

  display.setTextSize(2);
  display.setCursor(30, 25);
  display.println("READY");

  display.display();

  delay(1500);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Title
  display.setTextSize(1);
  display.setCursor(25, 0);
  display.println("WEATHER MONITOR");

  // Sensor error check
  if (isnan(temperature) || isnan(humidity)) {
    display.setTextSize(2);
    display.setCursor(10, 25);
    display.println("SENSOR");

    display.setCursor(10, 45);
    display.println("ERROR");
  } 
  else {
    // Temperature
    display.setTextSize(1);
    display.setCursor(5, 18);
    display.println("Temperature:");

    display.setTextSize(2);
    display.setCursor(15, 28);
    display.print(temperature, 1);
    display.print(" C");

    // Humidity
    display.setTextSize(1);
    display.setCursor(75, 18);
    display.println("Humidity:");

    display.setTextSize(2);
    display.setCursor(78, 28);
    display.print(humidity, 0);
    display.print("%");
  }

  display.display();

  delay(2000);
}
