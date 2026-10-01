/*
  Project 33: Wi-Fi Door Monitor (ESP32 + Reed Switch + OLED)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An IoT-enabled wireless smart door and window contact monitor built with an
  ESP32 microcontroller, a magnetic reed switch sensor module (with companion magnet),
  and a 0.96" SSD1306 I2C OLED display. When the door is opened (magnet separated from
  the reed switch), the module's digital output goes HIGH; when closed (magnet adjacent),
  the output is LOW. The ESP32 updates its local OLED display in real-time ("DOOR OPEN" /
  "DOOR CLOSED") and hosts an embedded HTTP web server on port 80. Remote users can
  open the ESP32's IP address in any web browser to view a live, auto-refreshing (every
  1 second) security status portal.

  Connections:
  - Reed Switch Module VCC -> ESP32 3V3
  - Reed Switch Module GND -> ESP32 GND
  - Reed Switch Module DO  -> ESP32 GPIO 4 (D4)
  - OLED VDD / VCC         -> ESP32 VIN (5V) / 3V3
  - OLED GND               -> ESP32 GND
  - OLED SCK / SCL         -> ESP32 GPIO 22 (D22 - Hardware I2C SCL)
  - OLED SDA               -> ESP32 GPIO 21 (D21 - Hardware I2C SDA)

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

#define DOOR_PIN 4

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

void updateDisplay(bool open) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(30, 5);
  display.println("DOOR MONITOR");

  display.setTextSize(2);

  if (open) {
    display.setCursor(5, 30);
    display.println("DOOR OPEN");
  } else {
    display.setCursor(5, 30);
    display.println("DOOR CLOSED");
  }

  display.display();
}

void handleRoot() {
  bool open = digitalRead(DOOR_PIN) == HIGH;

  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<meta http-equiv='refresh' content='1'>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>IoT Door Monitor</title>";
  html += "</head><body>";
  html += "<h2>IoT Door Monitor</h2>";

  if (open)
    html += "<h1>DOOR OPEN</h1>";
  else
    html += "<h1>DOOR CLOSED</h1>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  pinMode(DOOR_PIN, INPUT);

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
  bool open = digitalRead(DOOR_PIN) == HIGH;

  updateDisplay(open);
  server.handleClient();

  delay(200);
}
