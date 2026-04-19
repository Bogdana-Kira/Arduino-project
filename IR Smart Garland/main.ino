#include <IRremote.hpp>

int leds[] = {12, 11, 10, 9, 8, 7, 6, 5, 4};
int ledCount = 0;

int blinkMode = 0;
bool blinkState = true;

unsigned long lastBlinkTime = 0;
int blinkStep = 0;

void applyLeds() {
  for (int i = 0; i < 9; i++) {
    bool shouldBeOn = (i < ledCount) && blinkState;
    digitalWrite(leds[i], shouldBeOn ? HIGH : LOW);
  }
}

void updateBlink() {
  unsigned long now = millis();

  if (blinkMode == 0) {
    blinkState = true;
    return;
  }

  if (blinkMode == 1) {
    if (now - lastBlinkTime >= 700) {
      lastBlinkTime = now;
      blinkState = !blinkState;
    }
  }

  if (blinkMode == 2) {
    if (now - lastBlinkTime >= 200) {
      lastBlinkTime = now;
      blinkState = !blinkState;
    }
  }

  if (blinkMode == 3) {
    if (blinkStep == 0 && now - lastBlinkTime >= 120) {
      lastBlinkTime = now;
      blinkState = !blinkState;
      blinkStep = 1;
    } else if (blinkStep == 1 && now - lastBlinkTime >= 120) {
      lastBlinkTime = now;
      blinkState = !blinkState;
      blinkStep = 2;
    } else if (blinkStep == 2 && now - lastBlinkTime >= 120) {
      lastBlinkTime = now;
      blinkState = !blinkState;
      blinkStep = 3;
    } else if (blinkStep == 3 && now - lastBlinkTime >= 600) {
      lastBlinkTime = now;
      blinkState = !blinkState;
      blinkStep = 0;
    }
  }
}

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(2, ENABLE_LED_FEEDBACK);

  for (int i = 0; i < 9; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {
  if (IrReceiver.decode()) {
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
      uint8_t cmd = IrReceiver.decodedIRData.command;

      Serial.print("Command: 0x");
      Serial.println(cmd, HEX);

      switch (cmd) {
        case 0x1A: ledCount = 0; break; // 0
        case 0x0C: ledCount = 1; break; // 1
        case 0x10: ledCount = 2; break; // 2
        case 0x11: ledCount = 3; break; // 3
        case 0x12: ledCount = 4; break; // 4
        case 0x14: ledCount = 5; break; // 5
        case 0x15: ledCount = 6; break; // 6
        case 0x16: ledCount = 7; break; // 7
        case 0x18: ledCount = 8; break; // 8
        case 0x19: ledCount = 9; break; // 9

        case 0x06:
          blinkMode++;
          if (blinkMode > 3) blinkMode = 0;
          blinkState = true;
          blinkStep = 0;
          lastBlinkTime = millis();
          Serial.print("Blink mode: ");
          Serial.println(blinkMode);
          break;
      }
    }

    IrReceiver.resume();
  }

  updateBlink();
  applyLeds();
}
