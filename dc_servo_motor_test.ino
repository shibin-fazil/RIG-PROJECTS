#include <AccelStepper.h>

// Stepper Motor Connections
const int pulsePositivePin = 9;    // Positive pulse pin
const int pulseNegativePin = 10;   // Negative pulse pin
const int directionPositivePin = 11;   // Positive direction pin
const int directionNegativePin = 12;   // Negative direction pin

// Create an instance of AccelStepper
AccelStepper stepper(AccelStepper::DRIVER, pulsePositivePin, pulseNegativePin);

void setup() {
  // Initialize motor control pins as outputs
  pinMode(pulsePositivePin, OUTPUT);
  pinMode(pulseNegativePin, OUTPUT);
  pinMode(directionPositivePin, OUTPUT);
  pinMode(directionNegativePin, OUTPUT);

  // Set motor speed and acceleration
  stepper.setMaxSpeed(5000);  // Set maximum motor speed in steps per second
  stepper.setAcceleration(5000);  // Set motor acceleration in steps per second per second

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();

    // Move the stepper motor based on the input character
    switch (input) {
      case 'A':
      case 'a':
        digitalWrite(directionPositivePin, HIGH);
        digitalWrite(directionNegativePin, LOW);
        stepper.move(-5000);  // Move 1000 steps
        stepper.runToPosition();  // Wait until the motor reaches the target position
          // Set initial motor direction
        
        break;
        
      case 'S':
      case 's':
        stepper.stop();  // Stop the motor
        break;

      case 'D':
      case 'd':
        digitalWrite(directionPositivePin, LOW);
        digitalWrite(directionNegativePin, HIGH);
        stepper.move(-5000);  // Move 1000 steps in the opposite direction
        stepper.runToPosition();  // Wait until the motor reaches the target position
        break;
    }
  }
}
