// infrared tripwire
// Receiver part
#include <HijelHID_BLEKeyboard.h>   // download this library or it won't work
#define PIN_IR_IN      34   
#define PIN_LED_GREEN  16   
#define PIN_LED_RED    17   
#define PIN_BUTTON     27   
#define DEBOUNCE_MS    50

HijelHID_BLEKeyboard keyboard("IR Tripwire Receiver", "DIY");
bool lastBeamState = false;

void setGreen() {
  digitalWrite(PIN_LED_RED,   LOW);
  digitalWrite(PIN_LED_GREEN, HIGH);
}

void setRed() {
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_RED,   HIGH);
}

void ledsOff() {
  digitalWrite(PIN_LED_GREEN, LOW);
  digitalWrite(PIN_LED_RED,   LOW);
}

void goToSleep() {
  Serial.println("Going to deep sleep. Press button to wake.");
  ledsOff();
  delay(100);
  esp_sleep_enable_ext0_wakeup((gpio_num_t)PIN_BUTTON, LOW);
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_IR_IN,     INPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED,   OUTPUT);
  pinMode(PIN_BUTTON,    INPUT_PULLUP);

  ledsOff();
  setGreen(); delay(150);
  ledsOff();  delay(100);
  setGreen(); delay(150);
  ledsOff();  delay(100);
  keyboard.begin();
  delay(500);
  bool beamBroken = (digitalRead(PIN_IR_IN) == HIGH);
  lastBeamState   = beamBroken;
  beamBroken ? setRed() : setGreen();
}

void loop() {
  // Sleep button check
  if (digitalRead(PIN_BUTTON) == LOW) {
    delay(DEBOUNCE_MS);
    if (digitalRead(PIN_BUTTON) == LOW) {
      delay(200);
      goToSleep();
    }
  }

  bool beamBroken = (digitalRead(PIN_IR_IN) == HIGH);
  if (beamBroken != lastBeamState) {
    lastBeamState = beamBroken;
    if (beamBroken) {
      setRed();
      if (keyboard.isConnected()) {
        keyboard.press(KEY_TAB, KEY_MOD_LALT);
        delay(25);
        keyboard.releaseAll();
      } else {
        Serial.println("PC not connected");
      }
    } else {
      setGreen();
    }
  }
  delay(10);
}
