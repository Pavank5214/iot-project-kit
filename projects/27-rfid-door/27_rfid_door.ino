/*
  Project 27: Smart RFID Door (RC522 RFID Reader + SG90 Servo + OLED)
  IoT Project Kit - Arduino Uno

  Description:
  A contactless RFID-based electronic access control system using the RC522
  RFID module, an SG90 micro servo motor, and a 0.96" SSD1306 I2C OLED display.
  When an RFID card or key fob is tapped against the reader, its 4-byte unique
  identifier (UID) is read via SPI and compared to an authorized UID key.
  If the card is authorized, the OLED displays "GRANTED" and the servo motor rotates
  90 degrees to unlock/open the door for 3 seconds before automatically returning
  to 0 degrees ("SCAN CARD"). If unauthorized, the OLED displays "DENIED" and access
  is rejected. All scanned UIDs are logged to the Serial Monitor at 9600 baud.

  Connections:
  RC522 RFID Reader (SPI):
  - 3.3V (VCC)    -> Arduino 3.3V (DO NOT connect to 5V!)
  - RST           -> Digital Pin 9
  - GND           -> GND
  - IRQ           -> Not Connected (Unused)
  - MISO          -> Digital Pin 12 (SPI MISO)
  - MOSI          -> Digital Pin 11 (SPI MOSI)
  - SCK           -> Digital Pin 13 (SPI SCK)
  - SDA (SS)      -> Digital Pin 10 (SPI SS)

  SG90 Micro Servo:
  - Signal (PWM)  -> Digital Pin 6
  - Power (Red)   -> 5V
  - Ground (Brown)-> GND

  0.96" OLED Display (I2C):
  - VCC           -> 5V
  - GND           -> GND
  - SDA           -> Analog Pin A4
  - SCL           -> Analog Pin A5

  Required Libraries:
  - MFRC522 by GithubCommunity
  - Servo (built-in)
  - Adafruit_GFX
  - Adafruit_SSD1306
  - SPI (built-in)
  - Wire (built-in)
*/

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 6

MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorServo;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT,
  &Wire, OLED_RESET
);

// Replace this with your card's UID
byte authorizedUID[] = {0xDE, 0xAD, 0xBE, 0xEF};

void showMessage(const char* message) {
  display.clearDisplay();

  display.setTextSize(1);
  display.setCursor(35, 5);
  display.println("RFID DOOR");

  display.setTextSize(2);
  display.setCursor(10, 30);
  display.println(message);

  display.display();
}

bool checkCard() {
  if (rfid.uid.size != 4)
    return false;

  for (byte i = 0; i < 4; i++) {
    if (rfid.uid.uidByte[i] != authorizedUID[i])
      return false;
  }

  return true;
}

void setup() {
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  doorServo.attach(SERVO_PIN);
  doorServo.write(0);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  showMessage("SCAN CARD");
}

void loop() {

  if (!rfid.PICC_IsNewCardPresent())
    return;

  if (!rfid.PICC_ReadCardSerial())
    return;

  // Print UID to Serial Monitor
  Serial.print("UID: ");

  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }

  Serial.println();

  if (checkCard()) {

    showMessage("GRANTED");

    doorServo.write(90);
    delay(3000);

    doorServo.write(0);
    showMessage("SCAN CARD");

  } else {

    showMessage("DENIED");
    delay(1500);
    showMessage("SCAN CARD");
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
