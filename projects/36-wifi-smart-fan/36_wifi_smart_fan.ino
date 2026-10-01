/*
  Project 36: Wi-Fi Smart Fan (ESP32 + DHT11 + 5V Relay + OLED + WebServer)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An IoT-enabled automatic climate and temperature-regulated smart cooling fan
  built with an ESP32 microcontroller, a DHT11 temperature/humidity sensor,
  a 5V optocoupler-isolated relay module driving a 5V DC cooling fan, and a
  0.96" SSD1306 I2C OLED display.

  The ESP32 continuously samples ambient temperature from the DHT11 sensor (GPIO 4):
  - When the temperature reaches or exceeds 30.0 °C, the ESP32 energizes the active-LOW
    relay on GPIO 26, turning ON the cooling fan.
  - When temperature cools below 30.0 °C, the relay de-energizes, turning OFF the fan.
  - The 0.96" OLED screen displays live temperature in °C and fan operational status
    ("FAN: ON" / "FAN: OFF").
  - The onboard HTTP web server serves an auto-refreshing dashboard (every 2 seconds)
    over local 2.4 GHz Wi-Fi, allowing wireless monitoring from any web browser.

  Connections:
  - DHT11 Sensor VCC   -> ESP32 VIN (5V) / 3V3
  - DHT11 Sensor GND   -> ESP32 GND
  - DHT11 Sensor DAT   -> ESP32 GPIO 4 (D4)
  - Relay Module VCC   -> ESP32 VIN (5V)
  - Relay Module GND   -> ESP32 GND
  - Relay Module IN/S  -> ESP32 GPIO 26 (D26 - Active LOW)
  - Relay COM / NO     -> Connected in series with 5V DC Fan & External 5V Power Supply
  - OLED VDD / VCC     -> ESP32 VIN (5V) / 3V3
  - OLED GND           -> ESP32 GND
  - OLED SCK / SCL     -> ESP32 GPIO 22 (D22 - Hardware I2C SCL)
  - OLED SDA           -> ESP32 GPIO 21 (D21 - Hardware I2C SDA)

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
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DHT_PIN 4
#define DHT_TYPE DHT11
#define RELAY_PIN 26

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

DHT dht(DHT_PIN, DHT_TYPE);
WebServer server(80);

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

float temperature = 0;
bool fanOn = false;

void readTemperature() {
  float t = dht.readTemperature();

  if (!isnan(t)) {
    temperature = t;
  }
}

void setFan(bool state) {
  fanOn = state;

  // Most relay modules are active LOW
  digitalWrite(RELAY_PIN, fanOn ? LOW : HIGH);
}

void updateDisplay() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(35, 5);
  display.println("SMART FAN");

  display.setTextSize(2);
  display.setCursor(10, 25);
  display.print(temperature, 1);
  display.println(" C");

  display.setTextSize(1);
  display.setCursor(35, 50);

  if (fanOn)
    display.println("FAN: ON");
  else
    display.println("FAN: OFF");

  display.display();
}

void handleRoot() {
  readTemperature();

  String html = "<!DOCTYPE html><html>";
  html += "<head><meta http-equiv='refresh' content='2'>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>Smart Fan</title></head>";
  html += "<body><h2>Smart Fan</h2>";

  html += "<p>Temperature: <b>";
  html += String(temperature, 1);
  html += " C</b></p>";

  html += "<p>Fan: <b>";
  html += fanOn ? "ON" : "OFF";
  html += "</b></p>";

  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  setFan(false);

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
  readTemperature();

  // Automatic temperature control
  if (temperature >= 30.0) {
    setFan(true);
  } 
  else {
    setFan(false);
  }

  updateDisplay();

  server.handleClient();

  delay(2000);
}
