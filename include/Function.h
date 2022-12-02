/* Convert normal decimal numbers to binary coded decimal */
uint8_t decToBcd(uint8_t val)
{
  return (uint8_t)(((val / 10) << 4) | (val % 10));
}

/* Convert binary coded decimal to normal decimal numbers */ 
uint8_t bcdToDec(uint8_t val)
{
  return (uint8_t)(10 * ((val & 0xF0) >> 4) + (val & 0x0F));
}

bool getDateTime(DateTime_t *dt)
{
    Wire.beginTransmission(DS1307_I2C_ADDRESS);
    Wire.write(0x00);
    Wire.endTransmission();
    Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

    dt->second = bcdToDec(Wire.read() & 0x7f);
    dt->minute = bcdToDec(Wire.read());
    dt->hour = bcdToDec(Wire.read() & 0x3f);
    dt->dayOfWeek = bcdToDec(Wire.read());
    dt->dayOfMonth = bcdToDec(Wire.read());
    dt->month = bcdToDec(Wire.read());
    dt->year = bcdToDec(Wire.read());

    // Check if data is valid
    if ((dt->second > 59) || (dt->minute > 59) || (dt->hour > 23) ||
        (dt->dayOfWeek < 1) || (dt->dayOfMonth > 31) || (dt->month > 11) || (dt->year > 199) ||
        (dt->dayOfWeek > 6))
    {
        return false;
    }

    return true;
}
