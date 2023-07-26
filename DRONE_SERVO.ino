
//This code is only to test the working of drilling motor .
const int pulsePinPositive = D5; // Connect to "pulse+" pin on the motor driver
const int pulsePinNegative = D6; // Connect to "pulse-" pin on the motor driver
const int dirPinPositive = D7;   // Connect to "dir+" pin on the motor driver
const int dirPinNegative = D8;   // Connect to "dir-" pin on the motor driver

void setup() {
  // Set the pins as OUTPUT
  pinMode(pulsePinPositive, OUTPUT);
  pinMode(pulsePinNegative, OUTPUT);
  pinMode(dirPinPositive, OUTPUT);
  pinMode(dirPinNegative, OUTPUT);
}

void loop() {

for(int i=0;i<2000;i++){
  digitalWrite(dirPinPositive, HIGH);
  digitalWrite(dirPinNegative, LOW);

  // Generate a pulse signal
  digitalWrite(pulsePinPositive, HIGH);
  digitalWrite(pulsePinNegative, LOW);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed
  digitalWrite(pulsePinPositive, LOW);
  digitalWrite(pulsePinNegative, HIGH);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed
}
delay(1000);
for(int J=0;J<2000;J++){
  digitalWrite(dirPinPositive, LOW);
  digitalWrite(dirPinNegative, HIGH);

  // Generate a pulse signal
  digitalWrite(pulsePinPositive, HIGH);
  digitalWrite(pulsePinNegative, LOW);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed
  digitalWrite(pulsePinPositive, LOW);
  digitalWrite(pulsePinNegative, HIGH);
  delayMicroseconds(100); // Adjust the delay as needed to control motor speed
}



}
// Function to stop the mot
