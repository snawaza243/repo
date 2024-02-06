// Define the LED and LDR pins
#define LED_PIN 2
#define LDR_PIN 32

void setup() {
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read the analog value from the LDR
  int ldrValue = analogRead(LDR_PIN);

  // Map the analog value to a frequency between 0.5 and 5 Hz
  int freq = map(ldrValue, 0, 4095, 500, 5000);

  // Set the blinking frequency of the LED
  int onTime = 500;
  int offTime = freq - onTime;

  // Turn the LED on for onTime milliseconds
  digitalWrite(LED_PIN, HIGH);
  delay(onTime);

  // Turn the LED off for offTime milliseconds
  digitalWrite(LED_PIN, LOW);
  delay(offTime);
}
