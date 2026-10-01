/*
  Project 39: Wi-Fi Rain Monitor (ESP32 + Raindrop Sensor + OLED + WebServer)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An IoT-enabled weather station and precipitation monitoring system built with
  an ESP32 microcontroller, a raindrop sensor plate (YL-83) with an LM393
  comparator driver board, and a 0.96" SSD1306 I2C OLED display.

  The ESP32 reads analog voltage from the rain sensor using its 12-bit ADC (GPIO 34):
  - When dry, high electrical resistance produces an ADC reading near 4095 (3.3V).
  - When raindrops bridge the conductive nickel tracks on the rain plate, electrical
    conductivity increases and analog voltage drops towards ~1000.
  - The software inversely maps this reading to a 0 - 100% precipitation intensity:
    * < 20%: "DRY"
    * 20% - 59%: "LIGHT RAIN"
    * >= 60%: "HEAVY RAIN"
  - Real-time rainfall percentage and categorical status are displayed locally
    on the OLED screen.
  - The embedded HTTP web server on port 80 hosts a live dashboard that automatically
    refreshes every 2 seconds (<meta http-equiv='refresh' content='2'>) over local Wi-Fi.

  Connections:
  - Rain Sensor Plate  -> Comparator Board 2-pin probe header
  - Rain Sensor VCC    -> ESP32 3V3 / VIN (5V)
  - Rain Sensor GND    -> ESP32 GND
  - Rain Sensor AO     -> ESP32 GPIO 34 (ADC1_CH6 - Input Only)
  - OLED VDD / VCC     -> ESP32 VIN (5V) / 3V3
  - OLED GND           -> ESP32 GND
  - OLED SCK / SCL     -> ESP32 GPIO 22 (D22 - Hardware I2C SCL)
  - OLED SDA           -> ESP32 GPIO 21 (D21 - Hardware I2C SDA)

  Required Libraries:
  - WiFi (ESP32 core built-in)
  - WebServer (ESP32 core built-in)
  - Adafruit_GFX
  - Adafruit_SSD1306
  - Wire (built-in)
*/

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define RAIN_PIN 34

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

int rainLevel = 0;
String status = "DRY";

void readRain() {
  int value = analogRead(RAIN_PIN);

  // Typical sensor: lower ADC value = more water
  rainLevel = map(value, 4095, 1000, 0, 100);
  rainLevel = constrain(rainLevel, 0, 100);

  if (rainLevel < 20)
    status = "DRY";
  else if (rainLevel < 60)
    status = "LIGHT RAIN";
  else
    status = "HEAVY RAIN";
}

void updateDisplay() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(30, 2);
  display.println("RAIN MONITOR");

  display.setCursor(5, 20);
  display.print("Rain: ");
  display.print(rainLevel);
  display.println("%");

  display.setTextSize(1);
  display.setCursor(5, 40);
  display.print("Status:");

  display.setCursor(5, 52);
  display.println(status);

  display.display();
}

void handleRoot() {
  readRain();

  String html = "<!DOCTYPE html><html>";
  html += "<head><meta http-equiv='refresh' content='2'>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>IoT Rain Monitor</title></head>";
  html += "<body><h2>IoT Rain Monitor</h2>";

  html += "<p>Rain Level: <b>";
  html += String(rainLevel);
  html += "%</b></p>";

  html += "<p>Status: <b>";
  html += status;
  html += "</b></p>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

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
  readRain();
  updateDisplay();

  server.handleClient();

  delay(1000);
}
