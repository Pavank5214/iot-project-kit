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
    └── 15-rain-alarm/                 # Project 15: Rain Alarm (Raindrop Sensor + Buzzer)
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

---

## 🛠️ Hardware Requirements

- **Microcontroller**: Arduino Uno R3 / Nano / ESP32
- **Displays**: 0.96" I2C OLED (SSD1306), 7-Segment LED Display (Common Cathode)
- **Sensors**: DHT11 Temp & Humidity, HC-SR04 Ultrasonic Distance, HC-SR501 PIR Motion, Magnetic Reed Switch Module, Raindrop Sensor Module
- **Actuators & Audio**: Piezo Buzzer, 4-Pin RGB LED (Common Cathode), LEDs (Red, Yellow, Green)
- **Inputs & Passive Components**: Push Buttons, Resistors (220Ω, 10kΩ), Breadboard, Jumper Wires
- **Software**: Arduino IDE / PlatformIO / Web Editor

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
