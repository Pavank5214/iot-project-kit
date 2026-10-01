import os
import qrcode
from PIL import Image, ImageDraw, ImageFont

os.makedirs('assets', exist_ok=True)

# Helper to load fonts safely
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

# -------------------------------------------------------------------------
# POSTER 1: STANDALONE QR CODE SHOWCASE POSTER (assets/qr-showcase-poster.png)
# -------------------------------------------------------------------------
def generate_qr_poster():
    W, H = 2000, 2800
    img = Image.new('RGB', (W, H), '#080d1a')
    draw = ImageDraw.Draw(img)

    # Decorative top glow lines
    for i in range(16):
        alpha_color = '#38bdf8' if i < 8 else '#818cf8'
        draw.line([(0, i), (W, i)], fill=alpha_color)

    # Subtle background grid lines
    grid_spacing = 80
    for x in range(0, W, grid_spacing):
        draw.line([(x, 16), (x, H)], fill='#0e1726', width=1)
    for y in range(16, H, grid_spacing):
        draw.line([(0, y), (W, y)], fill='#0e1726', width=1)

    # Top Tag / Badge
    f_badge = get_font('sans', 24, bold=True)
    draw.rounded_rectangle([W//2 - 280, 70, W//2 + 280, 120], radius=12, fill='#111c33', outline='#38bdf8', width=2)
    draw.text((W//2, 95), 'OPEN SOURCE HARDWARE & CODE HUB', fill='#38bdf8', anchor='mm', font=f_badge)

    # Main Header
    f_h1 = get_font('sans', 76, bold=True)
    f_sub = get_font('sans', 32, bold=False)
    f_tagline = get_font('sans', 24, bold=False)

    draw.text((W//2, 180), 'IoT PROJECT KIT', fill='#ffffff', anchor='mm', font=f_h1)
    draw.text((W//2, 250), 'Complete Learning Repository • Circuit Schematics • Source Code', fill='#94a3b8', anchor='mm', font=f_sub)
    draw.text((W//2, 295), 'Arduino Uno R3 & ESP32 Dev Module Embedded Hardware Guides', fill='#38bdf8', anchor='mm', font=f_tagline)

    # Central Showcase Card with Large QR Code
    card_w, card_h = 1000, 1260
    card_x = (W - card_w) // 2
    card_y = 360

    # Glow border effect
    for b in range(6, 0, -1):
        draw.rounded_rectangle([card_x - b*2, card_y - b*2, card_x + card_w + b*2, card_y + card_h + b*2],
                               radius=28, outline='#1e3a5f')
    draw.rounded_rectangle([card_x, card_y, card_x + card_w, card_y + card_h], radius=24, fill='#0f172a', outline='#38bdf8', width=4)

    # Card Header
    draw.rectangle([card_x, card_y, card_x + card_w, card_y + 110], fill='#1e293b')
    draw.line([(card_x, card_y + 110), (card_x + card_w, card_y + 110)], fill='#38bdf8', width=2)
    f_card_title = get_font('sans', 36, bold=True)
    f_card_sub = get_font('sans', 20, bold=False)
    draw.text((W//2, card_y + 45), 'SCAN TO EXPLORE REPOSITORY', fill='#38bdf8', anchor='mm', font=f_card_title)
    draw.text((W//2, card_y + 82), 'Instant access via any smartphone camera or QR reader', fill='#94a3b8', anchor='mm', font=f_card_sub)

    # Generate High-Res Scannable QR Code
    repo_url = 'https://github.com/Pavank5214/iot-project-kit'
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_H,
        box_size=18,
        border=3,
    )
    qr.add_data(repo_url)
    qr.make(fit=True)
    qr_img = qr.make_image(fill_color='#0f172a', back_color='#ffffff').convert('RGBA')

    # White inner mount for QR code with rounded corners
    mount_w, mount_h = 760, 760
    mount_x = (W - mount_w) // 2
    mount_y = card_y + 145
    draw.rounded_rectangle([mount_x, mount_y, mount_x + mount_w, mount_y + mount_h], radius=20, fill='#ffffff')

    qr_resized = qr_img.resize((720, 720), Image.Resampling.LANCZOS)
    img.paste(qr_resized, (mount_x + 20, mount_y + 20), qr_resized)

    # Card URL / Link Section
    link_bar_y = mount_y + mount_h + 30
    draw.rounded_rectangle([card_x + 50, link_bar_y, card_x + card_w - 50, link_bar_y + 70], radius=14, fill='#1e293b', outline='#334155', width=2)
    f_url = get_font('mono', 26, bold=True)
    draw.text((W//2, link_bar_y + 35), 'github.com/Pavank5214/iot-project-kit', fill='#38bdf8', anchor='mm', font=f_url)

    # Card footer note
    f_hint = get_font('sans', 20, bold=False)
    draw.text((W//2, card_y + card_h - 40), 'Open Source • Free to Fork & Star • Step-by-Step Documentation', fill='#64748b', anchor='mm', font=f_hint)

    # 4 Feature / Knowledge Highlight Cards underneath
    f_sec_h = get_font('sans', 32, bold=True)
    draw.text((W//2, 1690), 'WHAT YOU WILL FIND IN THE REPOSITORY', fill='#f8fafc', anchor='mm', font=f_sec_h)
    draw.line([(W//2 - 250, 1720), (W//2 + 250, 1720)], fill='#38bdf8', width=2)

    features = [
        ('COMPLETE WIRING DIAGRAMS',
         'Detailed Cirkit Designer schematics & ASCII pinout maps for every sensor, actuator, display, and controller module.',
         '#38bdf8'),
        ('PRODUCTION ARDUINO & ESP32 CODE',
         'Clean, modular, thoroughly commented C/C++ sketches with sensor filtering, debounce logic, and WebServer dashboards.',
         '#34d399'),
        ('HARDWARE & BILL OF MATERIALS',
         'Exhaustive component checklists with electrical pinouts, recommended operating voltages, and resistor guidelines.',
         '#a855f7'),
        ('IOT & EMBEDDED SYSTEM CONCEPTS',
         'Hands-on tutorials explaining I2C, SPI, UART, ADC calibration, PWM power driving, and Wi-Fi HTTP telemetry.',
         '#fbbf24'),
    ]

    col_w = (W - 160 - 40) // 2
    for i, (title, desc, accent) in enumerate(features):
        r = i // 2
        c = i % 2
        fx = 80 + c * (col_w + 40)
        fy = 1760 + r * 220

        draw.rounded_rectangle([fx, fy, fx + col_w, fy + 190], radius=16, fill='#0f172a', outline='#1e293b', width=2)
        # Accent left border
        draw.rounded_rectangle([fx, fy, fx + 8, fy + 190], radius=4, fill=accent)

        f_ftitle = get_font('sans', 22, bold=True)
        f_fdesc = get_font('sans', 18, bold=False)

        draw.text((fx + 30, fy + 35), title, fill=accent, font=f_ftitle)

        # Word-wrap description
        words = desc.split()
        lines = []
        cur_line = []
        for w in words:
            cur_line.append(w)
            if len(' '.join(cur_line)) > 55:
                lines.append(' '.join(cur_line[:-1]))
                cur_line = [w]
        if cur_line:
            lines.append(' '.join(cur_line))

        for li, line_text in enumerate(lines[:3]):
            draw.text((fx + 30, fy + 75 + li * 28), line_text, fill='#cbd5e1', font=f_fdesc)

    # Bottom Instructions Bar
    draw.rounded_rectangle([80, 2260, W - 80, 2380], radius=16, fill='#111c33', outline='#38bdf8', width=2)
    f_bar_h = get_font('sans', 24, bold=True)
    f_bar_t = get_font('sans', 19, bold=False)
    draw.text((W//2, 2295), 'HOW TO CONNECT & LEARN AT THE BOOTH / LAB', fill='#ffffff', anchor='mm', font=f_bar_h)
    draw.text((W//2, 2335), '1. Open Camera App  ->  2. Point at QR Code  ->  3. Tap Notification  ->  4. Browse Code & Circuit Diagrams Instantly', fill='#38bdf8', anchor='mm', font=f_bar_t)

    # Footer
    draw.line([(80, 2440), (W - 80, 2440)], fill='#1e293b', width=2)
    f_foot = get_font('sans', 20, bold=False)
    f_foot_b = get_font('sans', 20, bold=True)
    draw.text((W//2, 2480), 'Pavank5214 / iot-project-kit  •  Open-Source Educational Hardware Collection', fill='#64748b', anchor='mm', font=f_foot)
    draw.text((W//2, 2515), 'Built for STEM Students, Robotics Labs, College Makerspaces, and Embedded IoT Engineers', fill='#94a3b8', anchor='mm', font=f_foot_b)

    # Save image
    output_path = 'assets/qr-showcase-poster.png'
    img.save(output_path, 'PNG', quality=95)
    print(f'Created: {output_path}')

generate_qr_poster()
