// library for the LCD display:
#include <LiquidCrystal.h>

int ledPin = 11;               
int PIRpin = 8;            
int pirState = LOW;            
int val = 0;                    
// photocell circuit
int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider         

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);                        


void setup() {  

  pinMode(ledPin, OUTPUT);       
  pinMode(PIRpin, INPUT);     
  pinMode(photocellPin, INPUT);
  
  Serial.begin(9600);
  lcd.begin(16, 2); 
  lcd.setCursor(2, 0);                   	// Set LCD cursor position (column, row)
  lcd.print("P.I.R Motion ");               // Print text to LCD
  lcd.setCursor(0, 1);                      // Set LCD cursor position (column,row) 
  lcd.print("and Light Sensors");           // Print text to LCD
  delay(2000); // wait 2s                   // Delay to read text
                                                              
	delay(2000);                            // Delay to read text
	lcd.clear();                            // Clear LCD    
	lcd.setCursor(0, 0); 
    lcd.print("Processing Data.");
    delay(3000);
    lcd.clear(); 
	lcd.setCursor(3, 0);                 	// Set LCD cursor position (column 0, row 0)
	lcd.print("No Motion ");   
	lcd.setCursor(3, 1); 
	lcd.print("Waiting !");	
  
}

void loop(){
  val = digitalRead(PIRpin);  
  photocellReading = analogRead(photocellPin);

  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(150);

		if (pirState == LOW) {
		  Serial.println("Motion detected!");
		  lcd.clear() ;
		  lcd.setCursor(0, 0);                 // Set LCD cursor position (column 0, row 0)
		  lcd.print("Motion Detected!");   
		  lcd.setCursor(0, 1);                 // Set LCD cursor position (column 0, row 1)
		  lcd.print(photocellReading);		  
		  // We only want to print on the output change, not state
		  pirState = HIGH;
          delay(5000) ;
		}
  } else {
      digitalWrite(ledPin, LOW); // turn LED OFF
	  
	  // display no motion screen saver
	  scrollScreenSaver() ;
      if (pirState == HIGH){
		  // There's no motion !
		  // change to no motion detected
		  pirState = LOW;
      }
  }
}

void scrollScreenSaver() {
	
	lcd.clear() ;
  	lcd.setCursor(15, 0);                
	lcd.print("No Motion ");   
	lcd.setCursor(15, 1); 
	lcd.print("Waiting !");	
	
    for (int positionCounter = 0; positionCounter < 22; positionCounter++) {
		// scroll one position left:
		lcd.scrollDisplayLeft();
		// wait a bit:
		delay(150);  
	}
}
