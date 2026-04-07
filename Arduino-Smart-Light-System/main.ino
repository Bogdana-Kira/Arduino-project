#include <LiquidCrystal.h>

#define LDR_PIN A0
#define LED_PIN 7      

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(LED_PIN, OUTPUT);
  lcd.begin(16, 2);
  
  lcd.setCursor(0, 0);
  lcd.print(" SMART LIGHT ");
  
  lcd.setCursor(0, 1);
  lcd.print("Night Logic Set");
  delay(2000);
  lcd.clear();
}

void loop() {
  int rawLight = analogRead(LDR_PIN);  
  
  int lightPercent = map(rawLight, 0, 1023, 0, 100);
  
  lcd.setCursor(0, 0);
  lcd.print("Brightness: ");
  lcd.print(lightPercent);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  if (lightPercent < 86) { 
    digitalWrite(LED_PIN, HIGH);
    lcd.print("Status: NIGHT ON ");
  } 
  else {
    digitalWrite(LED_PIN, LOW);
    lcd.print("Status: DAY OFF  ");
  }
  delay(200); 
}
