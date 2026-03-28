#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect to the row and column pinouts of the keypad
byte rowPins[ROWS] = {A0, A1, A2, A3}; 
byte colPins[COLS] = {A4, A5, 1, 0}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String text="";
int ctr=1;
int num1,num2,ans;
bool reset=false;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Enter 1st No.");  
  lcd.blink();
  lcd.setCursor(0,1);
}

void loop() {
  char key = keypad.getKey();
  
  if (key != NO_KEY)
  {
    // Allow digits 0 to 9 only
    if (key<='9' && key>='0' && reset==false)
    {
       text=text+key;
       lcd.print(key);
    } 
    
    if (key=='#') // Enter Key
    {
      switch(ctr)
      {
         case 1: 
           num1=text.toInt(); // convert text to integer
           ctr++;
           text="";
           lcd.clear();
           lcd.print("Enter 2nd No.");
           lcd.setCursor(0,1);
           lcd.blink(); 
           break;
         case 2: 
           num2=text.toInt(); // convert text to integer
           ctr++;
           text="";
           lcd.clear();
           lcd.print("CHOOSE OPERATION");
           lcd.setCursor(0,1);
           lcd.print("A=+ B=- C=* D=/");
           lcd.setCursor(0,2);
           lcd.blink(); 
           break;
      } 
    } 

    if(key == 'A')
    {
      ans=num1+num2;
      displayResult('+', ans);
    }

    if(key == 'B')
    {
      ans=num1-num2;
      displayResult('-', ans);
    }

    if(key == 'C')
    {
      ans=num1*num2;
      displayResult('*', ans);
    }

    if(key == 'D')
    {
      ans=num1/num2;
      displayResult('/', ans);
    }
    
    if (key=='*') // Reset Key
    {
      text="";
      ctr=1;
      num1=0;
      num2=0;
      ans=0;
      reset=false;
      lcd.clear();
      lcd.print("Enter 1st No.");
      lcd.blink();
      lcd.setCursor(0,1);
    }
  }
}

// Function to handle result display logic
void displayResult(char op, int result) {
  text="";
  text=text+num1+op+num2+"="; 
  ctr++;
  reset=true;
  lcd.clear();
  lcd.print(text);
  lcd.print(result); 
  lcd.noBlink();
  lcd.setCursor(0,1);
  lcd.print("Press * to reset");
}
