/*
  Project 32: Wi-Fi Motion Monitor (ESP32 + PIR Sensor + OLED)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An IoT-enabled wireless intrusion and motion surveillance station built with an
  ESP32 microcontroller, an HC-SR501 Passive Infrared (PIR) motion sensor, and a
  0.96" SSD1306 I2C OLED display. The ESP32 continuously scans the surrounding area
  for human or thermal motion, displays real-time status on the OLED screen ("MOTION
  DETECTED!" or "NO MOTION"), and hosts an embedded HTTP web server on port 80.
  Remote clients can navigate to the ESP32's IP address from any web browser to view
  a live, auto-refreshing (every 1 second) security status dashboard.

  Connections:
  - PIR Sensor VCC   -> ESP32 VIN (5V)
  - PIR Sensor GND   -> ESP32 GND
  - PIR Sensor OUT   -> ESP32 GPIO 4 (D4)
  - OLED VDD / VCC   -> ESP32 VIN (5V) / 3V3
  - OLED GND         -> ESP32 GND
  - OLED SCK / SCL   -> ESP32 GPIO 22 (D22 - Hardware I2C SCL)
  - OLED SDA         -> ESP32 GPIO 21 (D21 - Hardware I2C SDA)

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

#define PIR_PIN 4

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

WebServer server(80);

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

void updateDisplay(bool motion) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(25, 5);
  display.println("MOTION MONITOR");

  display.setTextSize(2);

  if (motion) {
    display.setCursor(5, 28);
    display.println("MOTION");
    display.setCursor(5, 48);
    display.println("DETECTED!");
  } else {
    display.setCursor(20, 35);
    display.println("NO MOTION");
  }

  display.display();
}

void handleRoot() {
  bool motion = digitalRead(PIR_PIN);

  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<meta http-equiv='refresh' content='1'>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>IoT Motion Monitor</title>";
  html += "</head><body>";
  html += "<h2>IoT Motion Monitor</h2>";

  if (motion == HIGH)
    html += "<h1>MOTION DETECTED</h1>";
  else
    html += "<h1>NO MOTION</h1>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

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
  bool motion = digitalRead(PIR_PIN);

  updateDisplay(motion);

  server.handleClient();

  delay(200);
}
