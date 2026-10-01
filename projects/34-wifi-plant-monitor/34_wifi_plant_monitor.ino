/*
  Project 34: IoT Smart Plant Monitor (ESP32 + Soil Moisture + DHT11 + OLED)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An IoT-enabled smart agriculture and indoor plant health monitor built with an
  ESP32 microcontroller, a resistive soil moisture sensor probe, a DHT11 ambient
  temperature/humidity sensor, and a 0.96" SSD1306 I2C OLED display. The ESP32 measures
  soil volumetric water content using its 12-bit ADC (GPIO 34) and maps it to 0-100%,
  categorizing hydration into "DRY", "MOIST", or "WET". It also reads ambient temperature
  and relative humidity from the DHT11 (GPIO 4), displays all parameters locally on the
  OLED screen, and hosts an embedded HTTP web server on port 80 with an auto-refreshing
  (every 2 seconds) plant dashboard accessible from any browser on the local Wi-Fi.

  Connections:
  - Soil Sensor Probe   -> Comparator Board 2-pin probe header
  - Soil Sensor VCC     -> ESP32 VIN (5V)
  - Soil Sensor GND     -> ESP32 GND
  - Soil Sensor AO      -> ESP32 GPIO 34 (ADC1_CH6 - Input Only)
  - DHT11 Sensor VCC    -> ESP32 VIN (5V) / 3V3
  - DHT11 Sensor GND    -> ESP32 GND
  - DHT11 Sensor DAT    -> ESP32 GPIO 4 (D4)
  - OLED VDD / VCC      -> ESP32 VIN (5V) / 3V3
  - OLED GND            -> ESP32 GND
  - OLED SCK / SCL      -> ESP32 GPIO 22 (D22 - Hardware I2C SCL)
  - OLED SDA            -> ESP32 GPIO 21 (D21 - Hardware I2C SDA)

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

#define SOIL_PIN 34
#define DHT_PIN 4
#define DHT_TYPE DHT11

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

WebServer server(80);
DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

int moisture = 0;
float temperature = 0;
float humidity = 0;

void readSensors() {
  int soilValue = analogRead(SOIL_PIN);

  // Higher ADC reading usually means drier soil (12-bit ADC: 0 - 4095)
  moisture = map(soilValue, 4095, 0, 0, 100);
  moisture = constrain(moisture, 0, 100);

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (!isnan(t)) temperature = t;
  if (!isnan(h)) humidity = h;
}

String plantStatus() {
  if (moisture < 30)
    return "DRY";
  else if (moisture < 70)
    return "MOIST";
  else
    return "WET";
}

void updateDisplay() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(25, 0);
  display.println("PLANT MONITOR");

  display.setCursor(0, 16);
  display.print("Soil: ");
  display.print(moisture);
  display.print("% ");
  display.println(plantStatus());

  display.setCursor(0, 32);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 48);
  display.print("Hum:  ");
  display.print(humidity, 1);
  display.println("%");

  display.display();
}

void handleRoot() {
  readSensors();

  String html = "<!DOCTYPE html><html>";
  html += "<head><meta http-equiv='refresh' content='2'>";
  html += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  html += "<title>IoT Plant Monitor</title></head>";
  html += "<body><h2>IoT Plant Monitor</h2>";
  html += "<p>Soil Moisture: <b>" + String(moisture) + "%</b></p>";
  html += "<p>Status: <b>" + plantStatus() + "</b></p>";
  html += "<p>Temperature: <b>" + String(temperature, 1) + " C</b></p>";
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
  readSensors();
  updateDisplay();

  server.handleClient();

  delay(2000);
}
