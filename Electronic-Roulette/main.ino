#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define BUTTON 7
#define BUZZER 8
#define NUMPIXELS 24

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.setBrightness(255);
  pixels.show();

  lcd.begin(16, 2);
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  randomSeed(analogRead(A0));

  lcd.print("ELECTRONIC");
  lcd.setCursor(0, 1);
  lcd.print("ROULETTE 1-24");
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    delay(30);
    if (digitalRead(BUTTON) == LOW) {
      spinRoulette();
      while (digitalRead(BUTTON) == LOW) delay(10);
    }
  }
}

void spinRoulette() {
  int pos = random(NUMPIXELS);
  int steps = random(60, 81);

  lcd.clear();
  lcd.print("ROULETTE");
  lcd.setCursor(0, 1);
  lcd.print("SPINNING...");

  for (int i = 0; i < steps; i++) {
    pixels.clear();
    pixels.setPixelColor(pos,
      pixels.gamma32(pixels.ColorHSV(random(65536), 255, 255)));
    pixels.show();

    tone(BUZZER, random(500, 2000), 30);
    delay(80 + i * i / 15);

    if (i < steps - 1)
      pos = (pos + 1) % NUMPIXELS;
  }

  noTone(BUZZER);

  int result = pos + 1;

  pixels.clear();
  pixels.setPixelColor(pos, pixels.Color(0, 255, 0));
  pixels.show();

  lcd.clear();
  lcd.print("WINNING NUMBER:");
  lcd.setCursor(0, 1);
  if (result < 10) lcd.print("0");
  lcd.print(result);

  tone(BUZZER, 1000, 200);
  delay(250);
  tone(BUZZER, 1500, 300);
  delay(350);
  noTone(BUZZER);
}
