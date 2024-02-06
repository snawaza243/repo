#include <ESP32Servo.h>
Servo myservo;  // crte servo object to control a servo
// Define LDR pin and LED pin
int ldrPin = 14;
int ledPin = 13;

void setup() {
  myservo.attach(2);  // attaches the servo on GPIO pin 2 to the servo object

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  myservo.write(90);  // sets the servo position to 90 degrees
  delay(1000);        // waits for 1 second
  myservo.write(0);   // sets the servo position to 0 degrees
  delay(1000);        // waits for 1 second

  // Read LDR value
  int ldrValue = analogRead(ldrPin);
  // Print LDR value to serial monitor
  Serial.print("LDR value: ");
  Serial.println(ldrValue);
  // Map LDR value to LED brightness (0-255)
  int brightness = map(ldrValue, 0, 450, 0, 255);
  // Set LED brightness 
  analogWrite(ledPin, brightness);
  // Delay for 100ms
  delay(100);
}