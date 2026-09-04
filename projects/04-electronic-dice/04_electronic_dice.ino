/*
  Project 04: Electronic Die with 7-Segment Display & Touch Sensor
  IoT Project Kit - Arduino Uno

  Description:
  Simulates a 6-sided electronic die. When the capacitive touch sensor is touched,
  a spinning animation pattern is shown on the 7-segment display, followed by a
  randomly generated number between 1 and 6.

  Hardware Connections:
  - 7-Segment Display (Common Anode):
      - Segment A -> Digital Pin 11
      - Segment B -> Digital Pin 10
      - Segment C -> Digital Pin 9
      - Segment D -> Digital Pin 8
      - Segment E -> Digital Pin 7
      - Segment F -> Digital Pin 6
      - Segment G -> Digital Pin 5
      - Common Anode Pin -> 5V (via 220Ω Resistor)
  - TTP223 Capacitive Touch Sensor:
      - VCC -> 5V
      - GND -> GND
      - OUT (SIG) -> Digital Pin 3
*/

// Pin Definitions for 7-Segment LED
const int seg_a = 11;
const int seg_b = 10;
const int seg_c = 9;
const int seg_d = 8;
const int seg_e = 7;
const int seg_f = 6;
const int seg_g = 5;

// Touch Sensor Pin
const int sensor = 3;

int i = 0; // Stores the generated random dice number

void pattern();
void sevenSeg();

void setup() {
  // Initialize segment pins as outputs
  pinMode(seg_a, OUTPUT); 
  pinMode(seg_b, OUTPUT);
  pinMode(seg_c, OUTPUT);
  pinMode(seg_d, OUTPUT);
  pinMode(seg_e, OUTPUT);
  pinMode(seg_f, OUTPUT);
  pinMode(seg_g, OUTPUT);
  
  // Touch Sensor Input
  pinMode(sensor, INPUT);

  // Play initial idle pattern until first touch
  while (digitalRead(sensor) == LOW) {
    pattern(); // Display spinning pattern on 7-segment LED
  }
  
  // Seed random number generator with floating analog pin A0
  randomSeed(analogRead(A0));
}

void loop() {
  // Trigger dice roll when touch sensor goes HIGH
  if (digitalRead(sensor) == HIGH) {
    i = random(1, 7); // Random number between 1 and 6

    // Play rolling animation 3 times
    for (int pat = 0; pat <= 2; pat++) {
      pattern();
    }
    
    // Display the rolled dice digit
    sevenSeg();
  }
}

// Display 1–6 on Common Anode 7-Segment Display (LOW = ON, HIGH = OFF)
void sevenSeg() {
  if (i == 1) {
    digitalWrite(seg_a, HIGH);
    digitalWrite(seg_b, LOW);
    digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, HIGH);
    digitalWrite(seg_e, HIGH);
    digitalWrite(seg_f, HIGH);
    digitalWrite(seg_g, HIGH);
    delay(20); // Digit 1
  } else if (i == 2) {
    digitalWrite(seg_a, LOW);
    digitalWrite(seg_b, LOW);
    digitalWrite(seg_c, HIGH);
    digitalWrite(seg_d, LOW);
    digitalWrite(seg_e, LOW);
    digitalWrite(seg_f, HIGH);
    digitalWrite(seg_g, LOW);
    delay(20); // Digit 2
  } else if (i == 3) {
    digitalWrite(seg_a, LOW);
    digitalWrite(seg_b, LOW);
    digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, LOW);
    digitalWrite(seg_e, HIGH);
    digitalWrite(seg_f, HIGH);
    digitalWrite(seg_g, LOW);
    delay(20); // Digit 3
  } else if (i == 4) {
    digitalWrite(seg_a, HIGH);
    digitalWrite(seg_b, LOW);
    digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, HIGH);
    digitalWrite(seg_e, HIGH);
    digitalWrite(seg_f, LOW);
    digitalWrite(seg_g, LOW);
    delay(20); // Digit 4
  } else if (i == 5) {
    digitalWrite(seg_a, LOW);
    digitalWrite(seg_b, HIGH);
    digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, LOW);
    digitalWrite(seg_e, HIGH);
    digitalWrite(seg_f, LOW);
    digitalWrite(seg_g, LOW);
    delay(20); // Digit 5
  } else if (i == 6) {
    digitalWrite(seg_a, LOW);
    digitalWrite(seg_b, HIGH);
    digitalWrite(seg_c, LOW);
    digitalWrite(seg_d, LOW);
    digitalWrite(seg_e, LOW);
    digitalWrite(seg_f, LOW);
    digitalWrite(seg_g, LOW);
    delay(20); // Digit 6
  }
}

// Spinning perimeter animation pattern
void pattern() {
  digitalWrite(seg_a, LOW);
  digitalWrite(seg_b, HIGH);
  digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, HIGH);
  digitalWrite(seg_e, HIGH);
  digitalWrite(seg_f, HIGH);
  digitalWrite(seg_g, HIGH);
  delay(100);
  
  digitalWrite(seg_a, HIGH);
  digitalWrite(seg_b, LOW);
  digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, HIGH);
  digitalWrite(seg_e, HIGH);
  digitalWrite(seg_f, HIGH);
  digitalWrite(seg_g, HIGH);
  delay(100);

  digitalWrite(seg_a, HIGH);
  digitalWrite(seg_b, HIGH);
  digitalWrite(seg_c, LOW);
  digitalWrite(seg_d, HIGH);
  digitalWrite(seg_e, HIGH);
  digitalWrite(seg_f, HIGH);
  digitalWrite(seg_g, HIGH);
  delay(100);

  digitalWrite(seg_a, HIGH);
  digitalWrite(seg_b, HIGH);
  digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, LOW);
  digitalWrite(seg_e, HIGH);
  digitalWrite(seg_f, HIGH);
  digitalWrite(seg_g, HIGH);
  delay(100);

  digitalWrite(seg_a, HIGH);
  digitalWrite(seg_b, HIGH);
  digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, HIGH);
  digitalWrite(seg_e, LOW);
  digitalWrite(seg_f, HIGH);
  digitalWrite(seg_g, HIGH);
  delay(100);

  digitalWrite(seg_a, HIGH);
  digitalWrite(seg_b, HIGH);
  digitalWrite(seg_c, HIGH);
  digitalWrite(seg_d, HIGH);
  digitalWrite(seg_e, HIGH);
  digitalWrite(seg_f, LOW);
  digitalWrite(seg_g, HIGH);
  delay(100);
}
