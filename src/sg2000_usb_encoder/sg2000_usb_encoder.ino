// Draft SG2000X Arcade Encoder Sketch
const int NUM_BUTTONS = 12;
const int buttonPins[NUM_BUTTONS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int lastButtonState[NUM_BUTTONS];

void setup() {
  Serial.begin(115200);

  // Set all arcade switch pins to use internal pull-up resistors
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
    lastButtonState[i] = HIGH;
  }
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    int reading = digitalRead(buttonPins[i]);

    // If the switch state changed, send an update to the Raspberry Pi
    if (reading != lastButtonState[i]) {
      if (reading == LOW) {
        Serial.print("PRESS:");
        Serial.println(i);
      } else {
        Serial.print("RELEASE:");
        Serial.println(i);
      }
      lastButtonState[i] = reading;
    }
  }
  delay(5); // Simple 5ms debounce delay
}
