#include "Arduino.h"
#include "RTClib.h"

#ifndef USR_BUTTON
  #define USR_BUTTON 0
#endif
const int POT_PIN = A0;

RTC_DS1307 rtc;
  
const int intervalDebug[3] = {1000, 5000, 10000};

void setup()
{
  /* Initialize serial communication and wait for port to open: */
  Serial.begin(115200); // Start the Serial communication to send messages to the computer

  /* PinMode */
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(USR_BUTTON, INPUT_PULLUP);
  pinMode(POT_PIN, INPUT);

  /* RTC setup */
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop()
{
  /* Initialize global variables */
  static int buttonState, potADC, potValue;
  static int index_interval = 0;
  static unsigned long lastDebugMillis = 0;

  /* Read */
  potADC = analogRead(POT_PIN);
  buttonState = digitalRead(USR_BUTTON);
  DateTime now = rtc.now();

  /* Logic */
  if (!buttonState) {
    index_interval = (index_interval + 1) % 3;
  }
  potValue = map(potADC, 0, 1023, 0, 500);
  
  /* Output */
  if (millis() - lastDebugMillis > intervalDebug[index_interval]) {
    lastDebugMillis = millis();
    // Debug
    float potVoltage_f = potValue / 100.00;
    char buffer[50];
    sprintf(buffer, "Potentiometer: %.2fV", potVoltage_f);
    Serial.print(buffer);
    sprintf(buffer, " - Time: %02d/%02d/%04d %02d:%02d:%02d", now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());
    Serial.println(buffer);    
    // LED Blink
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(200);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}