import os
from PIL import Image, ImageDraw, ImageFont

os.makedirs('assets', exist_ok=True)

def get_font(name, size, bold=False):
    win_fonts = r'C:\Windows\Fonts'
    font_file = 'segoeuib.ttf' if bold else 'segoeui.ttf'
    if name == 'mono':
        font_file = 'consolab.ttf' if bold else 'consola.ttf'
    full_path = os.path.join(win_fonts, font_file)
    try:
        return ImageFont.truetype(full_path, size)
    except:
        return ImageFont.load_default()

def draw_wrapped_text(draw, text, x, y, max_chars, font, fill, line_spacing=26, max_lines=4):
    words = text.split()
    lines = []
    cur_line = []
    for w in words:
        cur_line.append(w)
        if len(' '.join(cur_line)) > max_chars:
            lines.append(' '.join(cur_line[:-1]))
            cur_line = [w]
    if cur_line:
        lines.append(' '.join(cur_line))
    for li, line_text in enumerate(lines[:max_lines]):
        draw.text((x, y + li * line_spacing), line_text, fill=fill, font=font)
    return y + min(len(lines), max_lines) * line_spacing

def generate_learning_poster():
    W, H = 2400, 3600
    img = Image.new('RGB', (W, H), '#080d1a')
    draw = ImageDraw.Draw(img)

    # Accent top gradient line
    for i in range(16):
        c = '#38bdf8' if i < 6 else ('#10b981' if i < 11 else '#818cf8')
        draw.line([(0, i), (W, i)], fill=c)

    # Subtle tech background grid
    for x in range(0, W, 80):
        draw.line([(x, 16), (x, H)], fill='#0b1324', width=1)
    for y in range(16, H, 80):
        draw.line([(0, y), (W, y)], fill='#0b1324', width=1)

    # Top Tag
    f_badge = get_font('sans', 24, bold=True)
    draw.rounded_rectangle([W//2 - 320, 50, W//2 + 320, 100], radius=12, fill='#111c33', outline='#38bdf8', width=2)
    draw.text((W//2, 75), 'EMBEDDED HARDWARE & IoT ENGINEERING PRIMER', fill='#38bdf8', anchor='mm', font=f_badge)

    # Main Poster Titles
    f_h1 = get_font('sans', 78, bold=True)
    f_sub = get_font('sans', 30, bold=False)
    f_tag = get_font('sans', 24, bold=False)

    draw.text((W//2, 160), 'IoT ARCHITECTURE & EMBEDDED SYSTEMS', fill='#ffffff', anchor='mm', font=f_h1)
    draw.text((W//2, 230), 'The Complete Guide to Sensing, Computing, Hardware Protocols & Physical Actuation', fill='#94a3b8', anchor='mm', font=f_sub)
    draw.text((W//2, 275), 'A Technical Visual Reference for Engineers, Makers, and Robotics Students', fill='#38bdf8', anchor='mm', font=f_tag)

    pad = 80

    # =========================================================================
    # SECTION 1: THE 4-LAYER IoT ARCHITECTURE (y: 330 - 640)
    # =========================================================================
    draw.text((pad, 330), '01 | THE 4 CORE LAYERS OF AN IoT SYSTEM', fill='#f8fafc', font=get_font('sans', 32, bold=True))
    draw.line([(pad, 375), (W - pad, 375)], fill='#1e293b', width=2)

    layers = [
        ('1. PERCEPTION / SENSING',
         'Transducers convert physical phenomena into electrical signals. Analog sensors yield continuous voltage (0–3.3V/5V); digital sensors output binary pulses or structured serial data frames.',
         '#38bdf8'),
        ('2. EDGE PROCESSING',
         'Onboard microcontrollers sample signals, apply multi-sample noise averaging, execute control loops, process logic conditions, and format packets at the physical device edge.',
         '#34d399'),
        ('3. CONNECTIVITY & BUSES',
         'Local buses (I2C, SPI, UART) interconnect local sensors and displays. RF stacks (2.4GHz Wi-Fi, Bluetooth LE) stream telemetry to dashboards, local web servers, and cloud endpoints.',
         '#a855f7'),
        ('4. ACTUATION & ACTION',
         'Translates computational decisions into physical real-world outcomes using relays (power switching), servos (angular position), buzzers (acoustic alarms), and OLED dashboards.',
         '#fbbf24')
    ]

    card_w = (W - 2*pad - 3*30) // 4
    for i, (title, desc, accent) in enumerate(layers):
        cx = pad + i * (card_w + 30)
        cy = 395
        ch = 220
        draw.rounded_rectangle([cx, cy, cx + card_w, cy + ch], radius=16, fill='#0f172a', outline='#1e293b', width=2)
        draw.rounded_rectangle([cx, cy, cx + card_w, cy + 8], radius=4, fill=accent)

        draw.text((cx + 20, cy + 28), title, fill=accent, font=get_font('sans', 21, bold=True))
        draw_wrapped_text(draw, desc, cx + 20, cy + 68, 36, get_font('sans', 17, bold=False), '#cbd5e1', line_spacing=24, max_lines=5)

    # =========================================================================
    # SECTION 2: MICROCONTROLLER COMPARISON (y: 660 - 1180)
    # =========================================================================
    draw.text((pad, 660), '02 | CORE MICROCONTROLLER COMPARISON: ARDUINO UNO vs ESP32', fill='#f8fafc', font=get_font('sans', 32, bold=True))
    draw.line([(pad, 705), (W - pad, 705)], fill='#1e293b', width=2)

    mcu_w = (W - 2*pad - 40) // 2

    # Arduino Card
    ax = pad
    ay = 725
    ah = 440
    draw.rounded_rectangle([ax, ay, ax + mcu_w, ay + ah], radius=18, fill='#0f172a', outline='#1e293b', width=2)
    draw.rounded_rectangle([ax, ay, ax + mcu_w, ay + 60], radius=18, fill='#1e293b')
    draw.line([(ax, ay + 60), (ax + mcu_w, ay + 60)], fill='#00979d', width=3)
    draw.text((ax + 24, ay + 16), 'ARDUINO UNO R3 — THE 5V CLASSIC CONTROLLER', fill='#38bdf8', font=get_font('sans', 24, bold=True))

    uno_specs = [
        ('Architecture', '8-bit AVR Microchip ATmega328P @ 16 MHz Clock Speed'),
        ('Operating Voltage', '5V CMOS Logic — Extremely robust & noise-tolerant'),
        ('Memory Capacity', '32 KB Flash ROM, 2 KB SRAM, 1 KB EEPROM'),
        ('Analog-to-Digital', '10-bit ADC (1024 discrete steps, 4.88 mV per LSB step)'),
        ('I/O Breakdown', '14 Digital I/O (6 PWM channels: 3, 5, 6, 9, 10, 11), 6 Analog Inputs (A0–A5)'),
        ('Current Capacity', 'Up to 20 mA per I/O pin (safe limit), 500 mA total board draw'),
        ('Primary Application', 'Deterministic real-time control, basic sensor arrays, and beginner robotics')
    ]

    for li, (label, val) in enumerate(uno_specs):
        row_y = ay + 80 + li * 48
        draw.rounded_rectangle([ax + 20, row_y, ax + 200, row_y + 36], radius=6, fill='#162238')
        draw.text((ax + 28, row_y + 8), label, fill='#38bdf8', font=get_font('sans', 17, bold=True))
        draw.text((ax + 215, row_y + 8), val, fill='#f1f5f9', font=get_font('sans', 17, bold=False))

    # ESP32 Card
    ex = pad + mcu_w + 40
    ey = 725
    eh = 440
    draw.rounded_rectangle([ex, ey, ex + mcu_w, ey + eh], radius=18, fill='#0f172a', outline='#1e293b', width=2)
    draw.rounded_rectangle([ex, ey, ex + mcu_w, ey + 60], radius=18, fill='#1e293b')
    draw.line([(ex, ey + 60), (ex + mcu_w, ey + 60)], fill='#e11d48', width=3)
    draw.text((ex + 24, ey + 16), 'ESP32 DEV MODULE — 32-BIT DUAL-CORE IoT POWERHOUSE', fill='#f43f5e', font=get_font('sans', 24, bold=True))

    esp_specs = [
        ('Architecture', '32-bit Xtensa Dual-Core LX6 @ up to 240 MHz Clock Speed'),
        ('Operating Voltage', '3.3V Logic — Strictly NOT 5V tolerant on GPIO inputs!'),
        ('Memory Capacity', '4 MB / 8 MB SPI Flash, 520 KB SRAM, 448 KB ROM'),
        ('Analog-to-Digital', '12-bit SAR ADC (4096 discrete steps, 0.8 mV resolution)'),
        ('Wireless Comms', 'Integrated 2.4 GHz Wi-Fi (802.11 b/g/n) + Bluetooth 4.2 & BLE'),
        ('Peripherals', '10 Capacitive Touch pins, 2 DAC channels, 3 UARTs, 2 I2C, 3 SPI'),
        ('Primary Application', 'IoT WebServers, cloud dashboards, REST APIs, and wireless sensor nodes')
    ]

    for li, (label, val) in enumerate(esp_specs):
        row_y = ey + 80 + li * 48
        draw.rounded_rectangle([ex + 20, row_y, ex + 200, row_y + 36], radius=6, fill='#271926')
        draw.text((ex + 28, row_y + 8), label, fill='#f43f5e', font=get_font('sans', 17, bold=True))
        draw.text((ex + 215, row_y + 8), val, fill='#f1f5f9', font=get_font('sans', 17, bold=False))

    # =========================================================================
    # SECTION 3: COMMUNICATION PROTOCOLS (y: 1210 - 1760)
    # =========================================================================
    draw.text((pad, 1210), '03 | ESSENTIAL EMBEDDED COMMUNICATION BUSES', fill='#f8fafc', font=get_font('sans', 32, bold=True))
    draw.line([(pad, 1255), (W - pad, 1255)], fill='#1e293b', width=2)

    proto_cards = [
        ('I2C (INTER-INTEGRATED CIRCUIT)',
         '• 2-Wire Serial Bus: SDA (Data) & SCL (Clock)\n• Open-drain design; requires pull-up resistors to VCC\n• Multi-slave architecture using 7-bit addresses (e.g. OLED = 0x3C)\n• Standard speeds: 100 kHz (Standard), 400 kHz (Fast Mode)\n• Ideal for: Displays, IMUs, RTCs, and environmental sensors',
         '#38bdf8'),
        ('SPI (SERIAL PERIPHERAL INTERFACE)',
         '• 4-Wire Synchronous Bus: MOSI, MISO, SCK, SS/CS\n• Full-duplex synchronous data transmission at high MHz speeds\n• Dedicated Slave Select (SS) lines control individual bus devices\n• Blazing fast bandwidth up to 10–50 Mbps\n• Ideal for: RFID readers (RC522), SD card modules, TFT screens',
         '#34d399'),
        ('UART (ASYNCHRONOUS SERIAL)',
         '• 2 Lines: TX (Transmit) & RX (Receive) cross-connected\n• Point-to-point asynchronous packet framing (Start, Data, Stop)\n• Common Baud Rates: 9600, 57600, 115200 bits per second\n• Built-in USB-UART bridge enables PC Serial Monitor debugging\n• Ideal for: GPS receivers, Bluetooth modules, and PC telemetry',
         '#a855f7'),
        ('PWM (PULSE WIDTH MODULATION)',
         '• Simulates analog voltage via rapid high-speed digital pulsing\n• Duty Cycle: D = (T_on / T_period) * 100% controls average power\n• 50 Hz PWM (20ms frame) used for Servo control: 1ms=0°, 2ms=180°\n• 8-bit resolution (0–255) on Uno; up to 16-bit LEDC on ESP32\n• Ideal for: LED dimming, motor speed drivers, and servo position',
         '#fbbf24')
    ]

    p_w = (W - 2*pad - 3*30) // 4
    for i, (title, body, accent) in enumerate(proto_cards):
        px = pad + i * (p_w + 30)
        py = 1275
        ph = 450
        draw.rounded_rectangle([px, py, px + p_w, py + ph], radius=16, fill='#0f172a', outline='#1e293b', width=2)
        draw.rounded_rectangle([px, py, px + p_w, py + 8], radius=4, fill=accent)
        draw.text((px + 20, py + 26), title, fill=accent, font=get_font('sans', 20, bold=True))

        lines = body.split('\n')
        for li, line in enumerate(lines):
            draw.text((px + 20, py + 75 + li * 40), line, fill='#cbd5e1', font=get_font('sans', 16, bold=False))

    # =========================================================================
    # SECTION 4: SENSORS & TRANSDUCERS GUIDE (y: 1780 - 2380)
    # =========================================================================
    draw.text((pad, 1770), '04 | SENSORS & TRANSDUCERS QUICK-REFERENCE GUIDE', fill='#f8fafc', font=get_font('sans', 32, bold=True))
    draw.line([(pad, 1815), (W - pad, 1815)], fill='#1e293b', width=2)

    sensor_cards = [
        ('DHT11 TEMP & HUMIDITY',
         'Capacitive humidity sensing element + NTC thermistor. Outputs 40-bit custom single-wire digital packet with parity verification. Measures 0–50°C (±2°C) and 20–90% RH (±5%).',
         '#38bdf8'),
        ('HC-SR04 ULTRASONIC',
         'Transmits eight 40 kHz acoustic sound bursts upon receiving a 10µs trigger pulse. Measures echo return duration: Distance (cm) = (Duration_µs * 0.0343) / 2. Effective range: 2–400 cm.',
         '#34d399'),
        ('MQ-SERIES GAS SENSORS',
         'Heated Tin Dioxide (SnO2) semiconductor. In clean air, electrical conductivity is low; in the presence of target gases (LPG, smoke, CO2, alcohol), conductivity increases proportionally.',
         '#f43f5e'),
        ('LDR PHOTORESISTOR',
         'Cadmium Sulfide (CdS) photo-conductive cell. Semiconductor resistance drops exponentially from megaohms in darkness down to a few hundred ohms under bright illumination.',
         '#fbbf24'),
        ('PIR MOTION DETECTOR',
         'Dual pyroelectric IR sensors split through a segmented Fresnel lens. Detects the differential infrared heat radiation emitted by warm moving human bodies or animals.',
         '#a855f7'),
        ('SOIL / WATER PROBES',
         'Measures electrical conductivity between exposed PCB traces. In high moisture/water, conductive paths bridge, significantly lowering resistance and shifting the ADC voltage.',
         '#38bdf8'),
        ('MAGNETIC REED SWITCH',
         'Two ferromagnetic flexible contact reeds sealed inside a glass tube. When an external magnetic field approaches, the contacts attract and close, providing a clean digital signal.',
         '#34d399'),
        ('RC522 13.56 MHz RFID',
         'NFC/RFID transceiver operating at 13.56 MHz. Powers passive 1KB Mifare classic transponders via electromagnetic induction and communicates with the host MCU via high-speed SPI.',
         '#fbbf24')
    ]

    s_col_w = (W - 2*pad - 3*30) // 4
    for i, (title, desc, accent) in enumerate(sensor_cards):
        r = i // 4
        c = i % 4
        sx = pad + c * (s_col_w + 30)
        sy = 1835 + r * 240
        sh = 215

        draw.rounded_rectangle([sx, sy, sx + s_col_w, sy + sh], radius=14, fill='#0f172a', outline='#1e293b', width=2)
        draw.rounded_rectangle([sx, sy, sx + 6, sy + sh], radius=3, fill=accent)
        draw.text((sx + 20, sy + 20), title, fill=accent, font=get_font('sans', 20, bold=True))
        draw_wrapped_text(draw, desc, sx + 20, sy + 60, 36, get_font('sans', 16, bold=False), '#cbd5e1', line_spacing=24, max_lines=6)

    # =========================================================================
    # SECTION 5: ACTUATORS & POWER DRIVERS (y: 2360 - 2860)
    # =========================================================================
    draw.text((pad, 2350), '05 | ACTUATORS & PHYSICAL ELECTROMECHANICAL CONTROL', fill='#f8fafc', font=get_font('sans', 32, bold=True))
    draw.line([(pad, 2395), (W - pad, 2395)], fill='#1e293b', width=2)

    actuators = [
        ('5V OPTOCOUPLED RELAY MODULE',
         '• Optical Galvanic Isolation: Protects sensitive microcontrollers from high-voltage AC/DC surges.\n• Contacts: COM (Common), NO (Normally Open), and NC (Normally Closed) rated up to 10A @ 250VAC.\n• Active-LOW Logic: Writing digital LOW energizes the internal optocoupler LED and triggers the relay coil.\n• Flyback Protection: Integrated reverse diode clamps high inductive voltage spikes upon de-energizing.',
         '#f43f5e'),
        ('SG90 MICRO SERVO MOTOR',
         '• Closed-Loop Actuator: Consists of a high-torque DC motor, reduction gear train, and feedback potentiometer.\n• PWM Timing: Driven by a 50 Hz PWM signal (20ms period). Pulse width governs mechanical output shaft angle:\n    - 1.0 ms pulse = 0° (Minimum Position)\n    - 1.5 ms pulse = 90° (Neutral / Center Position)\n    - 2.0 ms pulse = 180° (Maximum Position)',
         '#38bdf8'),
        ('ACTIVE PIEZO BUZZER & DISPLAYS',
         '• Active Buzzer: Built-in oscillating circuit emits continuous ~2.3 kHz acoustic alarm on DC 5V.\n• 0.96" SSD1306 OLED: 128x64 pixels, hardware I2C interface, low 20mA power draw, infinite contrast ratio.\n• 7-Segment Display: 8 multiplexed LEDs (a–g + decimal point) in Common Cathode / Common Anode formats.\n• RGB LEDs: Tri-color mixing via pulse-width modulation across Red, Green, and Blue diodes.',
         '#34d399')
    ]

    act_w = (W - 2*pad - 2*30) // 3
    for i, (title, desc, accent) in enumerate(actuators):
        ax = pad + i * (act_w + 30)
        ay = 2415
        ah = 390
        draw.rounded_rectangle([ax, ay, ax + act_w, ay + ah], radius=16, fill='#0f172a', outline='#1e293b', width=2)
        draw.rounded_rectangle([ax, ay, ax + act_w, ay + 8], radius=4, fill=accent)
        draw.text((ax + 20, ay + 26), title, fill=accent, font=get_font('sans', 21, bold=True))

        lines = desc.split('\n')
        for li, line in enumerate(lines):
            draw.text((ax + 20, ay + 75 + li * 34), line, fill='#cbd5e1', font=get_font('sans', 16, bold=False))

    # =========================================================================
    # SECTION 6: GOLDEN RULES & CIRCUIT SAFETY (y: 2840 - 3380)
    # =========================================================================
    draw.text((pad, 2850), '06 | GOLDEN RULES OF HARDWARE PROTOTYPING & CIRCUIT SAFETY', fill='#f8fafc', font=get_font('sans', 32, bold=True))
    draw.line([(pad, 2895), (W - pad, 2895)], fill='#1e293b', width=2)

    safety_rules = [
        ('COMMON GROUND (GND) REFERENCE',
         'Always tie the GND pins of all external power supplies, sensors, motor drivers, and microcontrollers together. Without a shared common zero-volt reference, logic signal voltages will float erratically.',
         '#38bdf8'),
        ('3.3V vs 5V LOGIC LEVEL COMPATIBILITY',
         'ESP32 GPIO pins operate at 3.3V LVTTL and are NOT 5V tolerant! Never connect a 5V sensor output directly to an ESP32 pin. Always step down 5V using a 10kΩ/20kΩ voltage divider or bidirectional logic level shifter.',
         '#f43f5e'),
        ('INDUCTIVE LOAD TRANSIENT PROTECTION',
         'Inductive components (solenoids, relay coils, DC motors, water pumps) generate severe reverse-EMF voltage spikes when switched off. Always power them via separate power rails with flyback diodes.',
         '#fbbf24'),
        ('INPUT-ONLY PINS & NOISE FILTERING',
         'On the ESP32, GPIO 34, 35, 36, and 39 are hardware input-only pins without internal pull-ups or pull-downs. Always apply a 10–12 sample software averaging filter to analog readings to eliminate high-frequency ADC noise.',
         '#34d399')
    ]

    rule_w = (W - 2*pad - 3*30) // 4
    for i, (title, desc, accent) in enumerate(safety_rules):
        rx = pad + i * (rule_w + 30)
        ry = 2915
        rh = 360
        draw.rounded_rectangle([rx, ry, rx + rule_w, ry + rh], radius=16, fill='#0f172a', outline='#1e293b', width=2)
        draw.rounded_rectangle([rx, ry, rx + rule_w, ry + 8], radius=4, fill=accent)
        draw.text((rx + 20, ry + 26), title, fill=accent, font=get_font('sans', 19, bold=True))
        draw_wrapped_text(draw, desc, rx + 20, ry + 75, 33, get_font('sans', 16, bold=False), '#cbd5e1', line_spacing=26, max_lines=9)

    # =========================================================================
    # FOOTER & REPOSITORY ATTRIBUTION
    # =========================================================================
    draw.line([(pad, 3330), (W - pad, 3330)], fill='#1e293b', width=2)
    f_foot = get_font('sans', 22, bold=False)
    f_foot_b = get_font('sans', 22, bold=True)
    draw.text((W//2, 3370), 'Pavank5214 / iot-project-kit  •  Educational Hardware Reference Architecture & Engineering Primer', fill='#64748b', anchor='mm', font=f_foot)
    draw.text((W//2, 3410), 'Open-Source Learning Blueprint for STEM Education, College Maker Labs, Robotics Clubs & IoT Designers', fill='#94a3b8', anchor='mm', font=f_foot_b)

    output_path = 'assets/iot-learning-poster.png'
    img.save(output_path, 'PNG', quality=95)
    print(f'Created: {output_path}')

generate_learning_poster()
