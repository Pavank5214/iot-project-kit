/*
  Project 03: Rock Paper Scissors OLED Game
  IoT Project Kit - Arduino Uno

  Description:
  An interactive Rock-Paper-Scissors game using an I2C SSD1306 128x64 OLED Display
  and 3 push buttons. The user picks Rock, Paper, or Scissors, and the Arduino randomly
  selects a computer choice and determines the winner!

  Hardware Connections:
  - Left Button (Rock)    -> Digital Pin 2
  - Middle Button (Paper) -> Digital Pin 3
  - Right Button (Scissor)-> Digital Pin 4
  - OLED VDD              -> 5V
  - OLED GND              -> GND
  - OLED SCK / SCL        -> Analog Pin A5
  - OLED SDA              -> Analog Pin A4

  Required Libraries:
  - Adafruit_GFX
  - Adafruit_SSD1306
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin Definitions
const int LeftButtonPin = 2;   // Rock
const int MiddleButtonPin = 3; // Paper
const int RightButtonPin = 4;  // Scissor

int playerchoice, compchoice;

void setup() {
  pinMode(LeftButtonPin, INPUT);
  pinMode(MiddleButtonPin, INPUT);
  pinMode(RightButtonPin, INPUT);

  Serial.begin(115200);

  // Seed pseudo-random number generator using floating analog pin A0
  randomSeed(analogRead(0));

  // Initialize SSD1306 OLED display (I2C address 0x3C)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  delay(2000);
  display.clearDisplay();
}

void loop() {
  playerchoice = 0;
  compchoice = 0;

  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Prompt user screen
  display.setCursor(10, 0);
  display.println("Lets Play a Game!");
  display.setCursor(23, 15);
  display.println("(choose one)");
  display.setCursor(0, 30);
  display.println("ROCK PAPER or SCISSOR");
  display.setCursor(0, 45);
  display.println("LEFT MIDDLE or RIGHT");
  display.display();

  // Wait until player presses a button
  while (playerchoice == 0) { 
    if (digitalRead(LeftButtonPin) == HIGH) {
      playerchoice = 1; // Rock
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("You Chose");
      display.setCursor(5, 15);
      display.println("Rock");
      display.display();
    }
  
    if (digitalRead(MiddleButtonPin) == HIGH) {
      playerchoice = 2; // Paper
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("You Chose");
      display.setCursor(5, 15);
      display.println("Paper");
      display.display();
    }

    if (digitalRead(RightButtonPin) == HIGH) {
      playerchoice = 3; // Scissor
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("You Chose");
      display.setCursor(5, 15);
      display.println("Scissor");
      display.display();
    } 
  }

  // Draw UI split lines
  display.drawLine(60, 0, 60, 29, WHITE);
  display.drawLine(0, 29, 128, 29, WHITE);
  display.display();  

  delay(500);

  // Generate computer choice (1 = Rock, 2 = Paper, 3 = Scissor)
  compchoice = random(1, 4);

  if (compchoice == 1) {
    display.setCursor(68, 0);
    display.println("Comp Chose");
    display.setCursor(73, 15);
    display.println("Rock");
    display.display();
  } else if (compchoice == 2) {
    display.setCursor(68, 0);
    display.println("Comp Chose");
    display.setCursor(73, 15);
    display.println("Paper");
    display.display();
  } else if (compchoice == 3) {
    display.setCursor(68, 0);
    display.println("Comp Chose");
    display.setCursor(73, 15);
    display.println("Scissor");
    display.display();
  } 

  delay(1000);

  // Determine game outcome
  if (playerchoice == compchoice) {
    display.setCursor(32, 40);
    display.println("Its a Tie!");
    display.display(); 
  } else if ((playerchoice == 1 && compchoice == 3) ||
             (playerchoice == 2 && compchoice == 1) ||
             (playerchoice == 3 && compchoice == 2)) {
    display.setCursor(32, 40);
    display.println("You Won!");
    display.display(); 
  } else {
    display.setCursor(32, 40);
    display.println("Comp Won!");
    display.display(); 
  }

  delay(2000);  
  display.clearDisplay();
}
