/*
 * Project: Smart Soil Moisture Monitoring System
 * Description: Reads moisture levels from a soil sensor and visualizes 
 * the hydration status using an LED scale. Includes a blinking 
 * alert for critical low moisture using non-blocking code.
 */

int moisture = 0;                 // Variable to store soil moisture level
bool isLowMoisture = false;       // Flag to trigger the low moisture alert
unsigned long previousMillis = 0; // Stores last time the LED was updated
const long interval = 500;        // Blinking interval (milliseconds)

void setup() {
  // Sensor Power Management (A0 used to supply power only during reading)
  pinMode(A0, OUTPUT);            // Sensor VCC control
  pinMode(A1, INPUT);             // Analog input from sensor
  Serial.begin(9600);             // Initialize serial communication

  // LED Bar Configuration (Pins 8 to 12)
  pinMode(8, OUTPUT);             // Blue LED (High moisture)
  pinMode(9, OUTPUT);             // Green LED
  pinMode(10, OUTPUT);            // Yellow LED
  pinMode(11, OUTPUT);            // Orange LED
  pinMode(12, OUTPUT);            // Red LED (Critical low moisture)
}

void loop() {
  // --- Sensor Reading Process ---
  digitalWrite(A0, HIGH);         // Power up the sensor
  delay(10);                      // Short delay for sensor stabilization
  moisture = analogRead(A1);      // Read analog value (0-1023)
  digitalWrite(A0, LOW);          // Power down sensor to prevent corrosion
  
  Serial.println(moisture);       // Log value to Serial Monitor

  // Reset all LEDs before updating the status
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  // --- Logic for Moisture Levels ---
  if (moisture < 200) {
    digitalWrite(12, HIGH);       // Turn on Red LED
    isLowMoisture = true;         // Set alert flag
  } else {
    isLowMoisture = false;        // Reset alert flag
    
    // Gradual scale logic
    if (moisture < 400) {
      digitalWrite(11, HIGH);     // Orange LED
    } else if (moisture < 600) {
      digitalWrite(10, HIGH);     // Yellow LED
    } else if (moisture < 800) {
      digitalWrite(9, HIGH);      // Green LED
    } else {
      digitalWrite(8, HIGH);      // Blue LED (Optimal)
    }
  }

  // --- Non-blocking Blinking Alert ---
  // If moisture is critically low, blink the Red LED using millis()
  if (isLowMoisture) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis; // Update timestamp
      
      // Toggle LED state (If ON -> OFF, If OFF -> ON)
      if (digitalRead(12) == HIGH) {
        digitalWrite(12, LOW);
      } else {
        digitalWrite(12, HIGH);
      }
    }
  }
  
  delay(100); // Small stability delay
}
