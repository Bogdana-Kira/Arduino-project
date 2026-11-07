/*
 (*) Used to input negative and when 
user input is not on the first value it 
acts a backspace button
(#) Used to input decimal 
(A) Next Question/ Start/ Continue
(B) Check/ submit answer
(C) Current stats
(D) Restart game
*/

#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(13, A5, A3, 12, A4, 8);

const byte ROWS = 4;
const byte COLS = 4;

char keys [ROWS] [COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'-', '0', '.', 'D'}
};

byte rowPins[ROWS] = {3, 2, 1, 0};
byte colPins[COLS] = {7, 6, 5, 4};
Keypad myKeypad = Keypad( makeKeymap(keys), rowPins, colPins,
                         ROWS, COLS );
const int buzzer = 11;
const int buzzerDur = 150;
const int buzzerDel = 50;
const int green = 9;
const int red = 10;
boolean pageOne = false;
boolean difSelect = true;
boolean timerEnd = false;
bool timeON = false;
char key;
String oper;
String UserInput;
String change;
float ans;
int randOper;
int rand1;
int rand2;
int changeInt;
int divAdjust;
int cursorPosition = -1;
int score = 0;
int total = 0;
int difChoice;
int time;
int start;
int s, s1, s10;
int current;
int timeSet;

bool ansCheck(String user, float Comp) {
  change = "";
  if (user.indexOf('-') != -1) {
    for (int i = 1; i <= user.length(); i++) {
      change = change + user[i];
    }
    changeInt = 0 - change.toInt();
    if (changeInt == Comp) {
      return true;
    } else {
      return false;
    }
  } else if ((user.toFloat()) == (Comp)) {
    return true;
  } else {
    return false;
  }
}

bool numpad() {
  if (key == '1' && pageOne || key == '2' && pageOne ||
      key == '3' && pageOne || key == '4' && pageOne ||
      key == '5' && pageOne || key == '6' && pageOne ||
      key == '7' && pageOne || key == '8' && pageOne ||
      key == '9' && pageOne || key == '0' && pageOne ||
      key == '-' && pageOne || key == '.' && pageOne
      && (UserInput.indexOf('.') == -1) || key == '1' && difSelect ||
      key == '2' && difSelect || key == '3' && difSelect) {
    return true;
  } else {
    return false;
  }
}

void keyPress() {
  if (key == '1' && difSelect) {
    difChoice = 1;
  } else if (key == '2' && difSelect) {
    difChoice = 2;
  } else if (key == '3' && difSelect) {
    difChoice = 3;
  } else if (key == '-' && (UserInput.length() > 0)) {
    UserInput.remove(UserInput.length() - 1);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(rand1);
    lcd.print(oper);
    lcd.print(rand2);
    lcd.print("=");
    cursorPosition = 10 - ((String(score)).length());
    lcd.setCursor(cursorPosition, 0);
    lcd.print("Score:");
    lcd.print(score);
    lcd.setCursor(0, 1);
    lcd.print(UserInput);
    cursorPosition = UserInput.length() - 1;
  } else if (UserInput.length() < 10) {
    cursorPosition = cursorPosition + 1;
    lcd.setCursor(cursorPosition, 2);
    lcd.print(key);
    UserInput = UserInput + key;
  }
}

void keyA() {
  pageOne = true;
  timerEnd = true;
  difSelect = false;

  randOper = random(0, 4);
  rand1 = random(0, 10);
  rand2 = random(0, 10);
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  total++;

  lcd.clear();
  if (randOper == 0) {
    oper = "+";
    ans = rand1 + rand2;
  } else if (randOper == 1) {
    oper = "-";
    ans = rand1 - rand2;
  } else if (randOper == 2) {
    oper = "*";
    ans = rand1 * rand2;
  } else if (randOper == 3) {
    if (rand2 == 3 && rand1 != rand2 && rand1 != 0 && ((rand1 % rand2) != 0) ||
        rand2 == 6 && rand1 != rand2 && rand1 != 0 && ((rand1 % rand2) != 0) ||
        rand2 == 7 && rand1 != rand2 && rand1 != 0 && ((rand1 % rand2) != 0) ||
        rand2 == 9 && rand1 != rand2 && rand1 != 0 && ((rand1 % rand2) != 0) ||
        rand2 == 0) {
      divAdjust = random(0, 5);
      if (divAdjust == 0) {
        rand2 = rand1;
      } else if (divAdjust == 1) {
        rand2 = 1;
      } else if (divAdjust == 2) {
        rand2 = 2;
      } else if (divAdjust == 3) {
        rand2 = 4;
      } else if (divAdjust == 4) {
        rand2 = 5;
      } else {
        rand2 = 8;
      }
    }
    oper = "/";
    ans = (float(rand1) / float(rand2));
  }

  cursorPosition = 10 - ((String(score)).length());
  lcd.setCursor(cursorPosition, 0);
  lcd.print("Score:");
  lcd.print(score);

  cursorPosition = 0;
  lcd.setCursor(cursorPosition, 0);
  lcd.print(rand1);
  lcd.print(oper);
  lcd.print(rand2);
  lcd.print('=');
  cursorPosition = -1;
  UserInput = "";
}

void keyB() {
  if (ansCheck(UserInput, ans)) {
    lcd.print("Nice! Click A   ");
    tone(buzzer, 440, buzzerDur);
    delay(buzzerDel);
    tone(buzzer, 550, buzzerDur);
    delay(buzzerDel);
    tone(buzzer, 660, buzzerDur);
    delay(buzzerDel);
    digitalWrite(green, HIGH);
    score++;
  } else if (!ansCheck(UserInput, ans)) {
    lcd.print("Wrong! Click A  ");
    tone(buzzer, 330, buzzerDur);
    delay(buzzerDel);
    tone(buzzer, 220, buzzerDur);
    delay(buzzerDel);
    tone(buzzer, 110, buzzerDur);
    delay(buzzerDel);
    digitalWrite(red, HIGH);
  }
  timerEnd = false;
  pageOne = false;
}

void keyC() {
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total:");
  lcd.print(total);
  lcd.setCursor(0, 1);
  lcd.print("Correct:");
  lcd.print(score);
  pageOne = false;
}

void keyD() {
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  pageOne = false;
  lcd.clear();

  lcd.print("   Welcome to   ");
  lcd.setCursor(0, 1);
  lcd.print(" Epic Math Game ");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Difficulty");
  lcd.setCursor(0, 1);
  lcd.print("1-E 2-M 3-H");
  difSelect = true;
  difChoice = 0;

  total = 0;
  score = 0;
}

void timeDone() {
  lcd.print("Out of Time! 'A'");
  tone(buzzer, 330, buzzerDur);
  delay(buzzerDel);
  tone(buzzer, 220, buzzerDur);
  delay(buzzerDel);
  tone(buzzer, 110, buzzerDur);
  delay(buzzerDel);
  digitalWrite(red, HIGH);
  timerEnd = false;
  pageOne = false;
}

void timer(bool displayTime)
{
  if (displayTime && pageOne && timerEnd) {
    time = (current - (millis() - start));
    s = (time / 1000) % 60;
    s1 = s % 10;
    s10 = (s - s1) / 10;
    lcd.setCursor(9, 1);
    lcd.print("Time:");
    lcd.print(s10);
    lcd.print(s1);
  }
}

void setup() {
  lcd.begin(16, 2);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.print("   Welcome to   ");
  lcd.setCursor(0, 1);
  lcd.print(" Epic Math Game ");
  randomSeed(analogRead(0));
  start = millis();
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Difficulty");
  lcd.setCursor(0, 1);
  lcd.print("1-E 2-M 3-H");
}

void loop() {
  timer(timeON);
  key = myKeypad.getKey();
  lcd.setCursor(0, 1);
  if (numpad()) {
    keyPress();
    if (difSelect == true) {
      if (difChoice == 1) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Easy Mode");
        lcd.setCursor(0, 1);
        lcd.print("A to Continue");
        timeON = false;
        difChoice = -1;
      } else if (difChoice == 2) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Normal Mode");
        lcd.setCursor(0, 1);
        lcd.print("A to Continue");
        timeON = true;
        timeSet = 20000;
        difChoice = -1;
      } else if (difChoice == 3) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Hard Mode");
        lcd.setCursor(0, 1);
        lcd.print("A to Continue");
        timeON = true;
        timeSet = 10000;
        difChoice = -1;
      }
    }
  }
  else if (key == 'A' && !pageOne && difChoice == -1) {
    keyA();
    current = millis() + timeSet;
  }
  else if (key == 'B' && pageOne && time > 0 && !difSelect && UserInput != ""
           || key == 'B' && pageOne && !timeON && !difSelect && UserInput != "") {
    keyB();
  }
  else if (key == 'C' && !pageOne && !difSelect) {
    keyC();
  }
  else if (key == 'D') {
    keyD();
  }
  else if (time <= 0 && pageOne && timerEnd && timeON) {
    timeDone();
  }
}
