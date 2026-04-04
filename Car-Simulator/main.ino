// --- Pin Definitions ---
const int TRIG_PIN = 7;
const int ECHO_PIN = 2;

// Motor Pins (L293D Driver)
const int ENABLE_PIN = 13; // Bridge activation
const int MOTOR_L_FWD = 11; // Left Motor Forward
const int MOTOR_L_REV = 9;  // Left Motor Reverse
const int MOTOR_R_FWD = 5;  // Right Motor Forward
const int MOTOR_R_REV = 3;  // Right Motor Reverse

// Parameters
const int DISTANCE_THRESHOLD = 30; // Distance in cm to trigger avoidance

void setup() {
  Serial.begin(115200);

  // Setup Motor Pins
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(MOTOR_L_FWD, OUTPUT);
  pinMode(MOTOR_L_REV, OUTPUT);
  pinMode(MOTOR_R_FWD, OUTPUT);
  pinMode(MOTOR_R_REV, OUTPUT);

  digitalWrite(ENABLE_PIN, HIGH); // Enable the motor driver

  // Setup Ultrasonic Sensor Pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  
  Serial.println("Robot Initialized...");
}

void loop() {
  int currentDistance = getDistance();

  if (currentDistance > 0 && currentDistance < DISTANCE_THRESHOLD) {
    // OBSTACLE DETECTED
    Serial.print("Obstacle at: ");
    Serial.println(currentDistance);
    
    avoidObstacle();
  } else {
    // PATH IS CLEAR
    moveForward();
  }
  
  delay(50); // Small stability delay
}

// --- Movement Functions ---

void moveForward() {
  digitalWrite(MOTOR_L_FWD, HIGH);
  digitalWrite(MOTOR_L_REV, LOW);
  digitalWrite(MOTOR_R_FWD, HIGH);
  digitalWrite(MOTOR_R_REV, LOW);
}

void moveBackward(int duration) {
  digitalWrite(MOTOR_L_FWD, LOW);
  digitalWrite(MOTOR_L_REV, HIGH);
  digitalWrite(MOTOR_R_FWD, LOW);
  digitalWrite(MOTOR_R_REV, HIGH);
  delay(duration);
}

void turnRight(int duration) {
  digitalWrite(MOTOR_L_FWD, HIGH);
  digitalWrite(MOTOR_L_REV, LOW);
  digitalWrite(MOTOR_R_FWD, LOW);
  digitalWrite(MOTOR_R_REV, HIGH); // Counter-rotation for sharper turn
  delay(duration);
}

void stopRobot(int duration) {
  digitalWrite(MOTOR_L_FWD, LOW);
  digitalWrite(MOTOR_L_REV, LOW);
  digitalWrite(MOTOR_R_FWD, LOW);
  digitalWrite(MOTOR_R_REV, LOW);
  delay(duration);
}

// --- Logic Functions ---

void avoidObstacle() {
  stopRobot(500);
  moveBackward(800);
  stopRobot(200);
  
  // Turn to find a new path
  turnRight(600); 
  stopRobot(200);
}

int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the bounce back time
  long duration = pulseIn(ECHO_PIN, HIGH, 30000); 
  
  if (duration == 0) return 400; // No obstacle in range
  return duration / 58; // Convert to cm
}
