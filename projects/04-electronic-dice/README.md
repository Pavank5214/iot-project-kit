# Project 04 — Electronic Die with 7-Segment Display & Touch Sensor 🎲

[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen.svg)](#difficulty)
[![Board: Arduino Uno](https://img.shields.io/badge/Board-Arduino%20Uno-blue.svg)](#hardware-used)
[![Sensor: TTP223 Touch](https://img.shields.io/badge/Sensor-TTP223%20Touch-purple.svg)](#hardware-used)

## Overview

The **Electronic Die** simulates a 6-sided rolling die for tabletop games. Interfaced with a **TTP223 Capacitive Touch Sensor** and a **1-Digit 7-Segment LED Display**, touching the sensor triggers a fast "rolling" perimeter animation on the LED display, followed by displaying a random number between **1** and **6**.

This project introduces key embedded systems concepts:
* Controlling a 7-Segment LED Display (Common Anode logic)
* Interfacing digital touch sensors (TTP223)
* Creating custom display animations
* Generating pseudo-random numbers with `randomSeed(analogRead(A0))`

---

## Difficulty

**Easy** — Great beginner-to-intermediate project for understanding multiplexed segment mapping and sensor input.

---

## Hardware Required

| Component | Quantity | Notes |
| :--- | :---: | :--- |
| **Arduino Uno** | 1 | Microcontroller board |
| **1-Digit 7-Segment Display** | 1 | **Common Anode** type |
| **TTP223 Capacitive Touch Sensor** | 1 | Digital touch sensor module |
| **220Ω Resistor** | 1 | Current limiting resistor for Common Anode pin |
| **Breadboard** | 1 | Solderless breadboard |
| **Jumper Wires** | 10–12 | Male-to-Male wires |

---

## Circuit Connections

### 7-Segment Display (Common Anode)

```text
       ── a ──
      │       │
      f       b
      │       │
       ── g ──
      │       │
      e       c
      │       │
       ── d ──
```

| 7-Segment Display Pin | Arduino Uno Pin | Resistor Connection |
| :--- | :--- | :--- |
| **Segment a** | **Digital Pin 11** | Direct |
| **Segment b** | **Digital Pin 10** | Direct |
| **Segment c** | **Digital Pin 9** | Direct |
| **Segment d** | **Digital Pin 8** | Direct |
| **Segment e** | **Digital Pin 7** | Direct |
| **Segment f** | **Digital Pin 6** | Direct |
| **Segment g** | **Digital Pin 5** | Direct |
| **Common Anode (+)** | **5V** | via 220Ω Resistor |

### TTP223 Touch Sensor Module

| Touch Sensor Pin | Arduino Uno Pin | Description |
| :--- | :--- | :--- |
| **VCC** | **5V** | Power supply (+5V) |
| **GND** | **GND** | Ground |
| **OUT (SIG)** | **Digital Pin 3** | Touch signal input (`HIGH` when touched) |

---

## Circuit Diagram

### Wiring Diagram
![Electronic Dice Circuit Diagram](assets/dice.png)

### Schematic (ASCII)

```text
Arduino UNO

     D11 ───────> Segment a
     D10 ───────> Segment b
      D9 ───────> Segment c           ┌─────────┐
      D8 ───────> Segment d           │ 7-Seg   │
      D7 ───────> Segment e           │ Display │
      D6 ───────> Segment f           └────┬────┘
      D5 ───────> Segment g                │
      D3 <─────── Touch Sensor OUT         │ 220Ω
      5V ───────> Touch VCC & Resistor ────┘
     GND ───────> Touch GND
```

---

## Common Anode 7-Segment Truth Table

> [!NOTE]
> In a **Common Anode** 7-segment display, the common pin is tied to **+5V**. Therefore:
> * **`LOW`** turns an LED segment **ON** (current flows to pin).
> * **`HIGH`** turns an LED segment **OFF** (no potential difference).

| Digit | a | b | c | d | e | f | g |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| **1** | HIGH | **LOW** | **LOW** | HIGH | HIGH | HIGH | HIGH |
| **2** | **LOW** | **LOW** | HIGH | **LOW** | **LOW** | HIGH | **LOW** |
| **3** | **LOW** | **LOW** | **LOW** | **LOW** | HIGH | HIGH | **LOW** |
| **4** | HIGH | **LOW** | **LOW** | HIGH | HIGH | **LOW** | **LOW** |
| **5** | **LOW** | HIGH | **LOW** | **LOW** | HIGH | **LOW** | **LOW** |
| **6** | **LOW** | HIGH | **LOW** | **LOW** | **LOW** | **LOW** | **LOW** |

---

## Arduino Code

The source code for this project is available in [`04_electronic_dice.ino`](04_electronic_dice.ino).

```cpp
/*
 * Project 04: Electronic Die with 7-Segment Display & Touch Sensor
 * Board: Arduino Uno
 */

const int seg_a = 11;
const int seg_b = 10;
const int seg_c = 9;
const int seg_d = 8;
const int seg_e = 7;
const int seg_f = 6;
const int seg_g = 5;
const int sensor = 3;

int i = 0;

void setup() {
  pinMode(seg_a, OUTPUT); 
  pinMode(seg_b, OUTPUT);
  pinMode(seg_c, OUTPUT);
  pinMode(seg_d, OUTPUT);
  pinMode(seg_e, OUTPUT);
  pinMode(seg_f, OUTPUT);
  pinMode(seg_g, OUTPUT);
  pinMode(sensor, INPUT);

  while(digitalRead(sensor) == LOW){
    pattern(); // Display spinning pattern while waiting
  }
  
  randomSeed(analogRead(A0));
}

void loop() {
  if(digitalRead(sensor) == HIGH){
    i = random(1, 7); // Pick random number 1..6
    for(int pat = 0; pat <= 2; pat++){
      pattern(); // Play roll animation 3x
    }
    sevenSeg(); // Display final dice number
  }
}

void sevenSeg() {
  if (i == 1) {
    digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW);  digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, HIGH); digitalWrite(seg_e, HIGH); digitalWrite(seg_f, HIGH); digitalWrite(seg_g, HIGH);
  } else if (i == 2) {
    digitalWrite(seg_a, LOW);  digitalWrite(seg_b, LOW);  digitalWrite(seg_c, HIGH);
    digitalWrite(seg_d, LOW);  digitalWrite(seg_e, LOW);  digitalWrite(seg_f, HIGH); digitalWrite(seg_g, LOW);
  } else if (i == 3) {
    digitalWrite(seg_a, LOW);  digitalWrite(seg_b, LOW);  digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, LOW);  digitalWrite(seg_e, HIGH); digitalWrite(seg_f, HIGH); digitalWrite(seg_g, LOW);
  } else if (i == 4) {
    digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW);  digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, HIGH); digitalWrite(seg_e, HIGH); digitalWrite(seg_f, LOW);  digitalWrite(seg_g, LOW);
  } else if (i == 5) {
    digitalWrite(seg_a, LOW);  digitalWrite(seg_b, HIGH); digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, LOW);  digitalWrite(seg_e, HIGH); digitalWrite(seg_f, LOW);  digitalWrite(seg_g, LOW);
  } else if (i == 6) {
    digitalWrite(seg_a, LOW);  digitalWrite(seg_b, HIGH); digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, LOW);  digitalWrite(seg_e, LOW);  digitalWrite(seg_f, LOW);  digitalWrite(seg_g, LOW);
  }
}

void pattern() { // Outer segment chase animation (a -> b -> c -> d -> e -> f)
  digitalWrite(seg_a, LOW);  digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, HIGH); digitalWrite(seg_e, HIGH); digitalWrite(seg_f, HIGH); digitalWrite(seg_g, HIGH);
  delay(100);
  
  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, LOW);  digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, HIGH); digitalWrite(seg_e, HIGH); digitalWrite(seg_f, HIGH); digitalWrite(seg_g, HIGH);
  delay(100);

  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, LOW);
  digitalWrite(seg_d, HIGH); digitalWrite(seg_e, HIGH); digitalWrite(seg_f, HIGH); digitalWrite(seg_g, HIGH);
  delay(100);

  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, LOW);  digitalWrite(seg_e, HIGH); digitalWrite(seg_f, HIGH); digitalWrite(seg_g, HIGH);
  delay(100);

  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, HIGH); digitalWrite(seg_e, LOW);  digitalWrite(seg_f, HIGH); digitalWrite(seg_g, HIGH);
  delay(100);

  digitalWrite(seg_a, HIGH); digitalWrite(seg_b, HIGH); digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, HIGH); digitalWrite(seg_e, HIGH); digitalWrite(seg_f, LOW);  digitalWrite(seg_g, HIGH);
  delay(100);
}
```

---

## How It Works

1. **Idle Mode**: In `setup()`, while no touch is detected, the `pattern()` function loops continuously, causing an LED segment to chase around the outer border ($a \to b \to c \to d \to e \to f$).
2. **Touch Detection**: Touching the TTP223 module sets Pin 3 `HIGH`.
3. **Rolling Simulation**: The loop calls `pattern()` 3 times to simulate rolling dice.
4. **Random Result**: `random(1, 7)` picks a number from 1 to 6. `sevenSeg()` illuminates the corresponding segments.

---

## Experiments & Enhancements

* **Buzzer Sound Effects**: Add a piezo buzzer on Pin 12 to play a click sound during the rolling animation and a beep tone when the final number appears.
* **Double Die Mode**: Add a second 7-segment display or roll twice to generate numbers between 2 and 12.
