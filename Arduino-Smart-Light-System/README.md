# 💡 Smart Light System with LCD

An automated lighting solution that adjusts and monitors ambient light levels using an LDR sensor and displays real-time data on an LCD screen.

## 📌 Project Overview
This project simulates a smart home lighting controller. It detects the brightness of the environment; if it gets too dark, the system automatically turns on the light (LED) and updates the status and brightness percentage on the 16x2 LCD display.

## ⚙️ How it Works (Game Logic)
1. **Light Sensing:** The Photoresistor (LDR) reads analog light levels from the environment.
2. **Data Processing:** The Arduino converts the analog signal into a percentage (0% to 100%) for readability.
3. **Automation:** - If light levels drop below a 30% threshold, the system triggers the LED **ON**.
   - If ambient light is sufficient, the LED stays **OFF** to save energy.
4. **Monitoring:** The LCD display shows the current "Light Level" and the system "Status" (Day/Night) in real-time.

## 🛠 Technical Features
- **Analog-to-Digital Mapping:** Uses the `map()` function to convert raw sensor data (0-1023) into a user-friendly percentage (0-100%).
- **Automated Thresholding:** Implements conditional logic to act as a standalone light controller.
- **Visual Interface:** Real-time data visualization on a character LCD using the LiquidCrystal library.

## 🔌 Components Used
- **Microcontroller:** Arduino Uno R3
- **Sensor:** Photoresistor (LDR)
- **Visual Output:** 16x2 LCD Display & Blue LED
- **Input/Control:** Potentiometer (for LCD contrast)
- **Others:** 220Ω Resistor, 10kΩ Resistor, Breadboard, and Jumper wires.

## 📐 Circuit Diagram
![Smart Light Schematic](Smart-Light-System.png)
*Designed and simulated in Tinkercad.*

## 🚀 Installation & Use
1. **Get the Code:** Open the [main.ino](./main.ino) file and copy the source code.
2. **Setup:** Paste the code into your Arduino IDE or a new Tinkercad "Code" block.
3. **Hardware:** Connect the LCD and LDR sensor according to the pins defined in the `main.ino` header.
4. **Testing:** Simulate changing light conditions to see the LED and LCD respond automatically.

## 📺 Video Demonstration
[![Watch the video](https://img.youtube.com/vi/pYPe7i0znh8/0.jpg)](https://youtu.be/pYPe7i0znh8)

## 🔗 Interactive Simulation
[![Tinkercad Simulation](https://img.shields.io/badge/Tinkercad-Simulation-orange?style=for-the-badge&logo=autodesk)](https://www.tinkercad.com/things/lp4HFf6LK0Z-smart-light-system)
