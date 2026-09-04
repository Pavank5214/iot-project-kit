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
    │   ├── README.md                  # Project documentation & schematic
    │   ├── 01_led_blinking.ino        # Arduino source code sketch
    │   └── assets/
    │       └── led-blinking.png       # Circuit diagram
    │
    ├── 02-traffic-light/              # Project 02: Traffic Light Controller
    │   ├── README.md                  # Project documentation & schematic
    │   ├── 02_traffic_light.ino        # Arduino source code sketch
    │   └── assets/
    │       └── traffic-light.png      # Circuit diagram
    │
    ├── 03-rock-paper-scissors/        # Project 03: Rock Paper Scissors OLED Game
    │   ├── README.md                  # Project documentation & schematic
    │   ├── 03_rock_paper_scissors.ino # Arduino source code sketch
    │   └── assets/
    │       └── push-button-game.png   # Circuit diagram
    │
    └── 04-electronic-dice/            # Project 04: Electronic Die with Touch Sensor
        ├── README.md                  # Project documentation & schematic
        ├── 04_electronic_dice.ino      # Arduino source code sketch
        └── assets/
            └── dice.png               # Circuit diagram
```

---

## 🚀 Projects Index

| # | Project Name | Hardware Used | Difficulty | Status | Documentation |
| :-: | :--- | :--- | :-: | :-: | :-: |
| **01** | **LED Blinking** | Arduino Uno, LED, 220Ω Resistor | `Easy` | ✅ Completed | [View Guide 📖](projects/01-led-blinking/) |
| **02** | **Traffic Light Controller** | Arduino Uno, 3-LED Traffic Light Module | `Easy` | ✅ Completed | [View Guide 📖](projects/02-traffic-light/) |
| **03** | **Rock Paper Scissors Game** | Arduino Uno, SSD1306 OLED, 3x Buttons | `Medium` | ✅ Completed | [View Guide 📖](projects/03-rock-paper-scissors/) |
| **04** | **Electronic Die** | Arduino Uno, 7-Seg Display, Touch Sensor | `Easy` | ✅ Completed | [View Guide 📖](projects/04-electronic-dice/) |

---

## 🛠️ Hardware Requirements

- **Microcontroller**: Arduino Uno R3 / Nano / ESP32
- **Displays**: 0.96" I2C OLED (SSD1306), 7-Segment LED Display (Common Anode)
- **Sensors**: TTP223 Capacitive Touch Sensor
- **Basic Components**: Breadboard, Push Buttons, LEDs, Resistors (220Ω, 10kΩ), Jumper Wires
- **Software**: Arduino IDE / PlatformIO / Web Editor

---

## 💻 Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/Pavank5214/iot-project-kit.git
   ```
2. Navigate to any project folder under `projects/` (e.g., `projects/04-electronic-dice/`).
3. Open the `.ino` file in **Arduino IDE**.
4. Wire your circuit according to the provided `README.md` diagram.
5. Select your board (`Tools -> Board -> Arduino Uno`) and COM port, then click **Upload**.

---

## 📜 License

This repository is open-source and available under the [MIT License](LICENSE).
