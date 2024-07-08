/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _WIRE_H_
#define _WIRE_H_

#include "Arduino.h"
#include <stdio.h>
extern "C" {
#include "arduino/i2c_com.h"
}

class TwoWire :public Stream {

public:
    TwoWire(i2c_dev_t *dev);
    void begin(); /* as master */
    void begin(uint8_t address); /* as slave */
    void end(void);
    uint8_t requestFrom(uint8_t address, uint16_t quantity);
    uint8_t requestFrom(uint8_t address, uint16_t quantity, bool stop);
    void beginTransmission(uint8_t address);
    uint8_t endTransmission(void);
    uint8_t endTransmission(bool stop);
    virtual size_t write(uint8_t byte);
    virtual size_t write(const char *string);
    virtual size_t write(const uint8_t *data, size_t length);
    virtual int available(void);
    virtual int read(void);
    virtual int peek(void);
    virtual void flush(void);
    void setClock(uint32_t frequency);
    void onReceive(void (*)(int));  /* sets function called on slave write */
    void onRequest(void (*)(void)); /* sets function called on slave read */

    void setWireTimeout(uint32_t timeout = 25000, bool reset_with_timeout = false);
    void clearWireTimeoutFlag(void);
    bool getWireTimeoutFlag();
    void isr_handler(void);

private:
    void i2c_common_init(bool master);
    void i2c_bus_clear(void);
    size_t i2c_write(uint8_t *data, size_t length);
    void i2c_check_dead_lock_reset(void);

private:
    i2c_dev_t *i2c_dev;
    i2c_config_t i2c_config;
    uint8_t local_address;
    uint8_t slave_address;

    bool is_request_from;
    uint16_t request_from_byte_index;
    uint16_t request_from_byte_num;

    bool is_transmission;
    uint16_t transmission_size;

    uint8_t read_buffer[I2C_SOC_TRANSFER_COUNT_MAX];
    uint8_t write_buffer[I2C_SOC_TRANSFER_COUNT_MAX];

    void (*user_on_request)(void);
    void (*user_on_receive)(int);
    uint16_t receive_size_as_slave;
    uint16_t receive_index_as_slave;
    uint16_t request_index_as_slave;
    uint16_t request_size_as_slave;

    uint32_t transfer_timeout_us;
    bool reset_on_timeout;
    bool transfer_timeout_flag;
};

#if defined (SOC_HAS_I2C0)
    extern TwoWire I2C0;
    #define Wire          I2C0
#endif
#if defined (SOC_HAS_I2C1)
    extern TwoWire I2C1;
    #define Wire          I2C1
#endif
#if defined (SOC_HAS_I2C2)
    extern TwoWire I2C2;
    #define Wire          I2C2
#endif
#if defined (SOC_HAS_I2C3)
    extern TwoWire I2C3;
    #define Wire          I2C3
#endif

#endif
