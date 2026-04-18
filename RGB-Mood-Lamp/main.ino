// Pair 1
int red1 = 13;
int green1 = 11;
int blue1 = 12;

// Pair 2
int red2 = 10;
int green2 = 8;
int blue2 = 9;

// Pair 3
int red3 = 7;
int green3 = 5;
int blue3 = 6;

// Pair 4
int red4 = 4;
int green4 = 2;
int blue4 = 3;

void setup() {
  // Initialize all 12 pins as outputs
  pinMode(red1, OUTPUT); pinMode(green1, OUTPUT); pinMode(blue1, OUTPUT);
  pinMode(red2, OUTPUT); pinMode(green2, OUTPUT); pinMode(blue2, OUTPUT);
  pinMode(red3, OUTPUT); pinMode(green3, OUTPUT); pinMode(blue3, OUTPUT);
  pinMode(red4, OUTPUT); pinMode(green4, OUTPUT); pinMode(blue4, OUTPUT);
}

void loop() {
  // 1. Warm and bright colors
  // P1: Orange | P2: Pink (Magenta) | P3: Turquoise | P4: Lime
  setAllColors(255, 100, 0,  255, 0, 255,  0, 255, 150,  150, 255, 0); 
  delay(1500);
  
  // 2. Deep night colors
  // P1: Purple | P2: Deep Blue | P3: Cold White | P4: Golden
  setAllColors(130, 0, 255,  0, 0, 255,  200, 255, 255,  255, 200, 0); 
  delay(1500);

  // 3. "Traffic light" effect (different for each)
  // P1: Red | P2: Yellow | P3: Green | P4: Blue
  setAllColors(255, 0, 0,  255, 255, 0,  0, 255, 0,  0, 0, 255); 
  delay(1500);
}

// Function to control all RGB LEDs at once
void setAllColors(int r1, int g1, int b1, int r2, int g2, int b2, int r3, int g3, int b3, int r4, int g4, int b4) {
  // Pair 1
  analogWrite(red1, r1);
  analogWrite(green1, g1);
  analogWrite(blue1, b1);
  
  // Pair 2
  analogWrite(red2, r2);
  analogWrite(green2, g2);
  analogWrite(blue2, b2);
  
  // Pair 3
  analogWrite(red3, r3);
  analogWrite(green3, g3);
  analogWrite(blue3, b3);
  
  // Pair 4
  analogWrite(red4, r4);
  analogWrite(green4, g4);
  analogWrite(blue4, b4);
}
