/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <Wire.h>
 
void setup()
{
    Wire.begin();
    Serial.begin(115200);
    Serial.print("I2C master write sample\r\n");
}
byte x = 0;

void loop()
{
    Wire.beginTransmission(8);
    Wire.write("x is ");
    Wire.write(x);
    Wire.endTransmission();
    x++;
    delay(500);
}