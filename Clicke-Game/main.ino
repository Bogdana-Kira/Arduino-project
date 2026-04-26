const int onesPins[] = {A5, A4, 2, 3, 4, 5, 6}; // A, B, C, D, E, F, G
const int tensPins[] = {8, 7, 9, 10, 11, 12, 13};
const int buttonPin = A0;
const int buzzerPin = A2; 

int count = 0;
bool lastBtnState = LOW;

// Segment map
byte digits[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void setup() {
  for (int i = 2; i <= 13; i++) pinMode(i, OUTPUT);
  pinMode(A4, OUTPUT); 
  pinMode(A5, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void show(int number, const int pins[]) {
  byte pattern = digits[number];
  for (int i = 0; i < 7; i++) {
    digitalWrite(pins[i], bitRead(pattern, i));
  }
}

void loop() {
  // Read analog button and convert to digital state
  bool btnState = analogRead(buttonPin) > 500;
  
  if (btnState && !lastBtnState) { 
    int oldTens = count / 10; // Remember old tens
    
    count++;
    if (count > 99) count = 0;
    
    int newTens = count / 10; // Calculate new tens

    if (newTens != oldTens && count != 0) {
      // Frequency goes up: 400 + (100 * tens digit)
      int freq = 400 + (newTens * 100);
      tone(buzzerPin, freq, 200); 
    } else {
      // Normal click sound
      tone(buzzerPin, 1000, 50);
    }
    delay(150); // Debounce to prevent double counting
  }
  lastBtnState = btnState;

  show(count % 10, onesPins); 
  show(count / 10, tensPins);
}
