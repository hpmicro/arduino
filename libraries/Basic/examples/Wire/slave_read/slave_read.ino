/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <Wire.h>
 
void setup()
{
    Wire.begin(8);
    Wire.onReceive(receiveEvent);
    Serial.begin(115200);
    Serial.print("I2C slave read sample\r\n");
}

void loop()
{
    delay(100);
}

void receiveEvent(int howMany)
{
    while (1 < Wire.available())
    {
        char c = Wire.read();
        Serial.print(c);
    }
    int x = Wire.read();
    Serial.println(x);
}