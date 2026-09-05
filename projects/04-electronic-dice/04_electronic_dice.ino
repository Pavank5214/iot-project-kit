/*
  Project 04: Electronic Die with 7-Segment Display & Push Button
  IoT Project Kit - Arduino Uno

  Description:
  Simulates a 6-sided electronic rolling die using a 7-Segment LED display and a push button.
  When the push button is held down (Pin 12 -> INPUT_PULLUP), a rapid sequence of numbers (1 to 6)
  is displayed to simulate a rolling motion. When released, a random number between 1 and 6
  is picked and displayed.

  Circuit Connections:
  - 7-Segment Display (Common Cathode):
      - Segment A -> Digital Pin 7
      - Segment B -> Digital Pin 6
      - Segment C -> Digital Pin 4
      - Segment D -> Digital Pin 3
      - Segment E -> Digital Pin 2
      - Segment F -> Digital Pin 8
      - Segment G -> Digital Pin 9
      - Common Cathode Pin -> GND (via 220Ω Resistor)
  - Push Button:
      - Terminal 1 -> Digital Pin 12 (Internal Pull-Up enabled)
      - Terminal 2 -> GND
*/

// Pin Definitions for 7-Segment Display
const int A = 7;
const int B = 6;
const int C = 4;
const int D = 3;
const int E = 2;
const int F = 8;
const int G = 9;

// Push Button Pin (Internal Pull-Up)
const int buttonPin = 12;

int random_int = 0;

// Function prototypes
void one();
void two();
void three();
void four();
void five();
void six();

void setup() {
  // Initialize segment pins as outputs
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  // Initialize push button with internal pull-up resistor (NO external resistor needed)
  pinMode(buttonPin, INPUT_PULLUP);

  // Seed random number generator with floating analog pin A0
  randomSeed(analogRead(A0));
}

void loop() {
  int pusshed = digitalRead(buttonPin);

  // If push button is pressed (LOW due to INPUT_PULLUP)
  if (pusshed == LOW) {
    random_int = random(1, 7); // Pick random number between 1 and 6

    // Rapidly cycle digits to simulate a rolling dice effect
    one();   delay(20);
    two();   delay(20);
    three(); delay(20);
    four();  delay(20);
    five();  delay(20);
    six();   delay(20);
  } 
  else {
    // Display the rolled dice number when button is released
    switch (random_int) {
      case 1: one();   break;
      case 2: two();   break;
      case 3: three(); break;
      case 4: four();  break;
      case 5: five();  break;
      case 6: six();   break;
    }
    delay(200);
  }
}

// -------------------------------------------------------------
// Common Cathode 7-Segment Digit Functions (HIGH = ON, LOW = OFF)
// -------------------------------------------------------------

void one() {
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, LOW);
}

void two() {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void three() {
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void four() {
  digitalWrite(A, LOW);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void five() {
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void six() {
  digitalWrite(A, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}
