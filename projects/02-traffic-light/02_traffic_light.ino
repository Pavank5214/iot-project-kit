/*
  Project 02: Traffic Light Controller
  IoT Project Kit - Arduino Uno

  Description:
  Controls a 3-LED traffic light system in a standard automatic sequence:
  1. Green LED ON for 5 seconds
  2. Yellow LED ON for 2 seconds
  3. Red LED ON for 5 seconds
  The sequence repeats indefinitely.

  Circuit Connections:
  - Green LED Pin (G)  -> Digital Pin 3
  - Yellow LED Pin (Y) -> Digital Pin 2
  - Red LED Pin (R)    -> Digital Pin 1
  - Ground (GND)       -> GND
*/

// Pin definitions
const int greenPin = 3;
const int yellowPin = 2;
const int redPin = 1;

void setup() {
  // Initialize the digital pins as outputs
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
}

void loop() {
  // Green LED on for 5 seconds
  digitalWrite(greenPin, HIGH);
  delay(5000);
  digitalWrite(greenPin, LOW);

  // Yellow LED on for 2 seconds
  digitalWrite(yellowPin, HIGH);
  delay(2000);
  digitalWrite(yellowPin, LOW);

  // Red LED on for 5 seconds
  digitalWrite(redPin, HIGH);
  delay(5000);
  digitalWrite(redPin, LOW);
}
