/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "board.h"
#include "Arduino.h"

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_PUSH_BUTTON, INPUT);
}

void loop() {
    printf("Button is %s\n", digitalRead(PIN_PUSH_BUTTON) == PIN_PUSH_BUTTON_PRESSED ? "PRESSED" : "RELEASED");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
}