// --- Hardware Mapping ---
const byte LED_PINS[] = {11, 9, 7, 5};      // Red, Green, Blue, Yellow
const byte BUTTON_PINS[] = {12, 10, 8, 6};
const int TONES[] = {220, 262, 330, 392};

#define PIN_CORRECT 4
#define PIN_WRONG   2
#define PIN_BUZZER  3

// --- Game Logic Variables ---
byte sequence[50]; 
int gameStep = 0;
int readStep = 0;
int gameSpeed = 250;
int gameStatus = 0; // 0: Reset, 1: Playback, 2: Input, 3: Game Over

void setup() {
  Serial.begin(9600);
  Serial.println("--- SIMON SAYS GAME START ---");
  
  randomSeed(analogRead(0));
  
  for (int i = 0; i < 4; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  pinMode(PIN_CORRECT, OUTPUT);
  pinMode(PIN_WRONG, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {
  if      (gameStatus == 0) prepareNewGame();
  else if (gameStatus == 1) playSequence();
  else if (gameStatus == 2) checkPlayerInput();
  else if (gameStatus == 3) handleGameOver();
}

// --- Game State Functions ---

void prepareNewGame() {
  gameStep = 0;
  readStep = 0;
  gameSpeed = 250;
  
  for (int i = 0; i < 50; i++) {
    sequence[i] = random(0, 4);
  }
  
  Serial.println("New sequence generated.");
  gameStatus = 1;
}

void playSequence() {
  Serial.print("Level: "); Serial.println(gameStep + 1);
  delay(600);
  
  for (int i = 0; i <= gameStep; i++) {
    triggerSignal(sequence[i]);
  }
  gameStatus = 2;
}

void checkPlayerInput() {
  int pressed = getPressedButton();
  if (pressed == -1) return; // Wait for interaction

  if (pressed == sequence[readStep]) {
    Serial.print("Button "); Serial.print(pressed); Serial.println(": CORRECT");
    
    digitalWrite(PIN_CORRECT, HIGH);
    triggerSignal(pressed);
    digitalWrite(PIN_CORRECT, LOW);

    if (readStep == gameStep) {
      Serial.println("Round clear! Increasing speed...");
      gameStep++;
      readStep = 0;
      if (gameSpeed > 100) gameSpeed -= 15;
      
      playLevelUpEffect();
      gameStatus = 1;
    } else {
      readStep++;
    }
  } else {
    Serial.println("WRONG button! Game Over.");
    gameStatus = 3;
  }
}

void handleGameOver() {
  Serial.print("Final Score: "); Serial.println(gameStep);
  
  digitalWrite(PIN_WRONG, HIGH);
  tone(PIN_BUZZER, 100, 600);
  
  Serial.println("Press any button to restart...");
  while (getPressedButton() == -1); 
  
  digitalWrite(PIN_WRONG, LOW);
  gameStatus = 0;
}

// --- Utility Functions ---

void triggerSignal(int id) {
  digitalWrite(LED_PINS[id], HIGH);
  tone(PIN_BUZZER, TONES[id], gameSpeed);
  delay(gameSpeed);
  digitalWrite(LED_PINS[id], LOW);
  delay(gameSpeed / 2);
}

void playLevelUpEffect() {
  for (int i = 0; i < 4; i++) digitalWrite(LED_PINS[i], HIGH);
  delay(200);
  for (int i = 0; i < 4; i++) digitalWrite(LED_PINS[i], LOW);
}

int getPressedButton() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(BUTTON_PINS[i]) == LOW) {
      delay(50);
      while (digitalRead(BUTTON_PINS[i]) == LOW); // Wait for release
      return i;
    }
  }
  return -1;
}
