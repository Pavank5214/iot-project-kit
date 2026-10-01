/*
  Project 40: Wi-Fi Air Quality Monitor (ESP32 + MQ-135 + OLED + WebServer)
  IoT Project Kit - ESP32 Dev Module

  Description:
  An IoT-enabled indoor air quality telemetry station built with an ESP32
  microcontroller, an MQ-135 hazardous gas and air quality sensor module,
  and a 0.96" SSD1306 I2C OLED display.

  The MQ-135 sensor is sensitive to ammonia (NH3), nitrogen oxides (NOx), alcohol,
  benzene, smoke, and CO2:
  - The ESP32 samples the analog output (AO) on GPIO 34 (ADC1_CH6) using a 12-sample
    averaging routine to filter out ADC noise.
  - The raw 12-bit ADC value (0 - 4095) is mapped to a relative 0 - 100% pollution index:
    * ADC <= 1100: "GOOD"
    * 1101 - 2300: "MODERATE"
    * > 2300: "POOR"
  - The 0.96" SSD1306 OLED screen displays the header line, relative air quality %,
    categorical air status in large font, and the local Wi-Fi IP address.
  - The embedded HTTP web server on port 80 serves a styled HTML5 dashboard card
    with auto-refresh every 2 seconds (<meta http-equiv='refresh' content='2'>)
    allowing remote monitoring from any web browser on the local network.

  Connections:
  - MQ-135 Sensor VCC  -> ESP32 VIN (5V)
  - MQ-135 Sensor GND  -> ESP32 GND
  - MQ-135 Sensor AO   -> ESP32 GPIO 34 (ADC1_CH6 - Input Only)
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

// Wi-Fi network credentials (replace with your local network credentials)
const char* WIFI_SSID = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

constexpr uint8_t MQ135_AO_PIN = 34; // Analog output
constexpr uint8_t OLED_SDA = 21;
constexpr uint8_t OLED_SCL = 22;
constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr uint8_t OLED_ADDRESS = 0x3C;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WebServer server(80);

// Tune these ADC thresholds for your module.
// They indicate relative sensor response—not calibrated ppm or regulatory AQI.
constexpr int ADC_GOOD_MAX = 1100;
constexpr int ADC_MODERATE_MAX = 2300;

int rawReading = 0;
int airQualityPercent = 0; // Relative 0–100% sensor reading
String airStatus = "WARMING UP";
bool displayReady = false;
bool serverStarted = false;
unsigned long lastSampleMs = 0;
unsigned long lastWiFiAttemptMs = 0;

void sampleAir() {
  // Average samples to reduce ADC noise.
  uint32_t sum = 0;
  for (int i = 0; i < 12; ++i) {
    sum += analogRead(MQ135_AO_PIN);
    delay(3);
  }

  rawReading = sum / 12;
  airQualityPercent =
      constrain((int)((long)rawReading * 100L / 4095L), 0, 100);

  if (rawReading <= ADC_GOOD_MAX) {
    airStatus = "GOOD";
  } else if (rawReading <= ADC_MODERATE_MAX) {
    airStatus = "MODERATE";
  } else {
    airStatus = "POOR";
  }
}

String htmlPage() {
  String page = F(
      "<!doctype html><html><head>"
      "<meta name='viewport' content='width=device-width,initial-scale=1'>"
      "<meta http-equiv='refresh' content='2'>"
      "<title>ESP32 Air Quality Monitor</title>"
      "<style>body{font:20px Arial;text-align:center;"
      "background:#eef7ff;color:#123;padding:2em}"
      ".card{display:inline-block;background:white;padding:2em;"
      "border-radius:16px;box-shadow:0 2px 12px #abc}"
      ".level{font-size:3em;color:#1677c8}</style>"
      "</head><body><div class='card'>"
      "<h1>Air Quality Monitor</h1><div class='level'>");

  page += String(airQualityPercent);
  page += F("%</div><h2>");
  page += airStatus;
  page += F("</h2><p>MQ-135 ADC: ");
  page += String(rawReading);
  page += F(
      " / 4095</p>"
      "<small>Relative indication only; refreshes every 2 seconds</small>"
      "</div></body></html>");

  return page;
}

void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

void updateDisplay() {
  if (!displayReady) return;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("AIR QUALITY MONITOR"));
  display.drawLine(0, 11, 127, 11, SSD1306_WHITE);

  display.setCursor(0, 18);
  display.print(F("Relative level: "));
  display.print(airQualityPercent);
  display.println(F("%"));

  display.setTextSize(2);
  display.setCursor(0, 32);
  display.println(airStatus);

  display.setTextSize(1);
  display.setCursor(0, 55);
  if (WiFi.status() == WL_CONNECTED) {
    display.print(WiFi.localIP());
  } else {
    display.print(F("WiFi connecting..."));
  }

  display.display();
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  pinMode(MQ135_AO_PIN, INPUT);

  Wire.begin(OLED_SDA, OLED_SCL);
  displayReady = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  lastWiFiAttemptMs = millis();

  // The MQ-135 heater needs warm-up; treat readings as relative.
  sampleAir();
  updateDisplay();
}

void loop() {
  const unsigned long now = millis();

  if (WiFi.status() == WL_CONNECTED) {
    if (!serverStarted) {
      server.on("/", handleRoot);
      server.begin();
      serverStarted = true;
      updateDisplay();

      Serial.print(F("Air monitor page: http://"));
      Serial.println(WiFi.localIP());
    }

    server.handleClient();
  } else {
    serverStarted = false;

    if (now - lastWiFiAttemptMs >= 10000UL) {
      WiFi.disconnect();
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      lastWiFiAttemptMs = now;
    }
  }

  if (now - lastSampleMs >= 1000UL) {
    sampleAir();
    updateDisplay();
    lastSampleMs = now;
  }

  delay(2);
}
