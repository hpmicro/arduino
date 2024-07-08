/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "port/hpm_types.h"
#include "arduino/pins_arduino.h"
#include "hpm_uart_drv.h"

static ring_buffer uart_console_rb;
static ring_buffer uart_console_wb;

uart_dev_t uart_console = {
    .base = HPM_UART0,
    .clock_name = clock_uart0,
    .rb = &uart_console_rb,
    .wb = &uart_console_wb,
    .irq_num = IRQn_UART0,
    .tx_ioc_idx = IOC_PAD_PA00,
    .tx_ioc_fun = IOC_PA00_FUNC_CTL_UART0_TXD,
    .tx_pioc = false,
    .rx_ioc_idx = IOC_PAD_PA01,
    .rx_ioc_fun = IOC_PA01_FUNC_CTL_UART0_RXD,
    .rx_pioc = false,
    .tx_pin = PIN_CONSOLE_TX,
    .rx_pin = PIN_CONSOLE_RX,
};

static ring_buffer uart_console_rb2;
static ring_buffer uart_console_wb2;
uart_dev_t uart_console2 = {
    .base = HPM_UART2,
    .clock_name = clock_uart2,
    .rb = &uart_console_rb2,
    .wb = &uart_console_wb2,
    .irq_num = IRQn_UART2,
    .tx_ioc_idx = IOC_PAD_PB08,
    .tx_ioc_fun = IOC_PB08_FUNC_CTL_UART2_TXD,
    .tx_pioc = false,
    .rx_ioc_idx = IOC_PAD_PB09,
    .rx_ioc_fun = IOC_PB09_FUNC_CTL_UART2_RXD,
    .rx_pioc = false,
    .tx_pin = PIN_P1_8,
    .rx_pin = PIN_P1_10,
};

void uart_isr0(void)
{
    uint8_t irq_id = uart_get_irq_id(uart_console.base);
    if (irq_id == uart_intr_id_rx_data_avail) {
        while (uart_check_status(uart_console.base, uart_stat_data_ready)) {
            rb_push_insert(uart_console.rb, uart_read_byte(uart_console.base));
        }
    }
    if (irq_id == uart_intr_id_tx_slot_avail) {
        
        if (!rb_is_empty(uart_console.wb))
            uart_write_byte(uart_console.base, rb_remove(uart_console.wb));
        else
            uart_disable_irq(uart_console.base, uart_intr_tx_slot_avail);
    }
}

SDK_DECLARE_EXT_ISR_M(IRQn_UART0, uart_isr0)

void uart_isr2(void)
{
    uint8_t irq_id = uart_get_irq_id(uart_console2.base);
    if (irq_id == uart_intr_id_rx_data_avail) {
        while (uart_check_status(uart_console2.base, uart_stat_data_ready)) {
            rb_push_insert(uart_console2.rb, uart_read_byte(uart_console2.base));
        }
    }
    if (irq_id == uart_intr_id_tx_slot_avail) {
        
        if (!rb_is_empty(uart_console2.wb))
            uart_write_byte(uart_console2.base, rb_remove(uart_console2.wb));
        else
            uart_disable_irq(uart_console2.base, uart_intr_tx_slot_avail);
    }
}

SDK_DECLARE_EXT_ISR_M(IRQn_UART2, uart_isr2)