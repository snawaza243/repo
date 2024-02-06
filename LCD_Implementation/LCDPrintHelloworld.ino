#include <LiquidCrystal_I2C.h>
#include <Wire.h>;

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

#define I2C_SDA 15
#define I2C_SCL 14
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

void setup(){
  // initialize LCD
  Wire.begin(15, 14);
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
}

void loop(){
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print message
  lcd.print("Hello, World!");
  delay(1000);
  // clears the display to print new message
  lcd.clear();
  // set cursor to first column, second row
  lcd.setCursor(0,1);
  lcd.print("Hello, World!");
  delay(1000);
  lcd.clear(); 
}
