# Project 12 — Motion Alarm (PIR Sensor + Buzzer + OLED) 🚨🏃

[![Difficulty: Easy](https://img.shields.io/badge/Difficulty-Easy-brightgreen.svg)](#difficulty)
[![Board: Arduino Uno](https://img.shields.io/badge/Board-Arduino%20Uno-blue.svg)](#hardware-used)
[![Sensor: PIR HC-SR501](https://img.shields.io/badge/Sensor-PIR%20HC--SR501-purple.svg)](#hardware-used)

## Overview

The **Motion Alarm** is an intrusion and security detector. Using a **PIR (Passive Infrared) Motion Sensor (HC-SR501)**, it detects infrared radiation emitted by moving warm bodies (humans/animals). When motion is detected, a **Piezo Buzzer** sounds an alarm and the OLED screen displays `"MOTION!"`.

This project introduces:
* Passive Infrared (PIR) sensing technology
* Intrusion detection security systems
* Digital state evaluation (`HIGH` vs `LOW`)

---

## Hardware Required

| Component | Quantity | Notes |
| :--- | :---: | :--- |
| **Arduino Uno** | 1 | Microcontroller board |
| **PIR Motion Sensor (HC-SR501)** | 1 | Passive Infrared sensor |
| **Piezo Buzzer** | 1 | Sound warning module (+ to D8, - to GND) |
| **0.96" I2C OLED Display** | 1 | 128x64 pixels (SSD1306 controller, address `0x3C`) |
| **Breadboard & Jumpers** | 1 | Solderless board & wires |

---

## Circuit Connections

| Component Pin | Arduino Pin | Description |
| :--- | :--- | :--- |
| **PIR Sensor OUT** | **Digital Pin 2** | Motion detection output (`HIGH` = Motion) |
| **PIR Sensor VCC** | **5V** | Sensor Power (+5V) |
| **PIR Sensor GND** | **GND** | Sensor Ground |
| **Buzzer (+)** | **Digital Pin 8** | Audio alarm pin |
| **Buzzer (−)** | **GND** | Ground |
| **OLED VCC** | **5V** | Display Power (+5V) |
| **OLED GND** | **GND** | Display Ground |
| **OLED SDA** | **Analog Pin A4** | I2C Data Line |
| **OLED SCL** | **Analog Pin A5** | I2C Clock Line |

---

## Circuit Diagram

### Schematic (ASCII)

```text
Arduino UNO

             ┌───────────────────────┐
      A5 ────┤ SCL                   │
      A4 ────┤ SDA   0.96" SSD1306   │
      5V ────┤ VCC   OLED Display    │
     GND ────┤ GND                   │
             └───────────────────────┘

      D2 ───────────[ PIR OUT ] (VCC -> 5V, GND -> GND)
      D8 ───────────[ Piezo Buzzer (+) ] ────> GND
```

> [!NOTE]
> *Circuit diagram image will be updated as soon as provided.*

---

## Arduino Code

Available in [`12_motion_alarm.ino`](12_motion_alarm.ino).

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define PIR_PIN 2
#define BUZZER_PIN 8

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);

  display.clearDisplay();
  display.setTextSize(1); display.setCursor(30, 5);  display.println("MOTION ALARM");
  display.setTextSize(2); display.setCursor(30, 30); display.println("READY");
  display.display();
  delay(1500);
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  display.clearDisplay();
  display.setTextSize(1); display.setCursor(30, 5); display.println("MOTION ALARM");
  display.setTextSize(2);

  if (motion == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    display.setCursor(20, 30); display.println("MOTION!");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    display.setCursor(10, 30); display.println("NO MOTION");
  }

  display.display();
  delay(100);
}
```
