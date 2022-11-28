#include <Arduino.h>

/* Pin Def */
const byte potMeter   = PB0;
const byte ledPin     = PA1;

/* Global Var */
static int buttonState   = 0;
static int potAnalog     = 0;
static unsigned long lastDebugSerial = 0;
static unsigned long currentMillis = 0;

void ledFading(byte led_pin) {
  /* Global Var */
  static int8_t fadeAmount = 1;
  static uint8_t ledBrightness = 0;
  static unsigned long lastLedFading = 0;

  /* Fading */
  if (currentMillis - lastLedFading >= 5) {
    lastLedFading = currentMillis;
    ledBrightness += fadeAmount;
    if (ledBrightness == 0 || ledBrightness == 255) {
      fadeAmount = -fadeAmount;
    }
  }
  analogWrite(led_pin, ledBrightness);
}

void setup() {
  Serial.begin(115200);
  delay(500); // Wait for Serial Monitor

  /* PinMode */
  pinMode(USER_BTN, INPUT_PULLUP);
  pinMode(potMeter, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  /* Read */
  potAnalog     = analogRead(potMeter);
  buttonState   = digitalRead(USER_BTN);
  currentMillis = millis();

  int potVoltage = map(potAnalog, 0, 1023, 0, 500);

  /* Debug */
  
  if (currentMillis - lastDebugSerial > 200) {
    lastDebugSerial = millis();
    
    float potVoltage_f = potVoltage / 100.00;
    
    Serial.print("ADC Reading: ");Serial.print(potAnalog);
    Serial.print(" | Voltage: ");Serial.println(potVoltage_f);
  }

  /* Write */

  if (potVoltage > 200) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (buttonState == LOW) {
    ledFading(ledPin);
  } else {
    analogWrite(ledPin, 0);
  }
}