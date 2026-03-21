#include <LiquidCrystal.h>
// LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// LED
int ledR = 8;
int ledG = 9;

// Buzzer
int buzzer = 7;
  
// Gas Sensor
int sensor = A0;
int sensorThresh = 400;

void setup()
{
  Serial.begin(9600);
  pinMode (ledG, OUTPUT);
  pinMode (ledR, OUTPUT);
  pinMode (buzzer, OUTPUT);
  pinMode (sensor, INPUT);
  lcd.begin(16, 2);
}

void loop() 
{
 int sensorValue = analogRead (sensor);
 Serial.println(sensorValue);
  
 if(sensorValue > sensorThresh)
 {
   digitalWrite(ledG, LOW);
   digitalWrite(ledR, HIGH);
   tone(buzzer, 1000, 1000);
   lcd.clear();
   lcd.setCursor(4, 0);
   lcd.print("ALERT");
   delay(1000);
   lcd.clear();
   lcd.setCursor(2, 1);
   lcd.print("FIRE DETECTED");
   delay(1000);
 }
  else
 {
   digitalWrite(ledG, HIGH);
   digitalWrite(ledR, LOW);
   noTone(buzzer);
   lcd.clear();
   lcd.setCursor(3, 0);
   lcd.print("ALL CLEAR");
   delay(1000);
   lcd.clear();
   lcd.setCursor(2, 1);
   lcd.print("REST ASSURED");
   delay(1000);
  }
}
 
