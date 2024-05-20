#include <Servo.h> // Import Servo library

#define TRIGGER_PIN 7 // Trigger pin of the ultrasonic sensor
#define ECHO_PIN 6 // Echo pin of the ultrasonic sensor

Servo myservo; 
Servo myservo1;

int ledRed = 13; // Red LED pin
int ledGreen = 12; // Green LED pin

void setup() {
  pinMode(ledRed, OUTPUT); 
  pinMode(ledGreen, OUTPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  myservo.attach(9, 500, 2500);   
  myservo1.attach(10, 500, 2500);

  myservo.write(0); // Initialize servos to 0 position
  myservo1.write(0);
}

void loop() {
  long duration, distance;
  
  // Trigger the ultrasonic sensor
  digitalWrite(TRIGGER_PIN, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);

  // Read the echo pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance
  distance = duration * 0.034 / 2; // Distance in cm

  if (distance > 0 && distance <= 10) { // Object detected within 10 cm
    digitalWrite(ledRed, HIGH); // Turn on red LED
    digitalWrite(ledGreen, LOW); // Turn off green LED

    myservo.write(90); // Close servo1
    myservo1.write(0); // Open servo2
  } else {
    digitalWrite(ledRed, LOW); // Turn off red LED
    digitalWrite(ledGreen, HIGH); // Turn on green LED

    myservo.write(0); // Open servo1
    myservo1.write(90); // Close servo2
  }

  delay(1000); // Wait for 1 second before the next loop
}