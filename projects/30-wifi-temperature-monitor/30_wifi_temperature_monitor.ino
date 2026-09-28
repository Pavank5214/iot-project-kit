/*
  Project 30: Wi-Fi Temperature & Humidity Monitor (ESP32 + DHT11 + OLED)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An IoT-enabled wireless environmental monitoring station built with an
  ESP32 microcontroller, a DHT11 temperature/humidity sensor, and a 0.96" SSD1306
  I2C OLED display. The ESP32 reads real-time ambient temperature and humidity,
  displays values locally on the OLED screen, connects to a local 2.4GHz Wi-Fi network,
  and hosts an embedded HTTP web server on port 80. Users can connect from any web
  browser (phone, tablet, PC) on the same Wi-Fi network to view live, auto-refreshing
  temperature and humidity data.

  Connections:
  - DHT11 Sensor VCC    -> ESP32 3V3
  - DHT11 Sensor GND    -> ESP32 GND
  - DHT11 Sensor DAT    -> ESP32 GPIO 4
  - OLED VDD/VCC        -> ESP32 3V3
  - OLED GND            -> ESP32 GND
  - OLED SCK/SCL        -> ESP32 GPIO 22 (Hardware I2C SCL)
  - OLED SDA            -> ESP32 GPIO 21 (Hardware I2C SDA)

  Required Libraries:
  - WiFi (ESP32 core built-in)
  - WebServer (ESP32 core built-in)
  - DHT sensor library by Adafruit
  - Adafruit_GFX
  - Adafruit_SSD1306
  - Wire (built-in)
*/

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT11

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

DHT dht(DHT_PIN, DHT_TYPE);
WebServer server(80);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

float temperature = 0;
float humidity = 0;

void updateSensor() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (!isnan(t) && !isnan(h)) {
    temperature = t;
    humidity = h;
  }
}

void handleRoot() {
  updateSensor();

  String html = "<!DOCTYPE html><html>";
  html += "<head><meta http-equiv='refresh' content='2'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Temperature Monitor</title></head>";
  html += "<body><h2>Wi-Fi Temperature Monitor</h2>";
  html += "<p>Temperature: <b>" + String(temperature, 1) + " °C</b></p>";
  html += "<p>Humidity: <b>" + String(humidity, 1) + " %</b></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20, 25);
  display.println("Connecting WiFi...");
  display.display();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  updateSensor();

  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(25, 2);
  display.println("TEMP MONITOR");

  display.setTextSize(2);
  display.setCursor(5, 20);
  display.print(temperature, 1);
  display.println(" C");

  display.setTextSize(1);
  display.setCursor(5, 47);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println("%");

  display.display();

  server.handleClient();

  delay(2000);
}
