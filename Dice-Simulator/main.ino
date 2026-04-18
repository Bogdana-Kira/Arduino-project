int randomNumber = 0;

void setup() {
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  if (digitalRead(7) == HIGH) {
    randomNumber = random(1, 6 + 1);

    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(13, LOW);
    digitalWrite(9, LOW);
    digitalWrite(12, LOW);

    if (randomNumber == 1) {
      digitalWrite(8, HIGH);
    } else if (randomNumber == 2) {
      digitalWrite(8, HIGH);
      digitalWrite(13, HIGH);
    } else if (randomNumber == 3) {
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, HIGH);
    } else if (randomNumber == 4) {
      digitalWrite(8, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(13, HIGH);
    } else if (randomNumber == 5) {
      digitalWrite(8, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(9, HIGH);
    } else if (randomNumber == 6) {
      digitalWrite(8, HIGH);
      digitalWrite(10, HIGH);
      digitalWrite(11, HIGH);
      digitalWrite(13, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(12, HIGH);
    }

    delay(1000);

    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
    digitalWrite(13, LOW);
    digitalWrite(9, LOW);
    digitalWrite(12, LOW);
  }
}
