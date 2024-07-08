/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "board.h"
#include "Arduino.h"

int num = 100;

void setup() {
    Serial.begin(115200);
}

void loop() {
    num += 100;
    Serial.write('A');
    Serial.write("BCDE\n");
    Serial.println(num, BIN);
    Serial.println(num, OCT);
    Serial.println(num, DEC);
    Serial.println(num, HEX);
    if (Serial.available()) {
        Serial.write("Serial Recieve Data:\n");
        while (Serial.available()) {
            Serial.write(Serial.read());
        }
        Serial.print('\n');
    }
    delay(500);
}