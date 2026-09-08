/*
  Project 09: Temperature Alarm (DHT11 + Buzzer + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  Monitors ambient temperature using a DHT11 sensor. If the temperature exceeds
  the threshold limit (30.0°C), a Piezo Buzzer sounds an alert tone and an
  "!! HIGH TEMP !!" alarm message flashes on the 0.96" SSD1306 OLED display.

  Connections:
  - DHT11 Data Pin -> Digital Pin 2
  - DHT11 VCC      -> 5V
  - DHT11 GND      -> GND
  - Buzzer (+)     -> Digital Pin 8
  - Buzzer (-)     -> GND
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
#define BUZZER_PIN 8

#define TEMP_LIMIT 30.0

DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    while (true); // Halt execution if OLED initialization fails
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(25, 5);
  display.println("TEMPERATURE");

  display.setCursor(35, 18);
  display.println("ALARM");

  display.setTextSize(2);
  display.setCursor(30, 35);
  display.println("READY");

  display.display();

  delay(1500);
}

void loop() {
  float temperature = dht.readTemperature();

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setTextSize(1);
  display.setCursor(32, 0);
  display.println("TEMP ALARM");

  if (isnan(temperature)) {
    digitalWrite(BUZZER_PIN, LOW);

    display.setTextSize(2);
    display.setCursor(10, 20);
    display.println("SENSOR");

    display.setCursor(25, 43);
    display.println("ERROR");
  }
  else {
    // Temperature readout
    display.setTextSize(1);
    display.setCursor(5, 16);
    display.print("Temperature: ");

    display.setTextSize(2);
    display.setCursor(25, 27);
    display.print(temperature, 1);
    display.print(" C");

    // Threshold check
    if (temperature >= TEMP_LIMIT) {
      digitalWrite(BUZZER_PIN, HIGH);

      display.setTextSize(1);
      display.setCursor(30, 50);
      display.println("!! HIGH TEMP !!");
    }
    else {
      digitalWrite(BUZZER_PIN, LOW);

      display.setTextSize(1);
      display.setCursor(45, 50);
      display.println("NORMAL");
    }
  }

  display.display();

  delay(2000);
}
