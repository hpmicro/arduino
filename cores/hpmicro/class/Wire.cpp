/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "Wire.h"

TwoWire::TwoWire(i2c_dev_t *dev)
{
    this->i2c_dev = dev;
    this->is_request_from = false;
    this->is_transmission = false;
    this->transfer_timeout_us = 0;
    this->reset_on_timeout = false;
    this->transfer_timeout_flag = false;
}

void TwoWire::begin()
{
    uint32_t freq;
    this->i2c_common_init(true);
    this->i2c_config.i2c_mode = i2c_mode_normal;
    this->i2c_config.is_10bit_addressing = false;
    freq = clock_get_frequency(this->i2c_dev->clock_name);
    i2c_init_master(this->i2c_dev->i2c, freq, &this->i2c_config);
    this->i2c_dev->is_master = true;
    intc_m_enable_irq_with_priority(this->i2c_dev->irq_num, 1);
}

void TwoWire::begin(uint8_t address)
{
    uint32_t freq;
    this->i2c_common_init(false);
    this->i2c_config.i2c_mode = i2c_mode_normal;
    this->i2c_config.is_10bit_addressing = false;
    this->local_address = address;
    freq = clock_get_frequency(this->i2c_dev->clock_name);
    i2c_init_slave(this->i2c_dev->i2c, freq, &this->i2c_config, address);
    this->i2c_dev->is_master = false;
    intc_m_enable_irq_with_priority(this->i2c_dev->irq_num, 1);
}

void TwoWire::end()
{
    clock_remove_from_group(this->i2c_dev->clock_name, 0);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint16_t quantity)
{
    hpm_stat_t stat = status_success;
    if (this->i2c_dev->is_master == false) {
        return 0;
    }
    this->i2c_check_dead_lock_reset();
    stat = i2c_master_read(this->i2c_dev->i2c, address, this->read_buffer, quantity);
    if (stat != status_success) {
        return 0;
    }
    this->is_request_from = true;
    this->request_from_byte_index = 0;
    this->request_from_byte_num = quantity;
    return quantity;
}

uint8_t TwoWire::requestFrom(uint8_t address, uint16_t quantity, bool stop)
{
    hpm_stat_t stat = status_success;
    if (this->i2c_dev->is_master == false) {
        return 0;
    }
    if (quantity > I2C_SOC_TRANSFER_COUNT_MAX) {
        quantity = I2C_SOC_TRANSFER_COUNT_MAX;
    }
    this->i2c_check_dead_lock_reset();
    if (stop == false) {
        stat = i2c_master_transfer(this->i2c_dev->i2c, address, this->read_buffer, quantity, I2C_NO_STOP);
    } else {
        stat = i2c_master_transfer(this->i2c_dev->i2c, address, this->read_buffer, quantity, I2C_RD);
    }
    if (stat != status_success) {
        return 0;
    }
    this->is_request_from = true;
    this->request_from_byte_num = quantity;
    this->request_from_byte_index = 0;
    return quantity;
}

void TwoWire::beginTransmission(uint8_t address)
{
    if (this->i2c_dev->is_master == false) {
        return;
    }
    this->slave_address = address;
    this->is_transmission = true;
    this->transmission_size = 0;
}

uint8_t TwoWire::endTransmission(void)
{
    hpm_stat_t stat = status_success;
    if ((this->i2c_dev->is_master == false) ||
        (this->is_transmission == false)) {
        return I2C_OTHER_ERROR;
    }
    if (this->transmission_size > I2C_SOC_TRANSFER_COUNT_MAX) {
        return I2C_DATA_TOO_LONG;
    }
    this->i2c_check_dead_lock_reset();
    stat = i2c_master_transfer(this->i2c_dev->i2c, this->slave_address,
                               this->write_buffer, this->transmission_size,
                               I2C_WR);
    this->is_transmission = false;
    if (stat == status_timeout) {
        return I2C_TIMEOUT;
    } else if (stat == status_i2c_no_ack) {
        return I2C_NACK_DATA;
    } else if (stat == status_success) {
        return I2C_SUCCESS;
    } else {
        return I2C_OTHER_ERROR;
    }
}

uint8_t TwoWire::endTransmission(bool stop)
{
    (void)stop;
    return this->endTransmission();
}

size_t TwoWire::write(uint8_t byte)
{
    return this->i2c_write(&byte, 1);
}
size_t TwoWire::write(const char *string)
{
    size_t size = strlen(string);
    return this->i2c_write((uint8_t *)string, size);
}
size_t TwoWire::write(const uint8_t *data, size_t length)
{
    size_t size = length;
    return this->i2c_write((uint8_t *)data, size);
}

int TwoWire::available(void)
{
    uint16_t remain_size = this->request_from_byte_num - this->request_from_byte_index;
    if (this->i2c_dev->is_master == true) {
        if (this->is_request_from == true) {
            if (remain_size == 0) {
                this->is_request_from == false;
            }
            return remain_size;
        }
    } else {
        remain_size = this->receive_size_as_slave - this->receive_index_as_slave;
        if (remain_size == 0) {
            this->receive_size_as_slave = 0;
            this->receive_index_as_slave = 0;
        }
        return remain_size;
    }
    return 0;
}

int TwoWire::read(void)
{
    int ch = -1;
    if (this->i2c_dev->is_master == true) {
        if (this->is_request_from == true) {
            if (this->request_from_byte_index < this->request_from_byte_num) {
                ch = this->read_buffer[this->request_from_byte_index++];
            }
        }
    } else {
        if (this->receive_index_as_slave < this->receive_size_as_slave) {
            ch = this->read_buffer[this->receive_index_as_slave++];
        }
    }
    return ch;
}

void TwoWire::onReceive( void (*function)(int) )
{
    i2c_enable_irq(this->i2c_dev->i2c, I2C_EVENT_ADDRESS_HIT | I2C_EVENT_TRANSACTION_COMPLETE);
    this->receive_size_as_slave = 0;
    this->user_on_receive = function;
}

void TwoWire::onRequest( void (*function)(void) )
{
    i2c_enable_irq(this->i2c_dev->i2c, I2C_EVENT_ADDRESS_HIT | I2C_EVENT_TRANSACTION_COMPLETE);
    this->user_on_request = function;
    this->request_size_as_slave = 0;
    this->request_index_as_slave = 0;
}

void TwoWire::setWireTimeout(uint32_t timeout, bool reset_with_timeout)
{
    this->transfer_timeout_us = timeout;
    this->reset_on_timeout = reset_with_timeout;
}

void TwoWire::clearWireTimeoutFlag(void)
{
    this->transfer_timeout_flag = false;
    i2s_gen_reset_signal(this->i2c_dev->i2c, 9);
    board_delay_ms(10);
}

bool TwoWire::getWireTimeoutFlag()
{
    return this->transfer_timeout_flag;
}

void TwoWire::isr_handler(void)
{
    volatile uint32_t status, irq;
    status = i2c_get_status(i2c_dev->i2c);
    irq = i2c_get_irq_setting(i2c_dev->i2c);
    /* address hit */
    if (status & I2C_EVENT_ADDRESS_HIT) {
        if (I2C_DIR_SLAVE_READ == i2c_get_direction(i2c_dev->i2c)) {
            i2c_enable_irq(i2c_dev->i2c, I2C_EVENT_FIFO_HALF);
        } else {
            request_index_as_slave = 0;
            request_size_as_slave = 0;
            if (user_on_request != nullptr) {
                user_on_request();
            }
            i2c_enable_irq(i2c_dev->i2c, I2C_EVENT_FIFO_EMPTY);
        }
        i2c_clear_status(i2c_dev->i2c, I2C_EVENT_ADDRESS_HIT);
    }

    /* receive */
    if (status & I2C_EVENT_FIFO_HALF) {
        while (!i2c_fifo_is_empty(i2c_dev->i2c)) {
            read_buffer[receive_size_as_slave++] = i2c_read_byte(i2c_dev->i2c);
        }
    }

    /* transmit */
    if ((status & I2C_EVENT_FIFO_EMPTY) && (irq & I2C_EVENT_FIFO_EMPTY)) {
        while (!i2c_fifo_is_full(i2c_dev->i2c)) {
            i2c_write_byte(i2c_dev->i2c, write_buffer[request_index_as_slave++]);
            if (request_index_as_slave == request_size_as_slave) {
                i2c_disable_irq(i2c_dev->i2c, I2C_EVENT_FIFO_EMPTY);
                break;
            }
        }
    }

    /* complete */
    if (status & I2C_EVENT_TRANSACTION_COMPLETE) {
        if (I2C_DIR_SLAVE_READ == i2c_get_direction(i2c_dev->i2c)) {
            while (!i2c_fifo_is_empty(i2c_dev->i2c)) {
                read_buffer[receive_size_as_slave++] = i2c_read_byte(i2c_dev->i2c);
            }
            i2c_disable_irq(i2c_dev->i2c, I2C_EVENT_FIFO_HALF);
            user_on_receive(receive_size_as_slave);
        }
        i2c_clear_status(i2c_dev->i2c, I2C_EVENT_TRANSACTION_COMPLETE);
    }
}


int TwoWire::peek(void)
{
    int ch = -1;
    if (this->request_from_byte_index < this->request_from_byte_num) {
        ch = this->read_buffer[this->request_from_byte_index];
    }
    return ch;
}
void TwoWire::flush(void)
{
    this->is_request_from = false;
    this->is_transmission = false;
    this->request_from_byte_index = 0;
    this->request_from_byte_num = 0;
    this->transmission_size = 0;
}

void TwoWire::setClock(uint32_t frequency)
{
    uint32_t freq;
    this->i2c_config.is_10bit_addressing = false;
    freq = clock_get_frequency(this->i2c_dev->clock_name);
    if (frequency <= I2C_STANDARD_SPEED) {
        this->i2c_config.i2c_mode = i2c_mode_normal;
    } else if ((frequency > I2C_STANDARD_SPEED) && (frequency <= I2C_FAST_SPEED)) {
        this->i2c_config.i2c_mode = i2c_mode_fast;
    } else {
        this->i2c_config.i2c_mode = i2c_mode_fast_plus;
    }
    if (this->i2c_dev->is_master == true) {
        i2c_init_master(this->i2c_dev->i2c, freq, &this->i2c_config);
    } else {
        i2c_init_slave(this->i2c_dev->i2c, freq, &this->i2c_config, this->local_address);
    }
}
void TwoWire::i2c_common_init(bool master)
{
    HPM_IOC->PAD[this->i2c_dev->scl_ioc_pad].FUNC_CTL = this->i2c_dev->scl_ioc_func;
    HPM_IOC->PAD[this->i2c_dev->scl_ioc_pad].PAD_CTL = this->i2c_dev->scl_ioc_pad_ctrl;
    HPM_IOC->PAD[this->i2c_dev->sda_ioc_pad].FUNC_CTL = this->i2c_dev->sda_ioc_func;
    HPM_IOC->PAD[this->i2c_dev->sda_ioc_pad].PAD_CTL = this->i2c_dev->sda_ioc_pad_ctrl;
    if (master == true) {
        this->i2c_bus_clear();
    }
    clock_add_to_group(this->i2c_dev->clock_name, 0);
    clock_set_source_divider(this->i2c_dev->clock_name, clk_src_osc24m, 1U);
}

void TwoWire::i2c_bus_clear()
{
    if (i2c_get_line_scl_status(this->i2c_dev->i2c) == false) {
        while (1) {
        }
    }
    if (i2c_get_line_sda_status(this->i2c_dev->i2c) == false) {
    } else {
        return;
    }
    i2s_gen_reset_signal(this->i2c_dev->i2c, 9);
    board_delay_ms(100);
}

size_t TwoWire::i2c_write(uint8_t *data, size_t length)
{
    hpm_stat_t stat = status_success;
    size_t size = length;
    if (this->i2c_dev->is_master == true) {
        if (this->is_transmission == true) {
            memcpy(&this->write_buffer[this->transmission_size], data, size);
            this->transmission_size += size;
        } else {
            i2c_master_write(this->i2c_dev->i2c, this->slave_address, data, size);
        }
    } else {
        this->request_size_as_slave = size;
        memcpy(&this->write_buffer[0], data, size);
    }
    return size;
}

void TwoWire::i2c_check_dead_lock_reset(void)
{
    uint32_t ticks_per_us = (hpm_core_clock + 1000000 - 1U) / 1000000;
    uint64_t expected_ticks = hpm_csr_get_core_cycle() + (uint64_t)ticks_per_us * this->transfer_timeout_us;
    if (this->transfer_timeout_us != 0) {
        while (1) {
            /* is idle */
            if ((i2c_get_line_scl_status(this->i2c_dev->i2c) == true) &&
                (i2c_get_line_sda_status(this->i2c_dev->i2c) == true)) {
                this->transfer_timeout_flag = false;
                break;
            }
            if (hpm_csr_get_core_cycle() > expected_ticks) {
                if (this->reset_on_timeout == true) {
                    i2s_gen_reset_signal(this->i2c_dev->i2c, 9);
                    board_delay_ms(10);
                }
                this->transfer_timeout_flag = true;
                break;
            }
        }
    }
}
