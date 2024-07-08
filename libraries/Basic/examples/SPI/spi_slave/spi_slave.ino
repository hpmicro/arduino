/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <SPI.h>
#define TRANSFER_SIZE   23
char buff[50];
char send_buff[] = "Master, Hello World!\r\n";
volatile byte indx, send_indx;

void setup() {
  Serial.begin(115200);
  SPI.begin(SPI_SLAVE_ROLE);
  Serial.println("SPI-Slave Transfer Example\n");
}

void loop() {
  SPI.receive((uint8_t *)buff, TRANSFER_SIZE);
  SPI.transmit((uint8_t *)send_buff, sizeof(send_buff));
  Serial.print(buff);
  delay(100);
}
