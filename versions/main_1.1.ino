#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h> 
 

#define ir_front 23
#define ir_back 14

#define ir_car1 19
#define ir_car2 5
#define ir_car3 18
 

Servo myservo;
int pos=0;
 
// Create the lcd object address 0x3F and 16 columns x 2 rows 
LiquidCrystal_I2C lcd (0x27, 16,2);  //

int s1=1,s2=1,s3=1;
int flag1 = 0;
int flag2 = 0;
int slot = 6;
 
void  setup () {

  Serial.begin(9600);
  pinMode(ir_car1,INPUT);
  pinMode(ir_car2,INPUT);
  pinMode(ir_car3,INPUT);

  pinMode(ir_front,INPUT);

  
  myservo.attach(13);
  myservo.write(10);

   // initialize the lcd
   lcd.init();  
  // Turn on the backlight on LCD. 
  lcd. backlight();

  Read_Sensor();
  int total = s1+s2+s3;
  slot=slot-total;
}
 
void  loop () {
  
  lcd.setCursor(0,0);
  lcd. print ( " Smart Parking " );
  lcd.setCursor(0,1);
  lcd.print("    System    ");
  delay(2000);
  lcd.clear();

  Read_Sensor();

  lcd.setCursor(0,0);
  lcd.print("Have slot: ");
  lcd.print(slot);
  delay(2000);

  if(digitalRead(ir_front)==0 && flag1 == 0){
    if(slot>0){
      flag1 = 1;
      if(flag2==0){
        myservo.write(110);
        slot = slot-1;
      }
    }
    else{
        lcd.setCursor(0,0);
        lcd.print(" Sorry Praking");
        lcd.setCursor(0,1);
        lcd.print("   Full   ");
        delay(1500);
    }
  }
  if(digitalRead(ir_back) ==0 && flag2==0){
    flag2=1;
    if(flag1==0){
      myservo.write(110);
      slot = slot+1;
    }
  }

  if(flag1==1 && flag2==1){
    
    myservo.write(10);
    flag1=0;
    flag2=0;
  }

  delay(1+);
}

void Read_Sensor(){
  s1=0 ,s2=0 ,s3=0;
  if(digitalRead(ir_car1)==0){
    s1=1;
  }
  if(digitalRead(ir_car2)==0){
    s2=1;
  }
  if(digitalRead(ir_car3)==0){
    s3=1;
  }
}