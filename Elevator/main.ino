#include <Keypad.h>

const byte rows = 4; // Rows
const byte cols = 4; // Columns

char keys[rows][cols] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[rows] = {0, 2, 3, 4};//Keypad rows connected to arduino pins
byte colPins[cols] = {5, 6, 7, 8};//Keypad columns connected to arduino pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins,
                       rows, cols);

const int dataPin = 9;
const int latchPin = 10;
const int clockPin = 11;

int dataArray[10] = {0B11111100, 0B01100000, 0B11011010,
                     0B11110010, 0B01100110, 0B10110110,
                     0B10111110, 0B11100000, 0B11111110,
                     0B11110110};

int letterArray[4] = {0B11101110, 0B00111110, 0B10011100,
                      0B01111010};

const int motorPin1 = 12;
const int motorPin2 = 13;
int lastNumber = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  
  Serial.begin(9600);
}

void loop() 
{
  char keypressed = keypad.getKey();
  int keycode = 0;
  
  if (keypressed) {
    Serial.println(keypressed);
    String KeyNumber = String(keypressed);
    
    if (isalpha(keypressed)) {
      int index = char(keypressed) - 65;
      keycode = letterArray[index];
    } else {
      int index = KeyNumber.toInt();
      keycode = dataArray[index];
    }
    
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, keycode);
    digitalWrite(latchPin, HIGH);
    
    // motor will work if there is a pressed number
    if (!isalpha(keypressed)) {
      int currentNumber = KeyNumber.toInt();//convertion
      
      if (currentNumber > lastNumber) {
        //rotate in clockwise
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);
        delay(1000 * (currentNumber - lastNumber)); //delay
      } else {
        //rotate in counterclockwise
        digitalWrite(motorPin1, HIGH);
        digitalWrite(motorPin2, LOW);
        delay(1000 * (lastNumber - currentNumber)); //delay
      }
      
      // motor will stop
      digitalWrite(motorPin1, LOW);
      digitalWrite(motorPin2, LOW);
      lastNumber = currentNumber; //last pressed number will be displayed
    }
  }
}
