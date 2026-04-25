#include <Adafruit_LiquidCrystal.h>
#include <Adafruit_LEDBackpack.h>

// Initialize displays
Adafruit_LiquidCrystal lcd(0);
Adafruit_7segment matrix = Adafruit_7segment();

const int buzzer = 7;
int secret, guess = 0;
bool win = false;

void setup() {
  // Set buttons (Pins 2-5) and Buzzer (Pin 7)
  for (int i = 2; i <= 5; i++) {
    pinMode(i, INPUT);
  }
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  matrix.begin(0x70);
  
  secret = 1234; // Set your secret code here
  lcd.print("GUESS THE CODE!");
}

void loop() {
  if (win) return;

  // Buttons with audio feedback (short beep)
  if (digitalRead(2)) { buttonAction(1000); } // Thousands
  if (digitalRead(3)) { buttonAction(100);  } // Hundreds
  if (digitalRead(4)) { buttonAction(10);   } // Tens
  if (digitalRead(5)) { buttonAction(1);    } // Ones

  // Reset if guess exceeds 9999
  if (guess > 9999) guess = 0;

  // Update 7-segment display
  matrix.print(guess, DEC);
  matrix.writeDisplay();

  // Check if the guess matches the secret code
  if (guess == secret) {
    victoryTune();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("ACCESS GRANTED!");
    lcd.setCursor(0, 1);
    lcd.print("SAFE OPENED");
    win = true;
  }
}

// Function to handle button presses (sound + increment)
void buttonAction(int value) {
  guess += value;
  tone(buzzer, 1500, 50); // High pitch beep (1500 Hz) for 50ms
  delay(250); // Debounce delay
}

// Simple victory melody
void victoryTune() {
  tone(buzzer, 1000, 200); delay(200);
  tone(buzzer, 1200, 200); delay(200);
  tone(buzzer, 1500, 400); delay(400);
}
