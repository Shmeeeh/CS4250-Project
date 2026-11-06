/**
 * Week 09 Milestone: SG2000X Single Arcade Button & LED Test
 * - Button Switch (Yellow wire) on Physical Pin 11 (INPUT_PULLUP)
 * - Button LED (Red wire) on Physical Pin 12 (OUTPUT)
 * - Onboard Blue LED on Pin 0 (OUTPUT)
 */

#include <Arduino.h>

const int BUTTON_PIN = 11;       // Header J3 Pin 11 (XGPIOB_11)
const int BUTTON_LED_PIN = 12;   // Header J3 Pin 12 (XGPIOB_19)
const int ONBOARD_LED_PIN = 0;   // Onboard Blue LED (LED_BUILTIN)

const unsigned long DEBOUNCE_MS = 10;

int stableButtonState = HIGH;    // HIGH = unpressed, LOW = pressed
int lastRawReading = HIGH;
unsigned long lastDebounceTime = 0;

void setup() {
  // Configure arcade button pin with internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Configure both the arcade button LED and onboard blue LED as outputs
  pinMode(BUTTON_LED_PIN, OUTPUT);
  pinMode(ONBOARD_LED_PIN, OUTPUT);

  // Start with both LEDs OFF
  digitalWrite(BUTTON_LED_PIN, LOW);
  digitalWrite(ONBOARD_LED_PIN, LOW);
}

void loop() {
  int currentReading = digitalRead(BUTTON_PIN);
  unsigned long now = millis();

  // Reset debounce timer if the switch state changed
  if (currentReading != lastRawReading) {
    lastDebounceTime = now;
    lastRawReading = currentReading;
  }

  // Accept the state once stable for 10ms
  if ((now - lastDebounceTime) >= DEBOUNCE_MS) {
    if (currentReading != stableButtonState) {
      stableButtonState = currentReading;

      if (stableButtonState == LOW) {
        // Button PRESSED -> Turn both LEDs ON
        digitalWrite(BUTTON_LED_PIN, HIGH);
        digitalWrite(ONBOARD_LED_PIN, HIGH);
      } else {
        // Button RELEASED -> Turn both LEDs OFF
        digitalWrite(BUTTON_LED_PIN, LOW);
        digitalWrite(ONBOARD_LED_PIN, LOW);
      }
    }
  }
}