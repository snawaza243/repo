#include <LiquidCrystal_I2C.h>
#include <Wire.h>;
#include <ESP32Servo.h>


// Set up constants for pins
const int SERVO_PIN  = 2;
const int PROXIMITY_1_PIN = 14;
const int PROXIMITY_2_PIN = 15;
const int LDR_PIN = 16;
const int LED_PIN = 0;

// Set up variables for parking slots and occupancy
const int NUM_SLOTS = 5;
int slots_available = NUM_SLOTS;

// Set up objects for devices
Servo myServo;

// set the LCD number of columns and rows and define the point
int lcdColumns = 16;
int lcdRows = 2;
#define SDA 13
#define SCL 12
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);


void setup() {
  Wire.begin(SDA, SCL);
  // Initialize devices
  pinMode(PROXIMITY_1_PIN, INPUT);
  pinMode(PROXIMITY_2_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);

  // Display initial slot availability on LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Available: ");
  lcd.print(slots_available);
}

void loop() {
 // myServo.write(0);
  // Check for incoming car
  if (digitalRead(PROXIMITY_1_PIN) == HIGH) {
    // Check if there are any available slots
    if (slots_available > 0) {
      // Open barrier and decrease slot count
      myServo.write(90);
      slots_available--;
      
      // Update LCD with new slot availability
      lcd.setCursor(0, 0);
      lcd.print("Available: ");
      lcd.print(slots_available);
    }
    else {
      myServo.write(0);
      // Display "Slot Full" on LCD
      lcd.setCursor(0, 1);
      lcd.print("Slot Full");
    }
  }
  
  // Check for outgoing car
  if (digitalRead(PROXIMITY_2_PIN) == HIGH) {
    // Open barrier and increase slot count
    myServo.write(90);
    slots_available++;
    
    // Update LCD with new slot availability
    lcd.setCursor(0, 0);
    lcd.print("Available: ");
    lcd.print(slots_available);
  }
  
  // Check LDR reading and turn on LED if it is less than 500
  int ldr_reading = analogRead(LDR_PIN);
  if (ldr_reading < 500) {
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(LED_PIN, LOW);
  }
  
  // Delay to prevent rapid changes
  delay(100);
}
