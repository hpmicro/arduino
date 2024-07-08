/*
 * Copyright (c) 2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <SPI.h>

#define SAMPLE_PIN      PIN_SPI_SS
#define TRANSFER_SIZE   23
char buff[50];
char send_buff[] = "Slave, Hello World!!\r\n";
volatile byte indx;
void setup() {
  Serial.begin(115200);
  pinMode(SAMPLE_PIN, OUTPUT);
  digitalWrite(SAMPLE_PIN, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  Serial.println("SPI-Master Transfer Example\n");
}

void loop() {
  digitalWrite(SAMPLE_PIN, LOW);
  SPI.transmit((uint8_t *)send_buff, sizeof(send_buff));
  digitalWrite(SAMPLE_PIN, HIGH);
  delay(100);
  digitalWrite(SAMPLE_PIN, LOW);
  SPI.receive((uint8_t *)buff, TRANSFER_SIZE);
  digitalWrite(SAMPLE_PIN, HIGH);
  Serial.print(buff);
  delay(200);
}