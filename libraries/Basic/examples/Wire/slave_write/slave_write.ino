/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <Wire.h>
void setup()
{
    /* Wire is initialized and joins the i2c bus as slave device address #8 */
    Wire.begin(8);
    /* Register request response event */
    Wire.onRequest(requestEvent);
    /* Initialize the serial and set the baud rate to 115200 */
    Serial.begin(115200);
    Serial.print("I2C slave write sample\r\n");
}
 
void loop()
{
    delay(100);
}
 
void requestEvent()
{
    Wire.write("hello ");
}