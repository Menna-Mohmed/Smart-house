#include <Servo.h>

#include <LiquidCrystal_I2C.h>

#include <Keypad.h>

const byte ROWS = 4;

const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
int password=1234;
int attempt=0;
int counter=3;
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal_I2C lcd(0x27,16,2); 
int cursorColumn = 0;
Servo servo;
int angle=10;
void setup(){
  Serial.begin(9600);
  lcd.backlight();
  lcd.init();
  servo.attach(10);
  servo.write(angle);
}
  
void loop(){
  char customKey = customKeypad.getKey();
 if (customKey) {
    lcd.setCursor(cursorColumn, 0);
    lcd.print(customKey);                 

    cursorColumn++;                
    if(cursorColumn == 16) {       
      lcd.clear();
      cursorColumn = 0;
    }
  }
  
  if (customKey){
    Serial.println(customKey);
    customKey-=48;
  attempt+=customKey*pow(10,counter); 
    Serial.println(attempt);
    counter-=1;
    if(counter <0 ){
      counter=3;
      if(attempt == password){
        lcd.setCursor(cursorColumn, 1);
        lcd.print("Open");                 
        Serial.println("Open");
        attempt=1;
        delay(2000);
        lcd.clear();
        cursorColumn = 0;
        servo.write(100);
        delay(10000);
        servo.write(10);
      }
      else{
      Serial.println("Wrong");
        lcd.setCursor(cursorColumn, 1);
        lcd.print("Wrong");
        attempt=1;
        delay(2000);
        lcd.clear();
        cursorColumn = 0;
        
      }
    }
  }
}
