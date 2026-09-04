/*
  Project 05: RGB Mood Lamp / Smooth Color Fader
  IoT Project Kit - Arduino Uno

  Description:
  Creates an ambient RGB mood lamp that smoothly transitions (fades) between randomly
  generated colors using Pulse Width Modulation (PWM) and linear interpolation.

  Circuit Connections:
  - Red Pin   -> PWM Pin 11 (via 220Ω Resistor)
  - Green Pin -> PWM Pin 10 (via 220Ω Resistor)
  - Blue Pin  -> PWM Pin 9  (via 220Ω Resistor)
  - Cathode   -> GND (Common Cathode RGB LED)
*/

// Color arrays for interpolation
float RGB1[3]; // Current RGB color state
float RGB2[3]; // Target RGB color state
float INC[3];  // Increment step per iteration

int red, green, blue;

// PWM Pin Definitions
const int RedPin = 11;
const int GreenPin = 10;
const int BluePin = 9;

void setup() {
  Serial.begin(9600);
  
  // Seed random number generator using floating analog pin A0
  randomSeed(analogRead(0));

  // Initialize start color to Black (0, 0, 0)
  RGB1[0] = 0;
  RGB1[1] = 0;
  RGB1[2] = 0;

  // Generate initial target RGB color values (0–255)
  RGB2[0] = random(256);
  RGB2[1] = random(256);
  RGB2[2] = random(256);
}

void loop() {
  // Re-seed random number generator for variety
  randomSeed(analogRead(0));

  // Calculate increment step for each color channel across 256 fade steps
  for (int x = 0; x < 3; x++) {
    INC[x] = (RGB1[x] - RGB2[x]) / 256.0;
  }

  // Smoothly fade from RGB1 to RGB2
  for (int x = 0; x < 256; x++) {
    red = int(RGB1[0]);
    green = int(RGB1[1]);
    blue = int(RGB1[2]);

    // Output PWM signals to RGB LED pins
    analogWrite(RedPin, red);
    analogWrite(GreenPin, green);
    analogWrite(BluePin, blue);

    delay(100); // Control fade speed (100ms * 256 steps ≈ 25.6s transition)

    // Update color steps
    RGB1[0] -= INC[0];
    RGB1[1] -= INC[1];
    RGB1[2] -= INC[2];
  }

  // Select new target RGB color for the next transition cycle
  for (int x = 0; x < 3; x++) {
    RGB2[x] = random(556) - 300;
    RGB2[x] = constrain(RGB2[x], 0, 255);
    delay(1000);
  }
}
