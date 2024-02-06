#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  //Change the HEX address
#include <ESP32Servo.h>
Servo myservo1;

int ServoPin = 2;

int IR1 = 12;
int IR2 = 13;
int Slot = 5;  // total number of parking slots
int flag1 = 0;
int flag2 = 0;

#define I2C_SDA 15
#define I2C_SCL 14

void setup() {
  lcd.begin(15, 14);
  lcd.backlight();
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  myservo1.attach(ServoPin);
  // myservo1.write(0);

  lcd.setCursor(0, 0);
  lcd.print("  TechKnight   ");
  lcd.setCursor(0, 1);
  lcd.print("SMART PARKING");
  delay(2000);
  lcd.clear();
}

void loop() {
  if (digitalRead(IR1) == HIGH && flag1 == 0) {
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

    if (digitalRead(IR2) == HIGH && flag2 == 0) {
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
    lcd.print("   Welcome!    ");
    lcd.setCursor(0, 1);
    lcd.print("Slot Left: ");
    lcd.print(Slot);
  }
}
