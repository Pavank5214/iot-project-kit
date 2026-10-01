/*
  Project 31: Wi-Fi LED Controller (ESP32 + WebServer + OLED)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An IoT-enabled wireless smart home actuator controller built with an ESP32,
  a 5mm indicator LED (with a 220Ω current-limiting resistor), and a 0.96" SSD1306
  I2C OLED display. The ESP32 connects to a local 2.4GHz Wi-Fi network and runs an
  embedded HTTP web server on port 80. Users can navigate to the ESP32's IP address
  from any smartphone, tablet, or PC browser to toggle the LED remotely via interactive
  web buttons ("/on" and "/off"). The OLED display provides real-time local feedback,
  showing Wi-Fi connection progress, IP address, and current LED status ("LED ON" / "LED OFF").

  Connections:
  - LED Anode (Long Leg) -> 220Ω Resistor -> ESP32 GPIO 2 (D2)
  - LED Cathode (Short)  -> ESP32 GND
  - OLED VDD / VCC       -> ESP32 VIN / 5V (or 3V3)
  - OLED GND             -> ESP32 GND
  - OLED SCK / SCL       -> ESP32 GPIO 22 (D22 - Hardware I2C SCL)
  - OLED SDA             -> ESP32 GPIO 21 (D21 - Hardware I2C SDA)

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

#define LED_PIN 2

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

void showStatus(bool state) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(35, 5);
  display.println("WI-FI LED");

  display.setTextSize(2);
  display.setCursor(25, 30);

  if (state) {
    display.println("LED ON");
  } else {
    display.println("LED OFF");
  }

  display.display();
}

void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>Wi-Fi LED</title>";
  html += "</head><body>";
  html += "<h2>Wi-Fi LED Controller</h2>";
  html += "<p><a href='/on'><button>ON</button></a></p>";
  html += "<p><a href='/off'><button>OFF</button></a></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void turnOn() {
  digitalWrite(LED_PIN, HIGH);
  showStatus(true);
  server.send(200, "text/html",
              "<h2>LED ON</h2><a href='/'>Back</a>");
}

void turnOff() {
  digitalWrite(LED_PIN, LOW);
  showStatus(false);
  server.send(200, "text/html",
              "<h2>LED OFF</h2><a href='/'>Back</a>");
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

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

  showStatus(false);

  server.on("/", handleRoot);
  server.on("/on", turnOn);
  server.on("/off", turnOff);

  server.begin();
}

void loop() {
  server.handleClient();
}
