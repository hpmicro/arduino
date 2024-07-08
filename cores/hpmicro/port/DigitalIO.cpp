/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "DigitalIO.h"

void digitalWrite(pin_size_t pinNumber, uint8 status)
{
    /* Assert wether pin number is out of range */
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));
    const gpio_desc_t* info = PIN_MAP[pinNumber].gpio_device;
    assert(info != NULL);
    pinMode(pinNumber, OUTPUT);
    switch (status) {
        case FALLING:
        case LOW:
            gpio_write_pin(info->ctrl, info->do_idx, info->pin, 0);
        break;
        case RISING:
        case HIGH:
            gpio_write_pin(info->ctrl, info->do_idx, info->pin, 1);
        break;
        case CHANGE:
            gpio_toggle_pin(info->ctrl, info->do_idx, info->pin);
        break;
    }
}

uint8 digitalRead(pin_size_t pinNumber)
{
    /* Assert wether pin number is out of range */
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));
    const gpio_desc_t* info = PIN_MAP[pinNumber].gpio_device;
    assert(info != NULL);
    uint8_t stat = gpio_read_pin(info->ctrl, info->di_idx, info->pin);
    return stat == 0 ? LOW : HIGH;
}

unsigned long pulseIn(pin_size_t pin, uint8_t state, unsigned long timeout)
{
    unsigned long time_enter = micros();
    bool detected = false;
    while ((micros() - time_enter) / 1000 < timeout) {
        if (!detected) { /* Waiting for pulse occur */
            if (state) { /* Waiting High Level Occur */
                if (digitalRead(pin) == HIGH)
                    detected = true;
            } else {
                if (digitalRead(pin) == LOW)
                    detected = true;
            }
        } else {
            if (state) { 
                if (digitalRead(pin) == LOW) {
                    return ((micros() - time_enter) / 1000);
                }
            } else {
                if (digitalRead(pin) == HIGH) {
                    return ((micros() - time_enter) / 1000);
                }
            }
        }
    }
    return 0;
}

void shiftOut(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST) {
            digitalWrite(dataPin, val & 1 ? HIGH : LOW);
            val >>= 1;
        } else {	
            digitalWrite(dataPin, (val & 128) != 0 ? HIGH : LOW);
            val <<= 1;
        }
            
        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);		
    }
}

uint8_t shiftIn(pin_size_t dataPin, pin_size_t clockPin, BitOrder bitOrder)
{
    uint8_t value = 0;
    uint8_t i;

    for (i = 0; i < 8; ++i) {
        digitalWrite(clockPin, HIGH);
        if (bitOrder == LSBFIRST)
            value |= (digitalRead(dataPin) == HIGH ? 1 : 0) << i;
        else
            value |= (digitalRead(dataPin) == HIGH ? 1 : 0) << (7 - i);
        digitalWrite(clockPin, LOW);
    }
    return value;
}

void attachInterrupt(pin_size_t pinNumber, voidFuncPtr callback, uint8 mode)
{
    /* Assert wether pin number is out of range */
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));
    assert(callback != NULL);

    gpio_interrupt_trigger_t trigger;
    switch (mode) {
        case LOW:
            trigger = gpio_interrupt_trigger_level_low;
            break;
        case HIGH:
            trigger = gpio_interrupt_trigger_level_high;
            break;
        case FALLING:
            trigger = gpio_interrupt_trigger_edge_falling;
            break;
        case RISING:
            trigger = gpio_interrupt_trigger_edge_rising;
            break;
        case CHANGE:
#if defined(GPIO_SOC_HAS_EDGE_BOTH_INTERRUPT) && (GPIO_SOC_HAS_EDGE_BOTH_INTERRUPT == 1)
            trigger = gpio_interrupt_trigger_edge_both;
#else
            perror("SOC do not support both edge interrupt.\n");
            assert(0);
#endif
            break;
        default:
            assert(0);
            break;
    }
    const gpio_desc_t* info = PIN_MAP[pinNumber].gpio_device;
    assert(info != NULL);
    gpio_handlers[info->irq_group][info->pin].handler = (voidFuncPtrParam)callback;
    gpio_handlers[info->irq_group][info->pin].arg = NULL;
    gpio_config_pin_interrupt(info->ctrl, info->di_idx, info->pin, trigger);
    gpio_enable_pin_interrupt(info->ctrl, info->di_idx, info->pin);
    intc_m_enable_irq_with_priority(info->irq_num, 1);
}

void attachInterruptParam(pin_size_t pinNumber, voidFuncPtrParam callback, uint8 mode, void* param)
{
    /* Assert wether pin number is out of range */
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));
    assert(callback != NULL);
    const gpio_desc_t* info = PIN_MAP[pinNumber].gpio_device;
    assert(info != NULL);
    gpio_handlers[info->irq_group][info->pin].handler = callback;
    gpio_handlers[info->irq_group][info->pin].arg = param;
}

void detachInterrupt(pin_size_t pinNumber)
{
    /* Assert wether pin number is out of range */
    assert(pinNumber < sizeof(PIN_MAP) / sizeof(hpm_pin_info_t));
    const gpio_desc_t* info = PIN_MAP[pinNumber].gpio_device;
    assert(info != NULL);
    gpio_handlers[info->irq_group][info->pin].handler = NULL;
    gpio_handlers[info->irq_group][info->pin].arg = NULL;

}
