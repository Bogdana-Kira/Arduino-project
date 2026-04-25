# 🔐 Safe Cracker: Digital Code Lock

An interactive puzzle and security simulation project. Users must guess a 4-digit secret code using hardware buttons to "crack the safe," with real-time feedback on multiple displays.

## 📌 Project Overview
"Safe Cracker" is a logic-based game where the Arduino acts as a secure vault. It features a 7-segment display for the current guess and an LCD for system status. The project demonstrates advanced techniques in state management, display multiplexing, and user interaction logic.

## ⚙️ How it Works (Logic)
1. **Secret Initialization:** A 4-digit code is hardcoded into the system (e.g., `1234`).
2. **Input System:** Four tactile buttons control the digits:
   - **Button 1:** Increments Thousands
   - **Button 2:** Increments Hundreds
   - **Button 3:** Increments Tens
   - **Button 4:** Increments Ones
3. **Dual Display Feedback:** - **7-Segment Display:** Shows the current 4-digit number being entered.
   - **16x2 LCD:** Provides instructions and the final "ACCESS GRANTED" message.
4. **Victory Condition:** Once the guess matches the secret code, the system triggers a victory melody and locks the input.

## 🛠 Technical Features
- **Library Integration:** Utilizes `Adafruit_LEDBackpack` for I2C 7-segment control and `Adafruit_LiquidCrystal`.
- **Audio Feedback:** Unique tones for button presses and a celebratory melody upon success.
- **Debounce Logic:** Software-based delays to ensure stable button inputs.
- **I2C Architecture:** Multiple devices sharing the I2C bus (LCD & 7-Segment) for efficient pin usage.

## 🔌 Components Used
- **Microcontroller:** Arduino Uno R3
- **Displays:** 1x 16x2 LCD (I2C), 1x 7-Segment Display (I2C Backpack)
- **Input:** 4x Pushbuttons
- **Sound:** 1x Piezo Buzzer
- **Protection:** 4x 10kΩ Pull-down resistors
- **Connection:** Breadboard & Jumper wires

## 🚀 Installation & Use
1. **Libraries:** Install `Adafruit LED Backpack` and `Adafruit LiquidCrystal` via Arduino Library Manager.
2. **Setup:** Connect the I2C pins (SDA/SCL) for both displays.
3. **Upload:** Flash the [main.ino](./main.ino) code.
4. **Play:** Try to guess the code to open the safe!
