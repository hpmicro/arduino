/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
/**
 * @file HardwareSerial.h
 * @brief serial port interface.
 */

#ifndef _HARDWARESERIAL_H_
#define _HARDWARESERIAL_H_

#include "Print.h"
#include "board.h"
#include "Stream.h"
#include "arduino/pins_arduino.h"
/*
 * IMPORTANT:
 *
 * This class documented "by hand" (i.e., not using Doxygen) in the
 * leaflabs-docs/ repository.
 *
 * If you alter the public HardwareSerial interface, you MUST update
 * the documentation accordingly.
 */

struct usart_dev;
#define SERIAL_5N1 1
#define SERIAL_6N1 2
#define SERIAL_7N1 3
#define SERIAL_8N1 4
#define SERIAL_5N2 5
#define SERIAL_6N2 6
#define SERIAL_7N2 7
#define SERIAL_8N2 8
#define SERIAL_5E1 9
#define SERIAL_6E1 10
#define SERIAL_7E1 11
#define SERIAL_8E1 12
#define SERIAL_5E2 13
#define SERIAL_6E2 14
#define SERIAL_7E2 15
#define SERIAL_8E2 16
#define SERIAL_5O1 17
#define SERIAL_6O1 18
#define SERIAL_7O1 19
#define SERIAL_8O1 20
#define SERIAL_5O2 21
#define SERIAL_6O2 22
#define SERIAL_7O2 23
#define SERIAL_8O2 24

#define DEFINE_HWSERIAL(name, n)                                   \
    HardwareSerial name(&n)	
class HardwareSerial : public Stream {

public:
    HardwareSerial(uart_dev_t *usart_device);

    /* Set up/tear down */
    void begin(uint32 baud);
    void begin(uint32 baud,uint8_t config);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;

    /* Pin accessors */
    int txPin(void) { return this->usart_device->tx_pin; }
    int rxPin(void) { return this->usart_device->rx_pin; }
    
    operator bool() { return true; }

    /* Escape hatch into libmaple */
    /* FIXME [0.0.13] documentation */
    uart_dev_t* c_dev(void) { return (uart_dev_t *)this->usart_device; }
private:
    uart_dev_t *usart_device;
    uint32_t err_count;
    uint32_t irq_num;
};
extern HardwareSerial Serial1, Serial2;
#define Serial	Serial1

#endif	//_HARDWARESERIAL_H_
