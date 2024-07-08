/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <Wire.h>
 
void setup()
{
    /* Wire initialization, joins the i2c bus, if not specified, joins the bus as a master. */
    Wire.begin();
    /* Initialize the serial and set the baud rate to 115200 */
    Serial.begin(115200);
    Serial.print("I2C master read sample\r\n");
}
 
void loop()
{
    /* Requesting 6 bytes from slave #8 */
    Wire.requestFrom(8, 6);
    while (Wire.available() > 0)
    {
        char c = Wire.read();
        Serial.print(c);
    }
    delay(500);
}
 