/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef _HPM_TYPES_H_
#define _HPM_TYPES_H_
#include <stdint.h>
typedef uint8_t uint8;
typedef uint16_t uint16; 
typedef uint32_t uint32; 
typedef uint64_t uint64; 
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef void (*voidFuncPtr)(void);
typedef void (*voidFuncPtrParam)(void*);

#endif
