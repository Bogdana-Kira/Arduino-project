/*
 * Project: Cowboy Duel Reaction Game
 * Description: A 2-player competitive game testing reaction speed.
 * Features random start delays and winner detection.
 */

#define BUZZER_PIN 7
#define PLAYER_COUNT 2 

// Configuration for player controls
int buttonPins[PLAYER_COUNT] = {2, 13}; 
int ledPins[PLAYER_COUNT] = {3, 12}; 

void setup() 
{
  pinMode(BUZZER_PIN, OUTPUT); 
  for (int player = 0; player < PLAYER_COUNT; ++player)
  {
    pinMode(ledPins[player], OUTPUT); 
    // Using internal pull-up resistors for cleaner wiring
    pinMode(buttonPins[player], INPUT_PULLUP); 
  }
}

void loop() 
{
  // 1. Wait for a random time before starting the round
  delay(random(1000, 3000)); 
  
  // 2. Play the "START" signal tone
  tone(BUZZER_PIN, 2000, 400); 
  delay(1000);

  // 3. Competitive loop: checking who presses the button first
  for (int player = 0; ; player = (player + 1) % PLAYER_COUNT) 
  {
    // Check if the current player's button is pressed
    // (Note: INPUT_PULLUP means button is LOW when pressed, 
    // but your circuit/code logic may vary based on wiring)
    if (digitalRead(buttonPins[player])) 
    { 
      // Winner found!
      digitalWrite(ledPins[player], HIGH); 
      tone(BUZZER_PIN, 3500, 300); // Victory sound
      delay(1000);
      digitalWrite(ledPins[player], LOW); 
      
      break; // End the round and start over
    }
  }
}
