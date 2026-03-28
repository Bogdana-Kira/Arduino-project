
#include <LiquidCrystal.h>

// --- Game Constants ---
#define START_SPEED 150    
#define MAX_SPEED 40       
#define JUMP_LENGTH 3      
#define LEFT_LIMIT 1       
#define RIGHT_LIMIT 2      
#define GROUND 0
#define AIR 1

// --- Hardware Pins ---
#define BUTTON_JUMP 13
#define SPEAKER 6
#define RESET_PIN 7

// Musical frequencies
const float melody[] = {
  293.66, 246.94, 293.66, 196.0, 293.66, 246.94, 293.66, 196.0, 329.63, 261.63
};

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(BUTTON_JUMP, INPUT);
  pinMode(SPEAKER, OUTPUT);
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
  loadCustomSprites();
  
  // --- START SCREEN LOGIC ---
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("T-Rex Dino");
  lcd.setCursor(1, 1);
  lcd.print("Press to Start");
  
  // Чекаємо, поки користувач натисне кнопку, щоб почати
  while(digitalRead(BUTTON_JUMP) == LOW) {
    delay(10); 
  }
  
  tone(SPEAKER, 600, 100); // Звуковий сигнал старту
  lcd.clear();
  updateScore(0);
}

void loop() {
  bool playerPos;
  int targetPos1, targetPos2;
  static bool isJumping = false;
  static byte jumpStep = 0;
  static unsigned int loopCount = 0;
  static unsigned int score = 0;
  static int currentDelay = START_SPEED;

  // Плавне прискорення
  if (loopCount % 50 == 0 && currentDelay > MAX_SPEED) {
    currentDelay -= 2;
  }

  if(!isJumping) {
    tone(SPEAKER, melody[(loopCount/4) % 10]);
    isJumping = digitalRead(BUTTON_JUMP);
  }

  if(isJumping && jumpStep <= JUMP_LENGTH) {
    playerPos = AIR;
    jumpStep++;
  } else {
    playerPos = GROUND;
    jumpStep = 0;
    isJumping = false;
  }

  drawPlayer(0, playerPos);
  targetPos1 = moveObstacle1(playerPos);
  targetPos2 = moveObstacle2(playerPos);

  if(playerPos == GROUND && ((targetPos1 <= RIGHT_LIMIT && targetPos1 >= LEFT_LIMIT) || 
     (targetPos2 <= RIGHT_LIMIT && targetPos2 >= LEFT_LIMIT))) {
    triggerGameOver();
  }

  if(isJumping && ((targetPos1 <= (LEFT_LIMIT + 1) && targetPos1 >= LEFT_LIMIT) || 
     (targetPos2 < (LEFT_LIMIT + 1) && targetPos2 >= LEFT_LIMIT))) {
    score++;
    updateScore(score);
  }

  delay(currentDelay); 
  loopCount++;
}

void loadCustomSprites() {
  byte p0[8] = {0,0,0,0,4,6,7,7}; byte p1[8] = {0,0,0,0,0,0,0,17};
  byte p2[8] = {7,13,15,15,15,15,31,31}; byte p3[8] = {30,31,31,31,16,30,0,0};
  byte p4[8] = {3,1,0,0,0,0,0,0}; byte p5[8] = {31,31,31,31,15,6,2,3};
  byte p6[8] = {31,30,30,28,24,16,16,24}; byte p7[8] = {24,8,0,0,0,0,0,0};
  lcd.createChar(0, p0); lcd.createChar(1, p1); lcd.createChar(2, p2); lcd.createChar(3, p3);
  lcd.createChar(4, p4); lcd.createChar(5, p5); lcd.createChar(6, p6); lcd.createChar(7, p7);
}

void drawPlayer(byte x, bool y) {
  if(y == GROUND) {
    lcd.setCursor(x, 0); lcd.write((unsigned char)0); lcd.write(1); lcd.write(2); lcd.write(3);
    lcd.setCursor(x, 1); lcd.write(4); lcd.write(5); lcd.write(6); lcd.write(7);
  } else {
    lcd.setCursor(x, 1); lcd.print("    ");
    lcd.setCursor(x, 0); lcd.write(4); lcd.write(5); lcd.write(6); lcd.write(7);
  }
}

int moveObstacle1(bool isPlayerHigh) {
  static int x = random(15, 20);
  lcd.setCursor(x, 1);
  if(x > 3) lcd.print(" ");
  else if(x <= 3 && !isPlayerHigh) lcd.write((unsigned char)x + 4);
  if(x >= 0) { x--; lcd.setCursor(x, 1); lcd.write(221); }
  else x = random(15, 20);
  return x;
}

int moveObstacle2(bool isPlayerHigh) {
  static int x = random(25, 30);
  lcd.setCursor(x, 1);
  if(x > 3) lcd.print(" ");
  else if(x <= 3 && !isPlayerHigh) lcd.write((unsigned char)x + 4);
  if(x >= 0) { x--; lcd.setCursor(x, 1); lcd.write(243); }
  else x = random(25, 30);
  return x;
}

void updateScore(int score) {
  lcd.setCursor(6, 0); lcd.print("Score:");
  if(score < 10) lcd.print("00"); else if(score < 100) lcd.print("0");
  lcd.print(score);
}

void triggerGameOver() {
  noTone(SPEAKER);
  while(true) {
    lcd.setCursor(4, 1); lcd.print(" Game Over ");
    delay(500);
    if(digitalRead(BUTTON_JUMP)) startNewGame();
    lcd.setCursor(4, 1); lcd.print("           ");
    delay(500);
    if(digitalRead(BUTTON_JUMP)) startNewGame();
  }
}

void startNewGame() {
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, LOW);
}
