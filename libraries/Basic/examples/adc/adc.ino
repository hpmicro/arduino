/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "board.h"
#include "Arduino.h"

#define PIN_TEST   PIN_ADC

void setup() {
    pinMode(PIN_TEST, ANOLOG);
}

float duty_cycle = 0.0f;
void loop() {
    printf("PIN_TEST: %f\n", 3.3f * analogRead(PIN_TEST) / 1024);
    delay(300);
}