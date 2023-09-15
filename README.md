
# IoT-Based Manhole Monitoring System

## Introduction

Manhole monitoring is crucial for municipal infrastructure as accidents caused by broken or missing manhole covers are common. Poor manhole management can lead to urban floods, especially in crowded cities. This project outlines the development of an IoT-based Manhole Monitoring device to address these issues. The system employs gas, ultrasonic, and tilt sensors to monitor gas levels, water levels, and manhole cover tilting. When predefined thresholds are exceeded, the system sends SMS notifications to an authority using the SIM800L GSM Module. The system is powered by a 18650 cell.

## Table of Contents

- [Components Required](#components-required)
- [Circuit Diagram](#circuit-diagram)
- [Code](#code)
- [Building the Circuit](#building-the-circuit)
- [Testing](#testing)
- [Contributions](#contributions)
- [License](#license)

## Components Required

- NodeMCU
- SIM800L GSM Module
- XL6009 Booster Module
- MQ Gas Sensor
- KY-017 Mercury Tilt Switch Module
- JSN SR-04T Waterproof Ultrasonic Sensor
- 18650 Cell & Cell Holder

## Circuit Diagram

The circuit includes gas, ultrasonic, and tilt sensors, an XL6009 Booster Module, a SIM800L GSM Module, and a 18650 cell. The booster module increases the voltage from the 18650 cell to 5V. The gas sensor detects gas presence, the ultrasonic sensor measures water level, and the tilt sensor detects manhole cover tilting. The SIM800L GSM Module sends SMS notifications.

## Building the Circuit
After testing the circuit on a breadboard, transfer it to a perf-board for a more practical application. The soldered board should resemble the following image:

## Manhole Monitoring Device

## Testing
Test the setup by simulating various scenarios, such as tilting the cover, detecting gas, and measuring water levels. The system should send SMS notifications when thresholds are exceeded.

## Contributions
This project welcomes contributions from the community. If you'd like to contribute, please follow these guidelines:

## Fork the repository.
Create a new branch for your feature or bug fix: git checkout -b feature-name.
Make your changes and commit them with clear commit messages.
Push your changes to your fork.
Create a pull request to the main repository, explaining your changes.
Contributions will be reviewed, and feedback will be provided. Thank you for contributing to this project!


## Code

```cpp
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Wi-Fi credentials
char auth[] = "9HCsk5yfshJr2sRj471PSPxYcG5NIgWg";
char ssid[] = "vivo Y21G";
char password[] = "12345678";

// Tilt sensor pin
const int tiltSensorPin = D2;

// Gas sensor pin
const int gasSensorPin = A0;

// Ultrasonic sensor pins
const int trigPin = D5;
const int echoPin = D6;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(tiltSensorPin, INPUT_PULLUP); // Set tilt sensor pin as input with internal pull-up resistor
  pinMode(trigPin, OUTPUT); // Set trig pin as output
  pinMode(echoPin, INPUT); // Set echo pin as input

  Blynk.begin(auth, ssid, password); // Connect to Blynk
}

void loop() {
  Blynk.run(); // Run Blynk background tasks

  // Read tilt sensor value
  int tiltValue = digitalRead(tiltSensorPin);

  // Read gas sensor value
  int gasValue = analogRead(gasSensorPin);

  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo pin duration
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  int distance = duration / 58;

  // Print sensor values to serial monitor
  Serial.print("Tilt sensor value: ");
  Serial.println(tiltValue);
  Serial.print("Gas sensor value: ");
  Serial.println(gasValue);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Send sensor values to Blynk app
  Blynk.virtualWrite(V0, tiltValue); // Send tilt sensor value to Virtual Pin V1
  Blynk.virtualWrite(V1, gasValue); // Send gas sensor value to Virtual Pin V2
  Blynk.virtualWrite(V2, distance); // Send distance to Virtual Pin V3

  delay(1000); // Delay for 1 second
}
