#include <WiFi.h>
#include <WebServer.h>
#include <ESP32_Cam.h>
#include <Servo.h>

// WiFi network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Web server port
const int serverPort = 80;

// Ultrasonic sensor pins
const int trigPin1 = 4;
const int echoPin1 = 5;
const int trigPin2 = 14;
const int echoPin2 = 12;

// Proximity sensor pins
const int proxPin1 = 16;
const int proxPin2 = 17;

// LED pin
const int ledPin = 25;

// LDR pin
const int ldrPin = 34;

// Servo motor pin
const int servoPin = 13;
Servo myservo;

// Global variables
WebServer server(serverPort);
int park1 = 0;
int park2 = 0;
int maxPark = 2;
int ldrValue = 0;

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize ultrasonic sensors
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // Initialize proximity sensors
  pinMode(proxPin1, INPUT);
  pinMode(proxPin2, INPUT);

  // Initialize LED
  pinMode(ledPin, OUTPUT);

  // Initialize LDR
  pinMode(ldrPin, INPUT);

  // Initialize servo motor
  myservo.attach(servoPin);
  myservo.write(0);

  // Start web server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();

  // Read LDR value
  ldrValue = analogRead(ldrPin);
  
  // Check parking spots availability
  if (park1 < maxPark && !digitalRead(proxPin1)) {
    if (measureDistance(trigPin1, echoPin1) < 50) {
      park1++;
      Serial.println("Car parked in spot 1");
      digitalWrite(ledPin, HIGH);
      myservo.write(90);
    }
  }
  if (park2 < maxPark && !digitalRead(proxPin2)) {
    if (measureDistance(trigPin2, echoPin2) < 50) {
      park2++;
      Serial.println("Car parked in spot 2");
      digitalWrite(ledPin, HIGH);
      myservo.write(0);
    }
  }

  // Check for parked cars leaving
  if (park1 > 0 && digitalRead(proxPin1)) {
    park1--;
    Serial.println("Car left spot 1");
    digitalWrite(ledPin, LOW);
    myservo.write(0);
  }
  if (park2 > 0 && digitalRead(proxPin2)) {
    park2--;
    Serial.println("Car left spot 2");
    digitalWrite(ledPin, LOW);
    myservo.write(90);
  }
}

// Measure distance using ultrasonic sensor
float measureDistance(int trigPin, int echoPin) {
 