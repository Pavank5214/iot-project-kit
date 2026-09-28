/*
  Project 28: Smart Touchless Dustbin (Ultrasonic Sensor + SG90 Servo + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An automated, contactless waste bin system that opens its lid automatically
  when a hand or object approaches within 15 cm. Using an HC-SR04 ultrasonic
  sensor, the system calculates proximity in real-time. When an object is detected
  within range, an SG90 micro servo rotates 90 degrees to lift the lid, and the
  0.96" SSD1306 OLED screen updates to display "OPEN". After holding the lid open
  for 3 seconds, the servo returns to 0 degrees to close the lid, and the display
  resets to "CLOSED".

  Connections:
  - HC-SR04 VCC       -> 5V
  - HC-SR04 GND       -> GND
  - HC-SR04 TRIG      -> Digital Pin 7
  - HC-SR04 ECHO      -> Digital Pin 6
  - SG90 Servo Signal -> Digital Pin 9 (PWM)
  - SG90 Servo Power  -> 5V
  - SG90 Servo Ground -> GND
  - OLED VCC          -> 5V
  - OLED GND          -> GND
  - OLED SDA          -> Analog Pin A4
  - OLED SCL          -> Analog Pin A5

  Required Libraries:
  - Servo (built-in)
  - Adafruit_GFX
  - Adafruit_SSD1306
  - Wire (built-in)
*/

#include <Wire.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN 7
#define ECHO_PIN 6
#define SERVO_PIN 9

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Servo lidServo;

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

void showMessage(const char* message) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(35, 5);
  display.println("DUSTBIN");

  display.setTextSize(2);
  display.setCursor(30, 30);
  display.println(message);

  display.display();
}

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  return duration * 0.0343 / 2;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  lidServo.attach(SERVO_PIN);
  lidServo.write(0);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  showMessage("CLOSED");
}

void loop() {

  long distance = getDistance();

  if (distance > 0 && distance <= 15) {

    lidServo.write(90);
    showMessage("OPEN");

    delay(3000);

    lidServo.write(0);
    showMessage("CLOSED");

    delay(500);

  } else {

    lidServo.write(0);
    showMessage("CLOSED");
  }

  delay(100);
}
