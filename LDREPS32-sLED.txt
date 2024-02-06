const int ldrPin = 34; // LDR pin connected to ESP32-S pin 34
const int ledPin = 32; // LED pin connected to ESP32-S pin 32

void setup() {
  pinMode(ldrPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int ldrValue = analogRead(ldrPin); // Read LDR value
  int ledValue = map(ldrValue, 0, 4095, 0, 255); // Map LDR value to LED brightness range
  analogWrite(ledPin, ledValue); // Set LED brightness
  delay(10); // Delay for stability
}