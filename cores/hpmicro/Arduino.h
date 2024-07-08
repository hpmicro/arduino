/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef Arduino_h
#define Arduino_h

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include "class/wirish_math.h"
#include <string.h>
#include <inttypes.h>
#include "port/Common.h"
#include "board.h"
#include "arduino/pins_arduino.h"
#include <class/HardwareSerial.h>
#include <class/SPI.h>
#include <class/Wire.h>
#include <class/USBMouse.h>
#include <class/USBKeyboard.h>
#include "arduino/i2c_instance.h"
#ifdef __cplusplus
extern "C" {
#endif
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#ifdef __cplusplus
}
#endif

#endif /* _HPMICRO_CORE_ARDUINO_H_ */
