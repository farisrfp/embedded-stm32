#include "Arduino.h"
#include "RTClib.h"

#ifndef USR_BUTTON
  #define USR_BUTTON 0
#endif
const int POT_PIN = A0;

RTC_DS1307 rtc;
  
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
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
  static int buttonState, potADC, potValue, index_interval;
  static unsigned long lastDebugMillis = 0;

  /* Read */
  potADC = analogRead(POT_PIN);
  buttonState = digitalRead(USR_BUTTON);

  /* Logic */
  if (!buttonState) {
    index_interval = (index_interval + 1) % 3;
  }
  potValue = map(potADC, 0, 1023, 0, 500);
  
  /* Output */
  if (millis() - lastDebugMillis > intervalDebug[index_interval]) {
    lastDebugMillis = millis();
    // LED Blink
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    // Debug
    Serial.println(potValue);
  }
}