/*
  Project 26: Keypad Door Lock (4x4 Matrix Keypad + SG90 Servo + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  A secure electronic door lock system using a 4x4 matrix membrane keypad,
  an SG90 micro servo motor, and a 0.96" SSD1306 I2C OLED display. Users enter
  a 4-digit numeric PIN (default "1234"). Each entered digit is masked as '*'
  on the screen. Pressing '#' verifies the passcode: if correct, the display shows
  "GRANTED" and the servo rotates 90 degrees to unlock the door for 3 seconds before
  relocking (0 degrees, "LOCKED"). If incorrect, "DENIED" is displayed. Pressing '*'
  clears the entered PIN at any time.

  Connections:
  - 4x4 Keypad Row Pins (R1-R4)   -> Digital Pins 2, 3, 4, 5
  - 4x4 Keypad Col Pins (C1-C4)   -> Digital Pins 6, 7, 8, 9
  - SG90 Servo Signal             -> Digital Pin 10 (PWM)
  - SG90 Servo Power (Red)        -> 5V
  - SG90 Servo Ground (Brown/Blk) -> GND
  - OLED VCC                      -> 5V
  - OLED GND                      -> GND
  - OLED SDA                      -> Analog Pin A4
  - OLED SCL                      -> Analog Pin A5

  Required Libraries:
  - Keypad by Mark Stanley, Alexander Brevig
  - Servo (built-in)
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <Wire.h>
#include <Keypad.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SERVO_PIN 10

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

Servo doorServo;

// 4x4 keypad
char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[4] = {2, 3, 4, 5};
byte colPins[4] = {6, 7, 8, 9};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  4,
  4
);

String password = "1234";
String input = "";

void showMessage(const char* message) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(35, 5);
  display.println("DOOR LOCK");

  display.setTextSize(2);
  display.setCursor(10, 30);
  display.println(message);

  display.display();
}

void setup() {
  doorServo.attach(SERVO_PIN);
  doorServo.write(0);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  showMessage("ENTER PIN");
}

void loop() {

  char key = keypad.getKey();

  if (key) {

    if (key == '#') {

      if (input == password) {

        showMessage("GRANTED");

        doorServo.write(90);
        delay(3000);

        doorServo.write(0);
        showMessage("LOCKED");

      } else {

        showMessage("DENIED");
        delay(1500);
        showMessage("ENTER PIN");
      }

      input = "";
    }

    else if (key == '*') {
      input = "";
      showMessage("ENTER PIN");
    }

    else if (input.length() < 4) {
      input += key;

      display.clearDisplay();

      display.setTextSize(1);
      display.setCursor(35, 5);
      display.println("ENTER PIN");

      display.setTextSize(2);
      display.setCursor(40, 30);

      for (int i = 0; i < input.length(); i++) {
        display.print("*");
      }

      display.display();
    }
  }
}
