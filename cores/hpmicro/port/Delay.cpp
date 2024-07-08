/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "Delay.h"
unsigned long millis(void)
{
    return mchtmr_get_count(HPM_MCHTMR) / 24E3;
}

unsigned long micros(void)
{
    return mchtmr_get_count(HPM_MCHTMR) / 24;
}
void delay(unsigned long val)
{
    board_delay_ms(val);
}

void delayMicroseconds(unsigned int us)
{
    board_delay_us(us);
}