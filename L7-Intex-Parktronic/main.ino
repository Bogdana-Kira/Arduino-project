#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>

// Pin definitions for RGB LED
const int RED_PIN = 13;
const int GREEN_PIN = 6;
const int BLUE_PIN = 7;
int DISPLAY_TIME = 100; 

long cm; // Variable to store distance in centimeters

// Initialize LCD display with interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Function to calculate distance using Ultrasonic Sensor
long Distance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);      // Set trigger pin as output
  digitalWrite(triggerPin, LOW);    // Ensure trigger is low
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);   // Send 10us pulse to trigger
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);          // Set echo pin as input
  return pulseIn(echoPin, HIGH);    // Measure the duration of the incoming pulse
}

void setup()
{ 
  lcd.begin(16, 2);                 // Initialize 16x2 LCD
  
  // Set pin modes for buzzer and LEDs
  pinMode(9, OUTPUT);               // Buzzer pin
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600);               // Start serial communication for debugging
}

void loop()
{
  // Reset all LEDs at the start of each loop
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  // Calculate distance: 0.01723 is a coefficient to convert pulse time to cm
  cm = 0.01723 * Distance(10, 10);

  // Case 1: Safe distance (More than 150 cm)
  if (cm > 150) {
    lcd.clear();
    digitalWrite(GREEN_PIN, HIGH);  // Solid Green light
    delay(1000);
  }
  
  // Case 2: Warning distance (80 cm to 150 cm)
  if (cm <= 150 && cm > 80) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("D:");
    lcd.print(cm);
    lcd.print("cm");
    tone(9, 294, 800);              // Slow beep
    digitalWrite(GREEN_PIN, HIGH);  // Green flashing
    delay(600); 
    digitalWrite(GREEN_PIN, LOW);
    delay(600);
  }
  
  // Case 3: Caution (25 cm to 80 cm)
  if (cm <= 80 && cm > 25) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("D:");
    lcd.print(cm);
    lcd.print("cm");
    tone(9, 294, 400);              // Faster beep
    digitalWrite(RED_PIN, HIGH);    // Yellow (Red+Green) light
    digitalWrite(GREEN_PIN, HIGH);
    delay(500);
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    delay(500);
  }
  
  // Case 4: Danger zone - STOP (8 cm to 25 cm)
  if (cm <= 25 && cm > 8) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("STOP!");
    lcd.setCursor(0, 1);
    lcd.print("D:");
    lcd.print(cm);
    lcd.print("cm");
    tone(9, 294, 200);              // Rapid beep
    digitalWrite(RED_PIN, HIGH);    // Red flashing
    delay(300); 
    digitalWrite(RED_PIN, LOW);
    delay(300);
  }
  
  // Case 5: Critical distance (Less than 8 cm)
  if (cm <= 8) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Critical dist!");
    lcd.setCursor(0, 1);
    lcd.print("D:");
    lcd.print(cm);
    lcd.print("cm");
    tone(9, 294, 150);              // Very fast beep
    digitalWrite(RED_PIN, HIGH);    // Intense Red flashing
    delay(200);
    digitalWrite(RED_PIN, LOW);
    delay(200);
  }
}
