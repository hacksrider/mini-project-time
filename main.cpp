#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
const int sw1 = D3;
const int sw2 = D4;
const int red = D5; 
const int green = D6;
const int yello = D7;

int start_stop;
int reset;
 
unsigned long prevTime = 0;
unsigned long currentTime = 0;
unsigned long passedTime = 0;      
boolean Time = false;            

void displayTime(unsigned long m, unsigned long s, unsigned long ms);
 
void setup() {
  pinMode(sw1, INPUT_PULLUP);  
  pinMode(sw2, INPUT_PULLUP);     
  pinMode(red, OUTPUT);   
  pinMode(green, OUTPUT); 
  pinMode(yello, OUTPUT);  
  digitalWrite(red, HIGH);  
  digitalWrite(green, LOW); 
  digitalWrite(yello, LOW); 
  lcd.init();                                 
  lcd.backlight();                            
  displayTime(0, 0, 0);                       
}
 
void loop() {
  start_stop = digitalRead(sw1);  
  reset = digitalRead(sw2);          

  if (start_stop == LOW) {
    Time = !Time;  
    delay(150); 
    prevTime = millis();  
     if (Time) {
      digitalWrite(red, LOW);    
      digitalWrite(green, HIGH); 
      digitalWrite(yello, LOW); 
    } else {
      digitalWrite(red, LOW);    
      digitalWrite(green, LOW);  
      digitalWrite(yello, HIGH);
    }
  }

  if (reset == LOW) {
    passedTime = 0;  
    displayTime(0, 0, 0); 
    delay(150);  
    digitalWrite(red, HIGH); 
    digitalWrite(green, LOW); 
    digitalWrite(yello, LOW);
    Time = false;
  }

  if (Time) {
    currentTime = millis();
    passedTime += currentTime - prevTime;
    prevTime = currentTime;

    unsigned long m = (passedTime / 60000) % 60;
    unsigned long s = (passedTime / 1000) % 60;   
    unsigned long ms = passedTime % 1000;  

    displayTime(m, s, ms);
  }
}

void displayTime(unsigned long m, unsigned long s, unsigned long ms) {
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  lcd.setCursor(6, 1);
  lcd.print("m");
  lcd.setCursor(10, 1);
  lcd.print("s");
  lcd.setCursor(14, 1); 
  lcd.print("ms");
  
  lcd.setCursor(5, 0);
  if (m < 10) {
    lcd.print("0");
  }
  lcd.print(m);
  lcd.print("  ");
  
  if (s < 10) {
    lcd.print("0");
  }
  lcd.print(s);
  lcd.print("  ");
  
  if (ms < 100) {
    lcd.print("0");
  }
  if (ms < 10) {
    lcd.print("0");
  }
  lcd.print(ms);
  lcd.print("                  ");
}

