/*
  Project 22: Automatic Temperature-Controlled Fan (DHT11 + Fan/Relay + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  A temperature-triggered cooling and climate-control system using a DHT11 digital
  temperature and humidity sensor. Ambient temperature is continuously measured and
  displayed on the 0.96" SSD1306 OLED screen. When temperature exceeds 30.0°C (TEMP_LIMIT),
  the Arduino activates digital pin 8 to turn ON the cooling fan (or relay/motor).
  When the temperature cools down below the limit, the fan turns OFF.

  Connections:
  - DHT11 Data    -> Digital Pin 2
  - DHT11 VCC     -> 5V
  - DHT11 GND     -> GND
  - Fan / Relay IN-> Digital Pin 8
  - Fan VCC / GND -> External / 5V / GND
  - OLED VCC      -> 5V
  - OLED GND      -> GND
  - OLED SDA      -> Analog Pin A4
  - OLED SCL      -> Analog Pin A5

  Required Libraries:
  - DHT sensor library (Adafruit)
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11
#define FAN_PIN 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

#define TEMP_LIMIT 30.0

void setup() {
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);

  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {

  float temperature = dht.readTemperature();

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("AUTOMATIC FAN");

  if (isnan(temperature)) {

    digitalWrite(FAN_PIN, LOW);

    display.setTextSize(2);
    display.setCursor(20, 25);
    display.println("SENSOR");

    display.setCursor(30, 45);
    display.println("ERROR");

  } 
  else {

    display.setTextSize(1);
    display.setCursor(10, 20);
    display.print("Temperature: ");

    display.setTextSize(2);
    display.setCursor(30, 32);
    display.print(temperature, 1);
    display.print(" C");

    if (temperature >= TEMP_LIMIT) {
      digitalWrite(FAN_PIN, HIGH);

      display.setTextSize(1);
      display.setCursor(40, 52);
      display.println("FAN: ON");
    }
    else {
      digitalWrite(FAN_PIN, LOW);

      display.setTextSize(1);
      display.setCursor(40, 52);
      display.println("FAN: OFF");
    }
  }

  display.display();

  delay(2000);
}
