/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "HardwareSerial.h"
#include "arduino/pins_arduino.h"
#include "hpm_soc.h"
#include "hpm_gpio_drv.h"
#include "hpm_uart_drv.h"
#include "hpm_interrupt.h"
#include "ring_buffer.h"
HardwareSerial::HardwareSerial(uart_dev_t *usart_device)
{
    this->usart_device = usart_device;
}

void HardwareSerial::begin(uint32 baud) 
{
    begin(baud,SERIAL_8N1);
}

void HardwareSerial::begin(uint32 baud, uint8_t config_arg) 
{

    hpm_stat_t stat = status_fail;

    this->irq_num = usart_device->irq_num;
    
    rb_init(usart_device->rb, USART_RX_BUF_SIZE, usart_device->rx_buf);
    rb_init(usart_device->wb, USART_TX_BUF_SIZE, usart_device->tx_buf);

    HPM_IOC->PAD[usart_device->tx_ioc_idx].FUNC_CTL = usart_device->tx_ioc_fun;
    HPM_IOC->PAD[usart_device->rx_ioc_idx].FUNC_CTL = usart_device->rx_ioc_fun;

    if (usart_device->tx_pioc) {
        HPM_PIOC->PAD[usart_device->tx_ioc_idx].FUNC_CTL = usart_device->tx_pioc_fun;
    }
    if (usart_device->rx_pioc) {
        HPM_PIOC->PAD[usart_device->rx_ioc_idx].FUNC_CTL = usart_device->rx_pioc_fun;
    }

    uart_config_t config = {0};
    uart_default_config(usart_device->base, &config);
    config.src_freq_in_hz = clock_get_frequency(usart_device->clock_name);
    config.baudrate = baud;
    switch (config_arg) {
        case SERIAL_5N1:
            config.word_length = word_length_5_bits;
        break;
        case SERIAL_6N1:
            config.word_length = word_length_6_bits;
        break;
        case SERIAL_7N1:
            config.word_length = word_length_7_bits;
        break;
        case SERIAL_5N2:
            config.word_length = word_length_5_bits;
            config.num_of_stop_bits = stop_bits_2;
        break;
        case SERIAL_6N2:
            config.word_length = word_length_6_bits;
            config.num_of_stop_bits = stop_bits_2;
        break;
        case SERIAL_7N2:
            config.word_length = word_length_7_bits;
            config.num_of_stop_bits = stop_bits_2;
        break;
        case SERIAL_8N2:
            config.num_of_stop_bits = stop_bits_2;
        break;
        case SERIAL_5E1:
            config.word_length = word_length_5_bits;
            config.parity = parity_even;
        break;
        case SERIAL_6E1:
            config.word_length = word_length_6_bits;
            config.parity = parity_even;
        break;
        case SERIAL_7E1:
            config.word_length = word_length_7_bits;
            config.parity = parity_even;
        break;
        case SERIAL_8E1:
            config.parity = parity_even;
        break;
        case SERIAL_5E2:
            config.word_length = word_length_5_bits;
            config.num_of_stop_bits = stop_bits_2;
            config.parity = parity_even;
        break;
        case SERIAL_6E2:
            config.word_length = word_length_6_bits;
            config.num_of_stop_bits = stop_bits_2;
            config.parity = parity_even;
        break;
        case SERIAL_7E2:
            config.word_length = word_length_7_bits;
            config.num_of_stop_bits = stop_bits_2;
            config.parity = parity_even;
        break;
        case SERIAL_8E2:
            config.num_of_stop_bits = stop_bits_2;
            config.parity = parity_even;
        break;
        case SERIAL_5O1:
            config.word_length = word_length_5_bits;
            config.parity = parity_odd;
        break;
        case SERIAL_6O1:
            config.word_length = word_length_6_bits;
            config.parity = parity_odd;
        break;
        case SERIAL_7O1:
            config.word_length = word_length_7_bits;
            config.parity = parity_odd;
        break;
        case SERIAL_8O1:
            config.parity = parity_odd;
        break;
        case SERIAL_5O2:
            config.word_length = word_length_5_bits;
            config.num_of_stop_bits = stop_bits_2;
            config.parity = parity_odd;
        break;
        case SERIAL_6O2:
            config.word_length = word_length_6_bits;
            config.num_of_stop_bits = stop_bits_2;
            config.parity = parity_odd;
        break;
        case SERIAL_7O2:
            config.word_length = word_length_7_bits;
            config.num_of_stop_bits = stop_bits_2;
            config.parity = parity_odd;
        break;
        case SERIAL_8O2:
            config.num_of_stop_bits = stop_bits_2;
            config.parity = parity_odd;
        break;
        default:
        break;
    }
    stat = uart_init(usart_device->base, &config);
    if (status_success != stat) {
        printf("Failed init HardwareSerial\n");
        while(1);
    }
    uart_enable_irq(usart_device->base, uart_intr_rx_data_avail_or_timeout);
    intc_m_enable_irq_with_priority(irq_num, 1);
}

void HardwareSerial::end(void)
{
    intc_m_disable_irq(irq_num);
}

int HardwareSerial::read(void)
{
    if(available()) {
        return rb_remove(usart_device->rb);
    } else {
        return -1;
    }
}

int HardwareSerial::available(void) {
    return rb_full_count(this->usart_device->rb);
}

int HardwareSerial::peek(void)
{
    return rb_peek(this->usart_device->rb);
}

int HardwareSerial::availableForWrite(void)
{
    return this->usart_device->wb->size-rb_full_count(this->usart_device->wb);
}

size_t HardwareSerial::write(unsigned char ch)
{
    hpm_stat_t stat;
    stat = uart_send_byte(usart_device->base, ch);
    if (stat != status_success) {
        err_count++;
    }
    return 1;
}

void HardwareSerial::flush(void)
{
    while(!rb_is_empty(this->usart_device->wb)); // wait for TX buffer empty
}
