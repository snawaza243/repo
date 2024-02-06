#include <LiquidCrystal_I2C.h>
#define SDA 15
#define SCL 14
#define COLUMNS 16
#define ROWS    2

LiquidCrystal_I2C lcd(0x38, COLUMNS, ROWS);  

void setup(){

  Wire.begin(SDA, SCL);
  lcd.init();   
  lcd.clear();           
  lcd.backlight();                      
  
  lcd.setCursor(0,0);
  lcd.print(" HELLO ESP32-CAM I2C ");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print(" LCD I2C Module ");
  delay(8000);

}

void loop(){

}