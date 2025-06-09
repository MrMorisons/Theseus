#include <LiquidCrystal.h>
#include <string.h>

const char name[] = "Theseus";
const char head = 0b11110010;
const char tail = 0b11110110;
const int columns = 16;
const int rows = 2;
const int out_pin = 10;
const int tmp_sensor_pin = A0;
const float base_temp = 25.0;
int time = 0;
const int rs = 12,
          en = 11,
          d4 = 5,
          d5 = 4,
          d6 = 3,
          d7 = 2;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

void debout(){
  const char begen[] = " I am ";
  const char space[] = " ";
  char help[columns] = "";
  strcpy(help,begen);
  strcat(help,name);
  strcat(help,space);
  for(int i=0;i< columns/2;i++){
    delay(100);
    lcd.clear();
    lcd.setCursor(columns/2-i-1, 0);
    lcd.print(head);
    for(int j=2*i; j>0;j--){
      lcd.print(help[columns/2+i-j-1]);
    }
    lcd.print(tail);
  }
}

void tempetur_check(){
  float value = analogRead(tmp_sensor_pin);
  float volt = (value/1024.0)*5.0;
  float temp = (volt - 0.53) *100;
  Serial.print("Sensor value: ");
  lcd.print(volt);
  lcd.print(" C");
  Serial.print(volt);
}

void clock(){
  time = millis() / 1000;
  lcd.print((time / 3600));
  lcd.print(":");
  if((time / 60)%60<10){
    lcd.print(0);
  }
  lcd.print((time / 60)%60);
  lcd.print(":");
  if(time%60<10){
    lcd.print(0);
  }
  lcd.print(time%60);
}

void setup() {
  pinMode(out_pin, OUTPUT);     
  digitalWrite(out_pin, HIGH); 
  lcd.begin(columns,rows);
  Serial.begin(600);
  debout();
}

void loop() {
  lcd.setCursor(1, 1);
  tempetur_check();
  //clock();
}
