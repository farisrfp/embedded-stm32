#include <Arduino.h>

/* Pin Def */
const byte potMeter   = PB1;
const byte ledPin     = PA1;

/* Global Var */
static uint16_t potValue = 0;
static bool buttonState = false;
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
  int16_t potAnalog   = analogRead(potMeter);
  int8_t  buttonState = digitalRead(USER_BTN);
  currentMillis = millis();

  int potVoltage = map(potAnalog, 0, 1023, 0, 500);

  /* Debug */
  
  if (currentMillis - lastDebugSerial > 200) {
    lastDebugSerial = millis();
    
    float potVoltage_f = potVoltage / 100.0;

    char str[100];
    sprintf(str, "ADC Reading: %d || Voltage: %f", potAnalog, potVoltage_f);
    Serial.println(str);
  }

  /* Write */

  if (potVoltage > 200) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
  if (!buttonState) {
    ledFading(ledPin);
  } else {
    digitalWrite(ledPin, LOW);
  }
}