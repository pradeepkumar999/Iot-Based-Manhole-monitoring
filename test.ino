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
