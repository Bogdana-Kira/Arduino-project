#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

#define buzzer 2
#define redLed 8
#define yellowLed 7
#define greenLed 6
#define forceSensor A0

Adafruit_LiquidCrystal lcd(0);

int sensorValue = 0;
int frequency = 1000;

void setup() {
  pinMode(forceSensor, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("System start");
  delay(1000);
  lcd.clear();
}

void loop() {
  sensorValue = analogRead(forceSensor);

  lcd.setCursor(0, 0);
  lcd.print("Force: ");
  lcd.print(sensorValue);
  lcd.print("    ");

  if (sensorValue > 1 && sensorValue <= 250) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    noTone(buzzer);

    lcd.setCursor(0, 1);
    lcd.print("Status: NORMAL ");
  }
  else if (sensorValue > 250 && sensorValue <= 370) {
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
    noTone(buzzer);

    lcd.setCursor(0, 1);
    lcd.print("Status: MEDIUM ");
  }
  else if (sensorValue > 370) {
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, HIGH);
    tone(buzzer, frequency);

    lcd.setCursor(0, 1);
    lcd.print("Status: OVERLOAD");
  }
  else {
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
    noTone(buzzer);

    lcd.setCursor(0, 1);
    lcd.print("Status: NO LOAD ");
  }

  delay(100);
}
