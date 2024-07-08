#include<LiquidCrystal.h>
#define echo D34
#define trig D35
#define RS   D32  
#define EN   D33
#define D4   D25
#define D5   D26
#define D6   D27
#define D7   D14
#define IN2  D19
#define IN1  D18
#define ENB  D21
#define Sspeed 0.34
float distance=0;
float t =0;

void setup()
{
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENB,INPUT);
  pinMode(led4,OUTPUT);
}

void loop()
{
digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);
t=pulseIn(echo,HIGH);
t/=1000;
distance = t*Sspeed/2;
Serial.println(distance);
delay(1000);

}
