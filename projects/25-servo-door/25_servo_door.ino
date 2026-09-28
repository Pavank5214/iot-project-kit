/*
  Project 25: Smart Servo Door (Servo Motor + Push Button + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  An automated door access system using a Micro Servo Motor (SG90) and a push button.
  When the push button is pressed (active-LOW via internal INPUT_PULLUP), the servo rotates
  to 90 degrees to unlock/open the door and the 0.96" SSD1306 OLED displays "OPEN".
  After an open dwell time of 3 seconds, the servo returns to 0 degrees to close the door
  and the display shows "CLOSED".

  Connections:
  - Push Button    -> Digital Pin 2 (Internal INPUT_PULLUP -> GND)
  - Servo Signal   -> Digital Pin 9 (PWM)
  - Servo Power    -> 5V
  - Servo Ground   -> GND
  - OLED VCC       -> 5V
  - OLED GND       -> GND
  - OLED SDA       -> Analog Pin A4
  - OLED SCL       -> Analog Pin A5

  Required Libraries:
  - Servo (built-in)
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_PIN 2
#define SERVO_PIN 9

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Servo doorServo;

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

void showMessage(const char* message) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(35, 5);
  display.println("SERVO DOOR");

  display.setTextSize(2);
  display.setCursor(15, 30);
  display.println(message);

  display.display();
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  doorServo.attach(SERVO_PIN);
  doorServo.write(0);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  showMessage("CLOSED");
}

void loop() {

  if (digitalRead(BUTTON_PIN) == LOW) {

    doorServo.write(90);
    showMessage("OPEN");

    delay(3000);

    doorServo.write(0);
    showMessage("CLOSED");

    delay(500);
  }
}
