// #include <ESP32Servo.h>
// Servo myservo;  // crte servo object to control a servo
// Define LDR pin and LED pin
 int ldrPin = 12;
 int  ledPin = 13;

void setup() {
  // myservo.attach(2);  // attaches the servo on GPIO pin 2 to the servo object

  // Set LED pin as output
  pinMode(ledPin, OUTPUT);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // myservo.write(90);  // sets the servo position to 90 degrees
  // delay(1000);        // waits for 1 second
  // myservo.write(0);   // sets the servo position to 0 degrees
  // delay(1000);        // waits for 1 second

  int x = analogRead(ldrPin);
  Serial.println(x);
  delay(1000);

  if (x >=450) {
    digitalWrite(ledPin, 0);
  } else {
    digitalWrite(ledPin, 1);
  }
}