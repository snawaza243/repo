#include <LiquidCrystal_I2C.h>
#include <Wire.h>;
#include <ESP32Servo.h>

// set the LCD number of columns and rows and define the point
int lcdColumns = 16;
int lcdRows = 2;
#define I2C_SDA 15
#define I2C_SCL 14

// int ServoPin = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

Servo myservo1;

int IR1 = 12;
int IR2 = 13;
int Slot = 5;  // total number of parking slots
int flag1 = 0;
int flag2 = 0;

// int ldr = 32;
// int led = 16;

#define LIGHT_SENSOR_PIN 32  // ESP32 pin GIOP4 connected to light sensor
#define LED_PIN 16           // ESP32 pin GIOP2 connected to LED
#define ANALOG_THRESHOLD 500


void setup() {
  // initialize LCD
  Wire.begin(15, 14);
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("     TechKnight     ");
  lcd.setCursor(0, 1);
  lcd.print(" Smart Parking");
  delay(2000);
  lcd.clear();
  Serial.begin(9600);


  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  myservo1.attach(2);  // Servo moter



  pinMode(LED_PIN, OUTPUT);  // set ESP32 pin to output mode

  pinMode(LIGHT_SENSOR_PIN, INPUT);
  // pinMode(led, OUTPUT);
}

void loop() {

  int analogValue = analogRead(LIGHT_SENSOR_PIN);  // read the value on analog pin
  Serial.println(analogValue);
  delay(5000);

  if (analogValue < ANALOG_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);  // turn on LED
  } else {
    digitalWrite(LED_PIN, LOW);  // turn off LED
  }


  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo1.write(0);
        Slot = Slot - 1;
      } else {
        lcd.setCursor(0, 0);
        lcd.print("   Sorry :(  ");
        lcd.setCursor(0, 1);
        lcd.print(" Parking Full  ");
        delay(3000);
        lcd.clear();
      }
    }

    if (digitalRead(IR2) == LOW && flag2 == 0) {
      flag2 = 1;
      if (flag1 == 0) {
        myservo1.write(0);
        Slot = Slot + 1;
      }
    }

    if (flag1 == 1 && flag2 == 1) {
      delay(1000);
      myservo1.write(100);
      flag1 = 0, flag2 = 0;
    }
    lcd.setCursor(0, 0);
    lcd.print("    Welcome!    ");
    lcd.setCursor(0, 1);
    lcd.print("Slot Left: ");
    lcd.print(Slot);
  }
}
