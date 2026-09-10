# IoT Project Kit 🧰⚡

Welcome to the **IoT Project Kit** repository! This collection contains step-by-step projects, circuit schematics, source code, and documentation designed for learning Internet of Things (IoT) and embedded systems hardware using **Arduino Uno**, sensors, and actuators.

---

## 📁 Repository Structure

```text
iot-project-kit/
│
├── README.md                          # Main repository overview & index
└── projects/                          # Individual IoT project guides
    ├── 01-led-blinking/               # Project 01: LED Blinking
    ├── 02-traffic-light/              # Project 02: Traffic Light Controller
    ├── 03-rock-paper-scissors/        # Project 03: Rock Paper Scissors OLED Game
    ├── 04-electronic-dice/            # Project 04: Electronic Die with Touch/Button
    ├── 05-rgb-mood-lamp/              # Project 05: RGB Mood Lamp / Smooth Color Fader
    ├── 06-digital-stopwatch/          # Project 06: Digital Stopwatch with OLED Display
    ├── 07-buzzer-reaction-game/       # Project 07: Buzzer Reaction Game
    ├── 08-weather-monitor/            # Project 08: Weather Monitor (DHT11 + OLED)
    ├── 09-temperature-alarm/          # Project 09: Temperature Alarm (DHT11 + Buzzer)
    ├── 10-distance-meter/             # Project 10: Digital Distance Meter (HC-SR04)
    ├── 11-parking-indicator/          # Project 11: Smart Parking Indicator (HC-SR04 + LEDs)
    ├── 12-motion-alarm/               # Project 12: Motion Alarm (PIR Sensor + Buzzer)
    ├── 13-door-alarm/                 # Project 13: Door Alarm (Reed Switch + Buzzer)
    ├── 14-touchless-doorbell/         # Project 14: Touchless Doorbell (Ultrasonic + Buzzer)
    ├── 15-rain-alarm/                 # Project 15: Rain Alarm (Raindrop Sensor + Buzzer)
    ├── 16-water-level/                # Project 16: Water Level Indicator (Sensor + OLED)
    ├── 17-water-leakage-alarm/        # Project 17: Water Leakage Alarm (Sensor + Buzzer + OLED)
    ├── 18-soil-moisture/              # Project 18: Soil Moisture Meter (Sensor + OLED)
    ├── 19-flame-alarm/                # Project 19: Flame Alarm (IR Flame Sensor + Buzzer + OLED)
    └── 20-gas-smoke-alarm/            # Project 20: Gas & Smoke Alarm (MQ-2 Sensor + Buzzer + OLED)
```

---

## 🚀 Projects Index

| # | Project Name | Hardware Used | Difficulty | Status | Documentation |
| :-: | :--- | :--- | :-: | :-: | :-: |
| **01** | **LED Blinking** | Arduino Uno, LED, 220Ω Resistor | `Easy` | ✅ Completed | [View Guide 📖](projects/01-led-blinking/) |
| **02** | **Traffic Light Controller** | Arduino Uno, 3-LED Traffic Light Module | `Easy` | ✅ Completed | [View Guide 📖](projects/02-traffic-light/) |
| **03** | **Rock Paper Scissors Game** | Arduino Uno, SSD1306 OLED, 3x Buttons | `Medium` | ✅ Completed | [View Guide 📖](projects/03-rock-paper-scissors/) |
| **04** | **Electronic Die** | Arduino Uno, 7-Seg Display, Push Button | `Easy` | ✅ Completed | [View Guide 📖](projects/04-electronic-dice/) |
| **05** | **RGB Mood Lamp** | Arduino Uno, 4-Pin RGB LED, Resistors | `Easy` | ✅ Completed | [View Guide 📖](projects/05-rgb-mood-lamp/) |
| **06** | **Digital Stopwatch** | Arduino Uno, SSD1306 OLED, 3x Buttons | `Medium` | ✅ Completed | [View Guide 📖](projects/06-digital-stopwatch/) |
| **07** | **Buzzer Reaction Game** | Arduino Uno, SSD1306 OLED, Button, Buzzer | `Easy` | ✅ Completed | [View Guide 📖](projects/07-buzzer-reaction-game/) |
| **08** | **Weather Monitor** | Arduino Uno, DHT11 Sensor, SSD1306 OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/08-weather-monitor/) |
| **09** | **Temperature Alarm** | Arduino Uno, DHT11 Sensor, Buzzer, OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/09-temperature-alarm/) |
| **10** | **Digital Distance Meter** | Arduino Uno, HC-SR04 Sensor, SSD1306 OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/10-distance-meter/) |
| **11** | **Smart Parking Indicator** | Arduino Uno, HC-SR04 Sensor, 3x LEDs, Buzzer, OLED | `Medium` | ✅ Completed | [View Guide 📖](projects/11-parking-indicator/) |
| **12** | **Motion Alarm** | Arduino Uno, PIR Sensor, Buzzer, SSD1306 OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/12-motion-alarm/) |
| **13** | **Door Alarm** | Arduino Uno, Reed Switch Module, Buzzer, OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/13-door-alarm/) |
| **14** | **Touchless Doorbell** | Arduino Uno, HC-SR04 Sensor, Buzzer, OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/14-touchless-doorbell/) |
| **15** | **Rain Alarm** | Arduino Uno, Raindrop Sensor Module, Buzzer, OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/15-rain-alarm/) |
| **16** | **Water Level Indicator** | Arduino Uno, Water Level Sensor, SSD1306 OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/16-water-level/) |
| **17** | **Water Leakage Alarm** | Arduino Uno, Water Leak Module, Buzzer, OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/17-water-leakage-alarm/) |
| **18** | **Soil Moisture Meter** | Arduino Uno, Soil Moisture Sensor, SSD1306 OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/18-soil-moisture/) |
| **19** | **Flame Alarm** | Arduino Uno, IR Flame Sensor, Buzzer, OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/19-flame-alarm/) |
| **20** | **Gas & Smoke Alarm** | Arduino Uno, MQ-2 Gas Sensor, Buzzer, OLED | `Easy` | ✅ Completed | [View Guide 📖](projects/20-gas-smoke-alarm/) |

---

## 🛠️ Hardware Kit / Shopping List (Bill of Materials)

To build all 20 projects in this repository, here is the complete checklist of items needed for purchase or to bundle as a comprehensive IoT kit:

### 1. Core Microcontroller & Prototyping
| Item | Qty | Specifications / Notes | Used in Projects |
| :--- | :---: | :--- | :--- |
| **Arduino Uno R3** | 1 | Microcontroller board with USB-A to Type-B cable | All Projects (01–20) |
| **Solderless Breadboard** | 1 | Standard 830 tie-points (or 400 tie-points) | All Projects (01–20) |
| **Jumper Wires (M-to-M)** | ~30–40 | Male-to-Male prototyping wires | Projects 01–20 |
| **Jumper Wires (M-to-F)** | ~15–20 | Male-to-Female wires (for module header pins) | Projects 08–20 |
| **Jumper Wires (F-to-F)** | ~5–10 | Female-to-Female wires (for direct module connects) | Optional / Convenient |

### 2. Displays
| Item | Qty | Specifications / Notes | Used in Projects |
| :--- | :---: | :--- | :--- |
| **0.96" I2C OLED Display** | 1 | 128x64 resolution, SSD1306 driver, 4-pin (VCC, GND, SCL, SDA, `0x3C`) | Projects 03, 06, 07, 08, 09, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 |
| **1-Digit 7-Segment Display** | 1 | **Common Cathode (CC)**, 10-pin through-hole display | Project 04 |

### 3. Sensor Modules (10 Sensors)
| Sensor Module | Qty | Specifications / Interface | Used in Projects |
| :--- | :---: | :--- | :--- |
| **DHT11 Sensor** | 1 | Temperature & Relative Humidity digital sensor module (3-pin) | Projects 08, 09 |
| **HC-SR04 Ultrasonic Sensor** | 1 | Ultrasonic distance sensor (4-pin: VCC, Trig, Echo, GND) | Projects 10, 11, 14 |
| **HC-SR501 PIR Motion Sensor** | 1 | Passive Infrared motion detection module (3-pin: VCC, OUT, GND) | Project 12 |
| **Magnetic Reed Switch Module** | 1 | Door magnetic contact switch module + companion bar magnet | Project 13 |
| **Raindrop Sensor Module** | 1 | Rain sensing plate + LM393 comparator driver board (`DO`) | Project 15 |
| **Submersible Water Level Sensor** | 1 | Analog resistive water depth sensor board (3-pin: `S`, `+`, `-`) | Project 16 |
| **Water Leakage Sensor Module** | 1 | Droplet detection probe board + LM393 comparator (`DO`) | Project 17 |
| **Soil Moisture Sensor Module** | 1 | 2-prong soil probe fork + LM393 comparator board (`AO`) | Project 18 |
| **IR Flame Sensor Module** | 1 | 760nm–1100nm infrared receiver phototransistor + LM393 (`DO`) | Project 19 |
| **MQ-2 Gas & Smoke Sensor** | 1 | Combustible gas (LPG, methane, smoke) sensor module (`DO`) | Project 20 |

### 4. Actuators, Audio & Indicators
| Item | Qty | Specifications / Notes | Used in Projects |
| :--- | :---: | :--- | :--- |
| **Active 5V Piezo Buzzer** | 1 | 5V continuous audio buzzer (+ and - pins) | Projects 07, 09, 11, 12, 13, 14, 15, 17, 19, 20 |
| **Traffic Light Module (3-in-1)** | 1 | Integrated Red/Yellow/Green LED module *(or discrete LEDs)* | Project 02 |
| **5mm LEDs (Assorted)** | 5–10 | At least 2x Red, 2x Yellow, 2x Green standard LEDs | Projects 01, 02, 11 |
| **4-Pin RGB LED** | 1 | **Common Cathode** 5mm RGB LED | Project 05 |

### 5. Inputs & Passive Components
| Item | Qty | Specifications / Notes | Used in Projects |
| :--- | :---: | :--- | :--- |
| **Tactile Push Buttons** | 3–4 | 6x6mm mini tactile momentary switches | Projects 03, 04, 06, 07 |
| **220Ω Resistors** | 10 | 1/4W through-hole (current limiting for LEDs and 7-segment) | Projects 01, 02, 04, 05, 11 |
| **10kΩ Resistors** | 5 | 1/4W through-hole (general pull-up / pull-down) | General prototyping |
| **9V Battery Clip with DC Jack** | 1 | *(Optional)* For powering Arduino without a PC connection | Standalone demos |

---

## 💻 Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/Pavank5214/iot-project-kit.git
   ```
2. Navigate to any project folder under `projects/` (e.g., `projects/07-buzzer-reaction-game/`).
3. Open the `.ino` file in **Arduino IDE**.
4. Wire your circuit according to the provided `README.md` diagram.
5. Select your board (`Tools -> Board -> Arduino Uno`) and COM port, then click **Upload**.

---

## 📜 License

This repository is open-source and available under the [MIT License](LICENSE).
