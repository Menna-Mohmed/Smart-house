// lcd
// #include <Wire.h>
 #include <LiquidCrystal_I2C.h>
 LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// DHT
#include <DHT.h>
#define DHTPIN  2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE); //Sensor initiation
#define FAN_PIN 4

//for LDR
#define LDR1 A0
#define LDR2 A1
#define LED1 3
#define LED2 5
int LDR1Value;
int LDR2Value;
float intnsty1;
float intnsty2;

//for MQ2
int Gas_Read;
#define Gas_Pin A2
#define Buzer_Pin 6

// for PIR
#define pirSensor 7
#define PIR_LED 8
byte mask=1;
//toggle
#define button 13
int val=0;
int old_val=0;
int state=0;

void setup()
{ 
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  lcd.setCursor(3, 0);
  lcd.print("welcome to");
  lcd.setCursor(3, 1);
  lcd.print("smart home");
 
  // for DHT
  dht.begin();
  pinMode(FAN_PIN, OUTPUT);

  // LDR LED  
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  Serial.begin(9600);

  // for MQ2
  pinMode(Buzer_Pin, OUTPUT);

  // for PIR
  pinMode(pirSensor, INPUT);
  pinMode(PIR_LED, OUTPUT); 
  pinMode(button,INPUT);

}
void loop()
{
  //lcd
  lcd.clear();
  // DHT
  delay(100); 
  float h = dht.readHumidity(); //measure humidity
  float t = dht.readTemperature(); //measure temperature 

  if (t >25)
  {
    digitalWrite(FAN_PIN, HIGH);
  }
  else 
  {
    delay (100);
    digitalWrite(FAN_PIN, LOW);
  }
 // LDR 
  LDR1Value = analogRead(LDR1);
  LDR2Value = analogRead(LDR2);
  Serial.print("volt1 is ");
  Serial.println(LDR1Value);
  Serial.print("volt2 is ");
  Serial.println(LDR2Value);
  intnsty1=(LDR1Value*255.0)/850.0;
  intnsty2=(LDR2Value*255.0)/850.0;
  
  if(LDR1Value >=805)
  { 
    digitalWrite(LED1,LOW);
  }

  else
  {
    analogWrite(LED1,(255.0-intnsty1));
 
  }
  if(LDR2Value >= 805)
  {
  digitalWrite(LED2,LOW);
   
  }
 else
  {
       analogWrite(LED2,(255.0-intnsty2));
  }
  val=digitalRead(button);
if( (val==HIGH) && (old_val==LOW)) {
    state=1-state;}
    old_val=val;
    delay(500);
if (state==1) {
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.setCursor(9, 0);
  lcd.print(h);
  lcd.setCursor(14, 0);
  lcd.print("%");

   lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.setCursor(12, 1);
  lcd.print(t);
  lcd.setCursor(14, 1);
  lcd.print("C "); 
 
  }
else { 

   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("intnsty1 is: ");
  lcd.setCursor(12, 0);
  lcd.print(intnsty1);
  
  lcd.setCursor(0, 1);
  lcd.print("intnsty2 is: ");
  lcd.setCursor(12, 1);
  lcd.print(intnsty2);}

  // for GAS
  Gas_Read=analogRead(Gas_Pin);
  if(Gas_Read>500)
  {
    digitalWrite(Buzer_Pin,HIGH);
  }
  else
  {
    digitalWrite(Buzer_Pin,LOW);
  }
  Serial.print("GAS is ");
  Serial.println(Gas_Read);  

  //for PIR
  int sensorValue = digitalRead(pirSensor);
  Serial.println(sensorValue);
  if (sensorValue == 1) 
  {
    if(mask==1)
    {
      Serial.println("Motion Detect.");
      mask=0;
 }
    
    digitalWrite(PIR_LED, HIGH); // The Relay Input works Inversly
    //delay(2000);
  }
  else
  {
    mask=1;
    digitalWrite(PIR_LED, LOW);
  }
}
