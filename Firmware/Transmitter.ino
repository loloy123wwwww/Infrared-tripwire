// IR tripwire
// Transmitter part
#define PIN_IR_LED     25   
#define PIN_LED_GREEN  16   
#define PIN_BUTTON     27  
#define IR_FREQ_HZ     38000
#define IR_RESOLUTION  8
#define IR_DUTY_50PCT  128
#define DEBOUNCE_MS    50

void goToSleep() {
  ledcWrite(PIN_IR_LED, 0);
  ledcDetach(PIN_IR_LED);
  digitalWrite(PIN_IR_LED,    LOW);
  digitalWrite(PIN_LED_GREEN, LOW);
  delay(100);
  esp_sleep_enable_ext0_wakeup((gpio_num_t)PIN_BUTTON, LOW);
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_BUTTON,    INPUT_PULLUP);
  pinMode(PIN_IR_LED,    OUTPUT);
  ledcAttach(PIN_IR_LED, IR_FREQ_HZ, IR_RESOLUTION);
  ledcWrite(PIN_IR_LED, IR_DUTY_50PCT);
  digitalWrite(PIN_LED_GREEN, HIGH);
}
void loop() {
  if (digitalRead(PIN_BUTTON) == LOW) {
    delay(DEBOUNCE_MS);
    if (digitalRead(PIN_BUTTON) == LOW) {
      delay(200);
      goToSleep();
    }
  }
  delay(10);
}
