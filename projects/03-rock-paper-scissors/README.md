# Project 03 — Rock Paper Scissors OLED Game 🎮

[![Difficulty: Medium](https://img.shields.io/badge/Difficulty-Medium-yellow.svg)](#difficulty)
[![Board: Arduino Uno](https://img.shields.io/badge/Board-Arduino%20Uno-blue.svg)](#hardware-used)
[![Display: SSD1306 OLED](https://img.shields.io/badge/Display-0.96%22%20SSD1306%20OLED-orange.svg)](#hardware-used)

## Overview

The **Rock Paper Scissors OLED Game** is an interactive handheld game built with an Arduino Uno, a 0.96" I2C SSD1306 OLED display, and 3 tactile push buttons. Players choose their move (Rock, Paper, or Scissors) by pressing a button. The Arduino generates a random computer move, renders the graphics on the screen, and calculates the game result in real time.

This project introduces key embedded systems concepts:
* **I2C Protocol & Graphics Rendering** using the `Adafruit_SSD1306` library
* **Digital Inputs & Pulldown Resistors**
* **Pseudo-Random Number Generation** (`randomSeed()`)
* **Conditional Game Logic & UI State Management**

---

## Difficulty

**Medium** — Requires installing external Arduino libraries and wiring an I2C display alongside multiple digital inputs.

---

## Hardware Required

| Component | Quantity | Notes |
| :--- | :---: | :--- |
| **Arduino Uno** | 1 | Microcontroller board |
| **0.96" I2C OLED Display** | 1 | 128x64 pixels (SSD1306 controller, address `0x3C`) |
| **Push Buttons** | 3 | Tactile switches (Left = Rock, Middle = Paper, Right = Scissors) |
| **10kΩ Resistors** | 3 | Pull-down resistors for buttons |
| **Breadboard** | 1 | Solderless prototyping board |
| **Jumper Wires** | 10–12 | Male-to-Male wires |

---

## Circuit Connections

### OLED Display (I2C)

| OLED Pin | Arduino Uno Pin | Description |
| :--- | :--- | :--- |
| **VCC / VDD** | **5V** | Power supply (+5V) |
| **GND** | **GND** | Ground |
| **SCK / SCL** | **Analog Pin A5** | I2C Clock Line |
| **SDA** | **Analog Pin A4** | I2C Data Line |

### Push Buttons (Digital Inputs)

| Component | Arduino Pin | Resistor Connection | Function |
| :--- | :--- | :--- | :--- |
| **Left Button** | **Digital Pin 2** | 10kΩ to GND | Choose **Rock** |
| **Middle Button** | **Digital Pin 3** | 10kΩ to GND | Choose **Paper** |
| **Right Button** | **Digital Pin 4** | 10kΩ to GND | Choose **Scissors** |

---

## Circuit Diagram

### Wiring Diagram
![Rock Paper Scissors Circuit Diagram](assets/push-button-game.png)

### Schematic (ASCII)

```text
Arduino UNO

             ┌───────────────────────┐
      A5 ────┤ SCL                   │
      A4 ────┤ SDA   0.96" SSD1306   │
      5V ────┤ VCC   OLED Display    │
     GND ────┤ GND                   │
             └───────────────────────┘

      D2 ────[ Button 1 (Rock)     ]───> 10kΩ ──> GND
      D3 ────[ Button 2 (Paper)    ]───> 10kΩ ──> GND
      D4 ────[ Button 3 (Scissors) ]───> 10kΩ ──> GND
```

---

## Required Arduino Libraries

To compile and run this sketch, install the following libraries via the **Arduino IDE Library Manager** (`Ctrl + Shift + I`):

1. **Adafruit SSD1306** by Adafruit
2. **Adafruit GFX Library** by Adafruit

---

## Game Logic & Rules Matrix

| Player Choice | Computer Choice | Result |
| :---: | :---: | :---: |
| 🪨 **Rock** (1) | ✂️ **Scissors** (3) | **PLAYER WINS!** |
| 📄 **Paper** (2) | 🪨 **Rock** (1) | **PLAYER WINS!** |
| ✂️ **Scissors** (3) | 📄 **Paper** (2) | **PLAYER WINS!** |
| *Same Choice* | *Same Choice* | **TIE!** |
| *Otherwise* | — | **COMPUTER WINS!** |

---

## Arduino Code

The complete source code is available in [`03_rock_paper_scissors.ino`](03_rock_paper_scissors.ino).

```cpp
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int LeftButtonPin = 2;   // Rock
const int MiddleButtonPin = 3; // Paper
const int RightButtonPin = 4;  // Scissor

int playerchoice, compchoice;

void setup() {
  pinMode(LeftButtonPin, INPUT);
  pinMode(MiddleButtonPin, INPUT);
  pinMode(RightButtonPin, INPUT);

  Serial.begin(115200);
  randomSeed(analogRead(0));

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
}

void loop() {
  playerchoice = 0;
  compchoice = 0;

  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(10, 0);
  display.println("Lets Play a Game!");
  display.setCursor(23, 15);
  display.println("(choose one)");
  display.setCursor(0, 30);
  display.println("ROCK PAPER or SCISSOR");
  display.setCursor(0, 45);
  display.println("LEFT MIDDLE or RIGHT");
  display.display();

  while (playerchoice == 0) { 
    if (digitalRead(LeftButtonPin) == HIGH) {
      playerchoice = 1;
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("You Chose");
      display.setCursor(5, 15);
      display.println("Rock");
      display.display();
    }
  
    if (digitalRead(MiddleButtonPin) == HIGH) {
      playerchoice = 2;
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("You Chose");
      display.setCursor(5, 15);
      display.println("Paper");
      display.display();
    }

    if (digitalRead(RightButtonPin) == HIGH) {
      playerchoice = 3;
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println("You Chose");
      display.setCursor(5, 15);
      display.println("Scissor");
      display.display();
    } 
  }

  display.drawLine(60, 0, 60, 29, WHITE);
  display.drawLine(0, 29, 128, 29, WHITE);
  display.display();  

  delay(500);

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
```

---

## How It Works

1. **Display Initialization**: The OLED is configured using I2C address `0x3C`. If communication fails, the code halts execution.
2. **Random Seed Generation**: `randomSeed(analogRead(0))` reads static electrical noise from floating pin A0 to ensure unpredictable computer moves every match.
3. **Player Input Loop**: The `while (playerchoice == 0)` loop waits until one of the 3 push buttons sends a `HIGH` signal.
4. **Opponent AI Logic**: `random(1, 4)` picks a value between 1 and 3 representing the computer's choice.
5. **Score Evaluation & Screen Update**: The OLED displays the player's choice on the left, the computer's choice on the right, and the winner prompt across the bottom panel.

---

## Future Enhancements & Experiments

* **Bitmap Icons**: Replace text with custom 16x16 bitmap icons for Rock 🪨, Paper 📄, and Scissors ✂️ using `display.drawBitmap()`.
* **Score Tracker**: Keep track of Wins, Losses, and Ties across multiple rounds.
* **Piezo Buzzer**: Add sound effects for button clicks, victory tunes, and defeat tones.
