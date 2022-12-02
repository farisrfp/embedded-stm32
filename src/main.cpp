#define DS1307_I2C_ADDRESS 0x68

#include "Arduino.h"
#include "Wire.h"

typedef struct DateTime {
  // byte = uint8_t
  byte second;
  byte minute;
  byte hour;
  byte dayOfWeek;
  byte dayOfMonth;
  byte month;
  byte year;
} DateTime_t;
  

/* Include the following functions in your sketch */
#include "Function.h"

void setup()
{
  /* Initialize serial communication and wait for port to open: */
  Wire.begin();         // Join I2C Bus (address optional for master)
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(1000);          // Wait for 1 second
}

void loop()
{
  /* Initialize local variables */
  DateTime_t waktu;
  bool err;
  
  /* Read */
  err = getDateTime(&waktu);

  /* Debug  */

  /* Output */
  Serial.println("Hello World!");
  Serial.println(waktu.second);
}