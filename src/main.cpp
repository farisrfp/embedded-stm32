#include <Arduino.h>
#include <HardwareSerial.h>

int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // put your setup code here, to run once:
  pinMode(PC13, OUTPUT);
  Serial.begin(9600);
  // pinMode(PA0, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Halo");
  digitalWrite(PC13, LOW);
  delay(1000);
  digitalWrite(PC13, HIGH);
  delay(1000);
}