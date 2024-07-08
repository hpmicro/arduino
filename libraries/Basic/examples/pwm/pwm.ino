/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "board.h"
#include "Arduino.h"

#define PIN_TEST   PIN_PWM

void setup() {
    pinMode(PIN_TEST, PWM);
}

float duty_cycle = 0.0f;
void loop() {
    delay(2000);
    duty_cycle += 0.2;
    duty_cycle = duty_cycle > 1.0f ? 0.0f : duty_cycle;
    printf("output PWM duty cycle is %f\n", duty_cycle);
    analogWrite(PIN_TEST, duty_cycle * 255);
}