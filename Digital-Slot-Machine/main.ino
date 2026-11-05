
#include <Wire.h>
#include <LiquidCrystal.h>

#define BUTTON 7
#define BUZZER 8
#define ADDRESS 0x70

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int reels[4];
unsigned long totalScore = 0;

const byte digits[10] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66,
  0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

// Initialize 7-segment display
void initDisplay() {
  Wire.begin();

  byte commands[] = {0x21, 0x81, 0xEF};

  for (byte c : commands) {
    Wire.beginTransmission(ADDRESS);
    Wire.write(c);
    Wire.endTransmission();
  }
}

// Display all four reels
void showReels() {
  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);

  for (int i = 0; i < 4; i++) {
    if (i == 2) {
      Wire.write(0x00);
      Wire.write(0x00);
    }

    Wire.write(digits[reels[i]]);
    Wire.write(0x00);
  }

  Wire.endTransmission();
}

// Play a sound
void sound(int frequency, int duration) {
  tone(BUZZER, frequency, duration);
  delay(duration + 30);
}

// Spin one reel
void spinReel(int n) {
  int result = random(10);
  int steps = random(25, 36);

  for (int i = 0; i < steps; i++) {
    reels[n] = random(10);
    showReels();

    tone(BUZZER, random(700, 1600), 35);
    delay(30 + i * 5);
  }

  reels[n] = result;
  showReels();
  noTone(BUZZER);
}

// Calculate prize
int checkWin() {
  int count[10] = {0};

  for (int i = 0; i < 4; i++)
    count[reels[i]]++;

  int pairs = 0;

  for (int i = 0; i < 10; i++) {
    if (count[i] == 2) pairs++;
    if (count[i] == 3) return 250;
    if (count[i] == 4) return 1000;
  }

  if (pairs == 2) return 100;
  if (pairs == 1) return 20;

  return 0;
}

// Show result and play sound
void showResult(int prize) {
  lcd.clear();

  if (prize == 1000) {
    lcd.print("JACKPOT!");
    lcd.setCursor(0, 1);
    lcd.print("+1000 POINTS");

    sound(900, 150);
    sound(1200, 150);
    sound(1600, 150);
    sound(2000, 400);
  }
  else if (prize == 250) {
    lcd.print("BIG WIN!");
    lcd.setCursor(0, 1);
    lcd.print("+250 POINTS");

    sound(1400, 150);
    sound(1800, 300);
  }
  else if (prize == 100) {
    lcd.print("DOUBLE PAIR!");
    lcd.setCursor(0, 1);
    lcd.print("+100 POINTS");

    sound(1400, 150);
    sound(1800, 300);
  }
  else if (prize == 20) {
    lcd.print("SMALL WIN!");
    lcd.setCursor(0, 1);
    lcd.print("+20 POINTS");

    sound(1000, 150);
    sound(1300, 200);
  }
  else {
    lcd.print("NO WIN!");
    lcd.setCursor(0, 1);
    lcd.print("TRY AGAIN!");

    sound(400, 300);
  }

  totalScore += prize;
  delay(1500);

  lcd.clear();
  lcd.print("TOTAL SCORE:");
  lcd.setCursor(0, 1);
  lcd.print(totalScore);
  delay(1800);

  lcd.clear();
  lcd.print("SLOT MACHINE");
  lcd.setCursor(0, 1);
  lcd.print("PRESS START!");
}

// Start game
void playGame() {
  lcd.clear();
  lcd.print("GOOD LUCK!");
  lcd.setCursor(0, 1);
  lcd.print("SPINNING...");

  for (int i = 0; i < 4; i++)
    spinReel(i);

  noTone(BUZZER);

  showResult(checkWin());
}

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);

  lcd.begin(16, 2);
  initDisplay();

  randomSeed(analogRead(A0));

  for (int i = 0; i < 4; i++)
    reels[i] = random(10);

  showReels();

  lcd.print("SLOT MACHINE");
  lcd.setCursor(0, 1);
  lcd.print("PRESS START!");
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {
    delay(30);

    if (digitalRead(BUTTON) == LOW) {
      playGame();

      while (digitalRead(BUTTON) == LOW)
        delay(10);
    }
  }
}
