/*
  Project 01: LED Blinking
  IoT Project Kit - Arduino Uno
  
  Description:
  Demonstrates basic digital output by turning an LED ON and OFF at 1-second intervals.
  
  Circuit Connections:
  - LED Anode (+)   -> Arduino Pin 13
  - LED Cathode (-) -> GND (No external resistor required; powered via USB)
*/

// Define the digital pin connected to the LED
const int LED_PIN = 13;

void setup() {
  // Initialize digital pin 13 as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);  // Turn the LED ON (Supply 5V)
  delay(1000);                  // Wait for 1000 milliseconds (1 second)

  digitalWrite(LED_PIN, LOW);   // Turn the LED OFF (Supply 0V)
  delay(1000);                  // Wait for 1000 milliseconds (1 second)
}
