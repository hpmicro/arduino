# HPMicro Arduino HPM5300EVK Description

The HPM5300EVK provides a series of interfaces for the characteristic peripherals of the HPM5300 series microcontrollers, including an ADC input SMA interface, a first-class motor control interface, a ABZ output interface, a RS485/422 interface. HPM5300EVK also integrates one 2x20 pin IO expansion interfaces, which connect most of the IOs of HPM5300 MCU for users to freely evaluate. HPM5300EVK expands NOR Flash storage for MCU and integrates an on-board debugger.

The main technical parameters are as follows:
| Name ||
| -------- |------ |
| Microcontroller |HPM5361ICB1 |
| Board Power Supply (USB/VIN) | 5V |
| MCU frequency | 480MHz |
| SRAM | 256K |
| FLASH | 4MB |
| LED number | 1 |
| User key number | 1 |
| GPIO number | 34 |
| PWM pin number | 6 |
| Analog input pin number | 8 |
| UART instance number | 2 |
| SPI instance number | 1 |
| I2C instance number | 2 |

- GPIO/ADC/PWM
The following is the corresponding relationship between the pin index and development board screen printing required by Arduino users to configure and operate pins during programming:

| Name |Position (silk screen) |Arduino Programming Index | Description |
| -------- |------ |----------------------- |---|
| LED | Onboard LED | LED_BUILTIN | Onboard LED |
| Key | USER KEY | PIN_PUSH_BUTTON | User key |
| PWM_WH | J7[PWM_WH] | PIN_PWM_WH | PWM pin |
| PWM_WL | J7[PWM_WL] | PIN_PWM_WL | PWM PIN |
| PWM_VH | J7[PWM_VH] | PIN_PWM_VH | PWM PIN |
| PWM_VL | J7[PWM_VL] | PIN_PWM_VL | PWM PIN |
| PWM_UH | J7[PWM_UH] | PIN_PWM_UH | PWM PIN |
| PWM_UL | J7[PWM_UL] | PIN_PWM_UL | PWM PIN |
| ADC-A | J7[ADC-A] | PIN_ADC_A | ADC input PIN |
| ADC-B | J7[ADC-B] | PIN_ADC_B | ADC input PIN |
| ADC-C | J7[ADC-C] | PIN_ADC_C | ADC input PIN |
| ADC-D | J7[ADC-D] | PIN_ADC_D | ADC input PIN |
| ADC-IW | J7[ADC-IW] | PIN_ADC_IW | ADC input PIN |
| ADC-IU | J7[ADC-IU] | PIN_ADC_IU | ADC input PIN |
| ADC-IV | J7[ADC-IV] | PIN_ADC_IV | ADC input PIN |
| ADC_BUS | J7[ADCBUS] | PIN_ADC_BUS | ADC input PIN |
| GPIOP1_3 | P1[3] | PIN_P1_3 | GPIO PIN |
| GPIOP1_5 | P1[5] | PIN_P1_5 | GPIO PIN |
| GPIOP1_7 | P1[7] | PIN_P1_7 | GPIO PIN |
| GPIOP1_8 | P1[8] | PIN_P1_8 | GPIO PIN |
| GPIOP1_10 | P1[10] | PIN_P1_10 | GPIO PIN |
| GPIOP1_11 | P1[11] | PIN_P1_11 | GPIO PIN |
| GPIOP1_12 | P1[12] | PIN_P1_12 | GPIO PIN |
| GPIOP1_13 | P1[13] | PIN_P1_13 | GPIO PIN |
| GPIOP1_15 | P1[15] | PIN_P1_15 | GPIO PIN |
| GPIOP1_16 | P1[16] | PIN_P1_16 | GPIO PIN |
| GPIOP1_18 | P1[18] | PIN_P1_18 | GPIO PIN |
| GPIOP1_19 | P1[19] | PIN_P1_19 | GPIO PIN |
| GPIOP1_21 | P1[21] | PIN_P1_21 | GPIO PIN |
| GPIOP1_22 | P1[22] | PIN_P1_22 | GPIO PIN |
| GPIOP1_23 | P1[23] | PIN_P1_23 | GPIO PIN |
| GPIOP1_24 | P1[24] | PIN_P1_24 | GPIO PIN |
| GPIOP1_26 | P1[26] | PIN_P1_26 | GPIO PIN |
| GPIOP1_27 | P1[27] | PIN_P1_27 | GPIO PIN |
| GPIOP1_28 | P1[28] | PIN_P1_28 | GPIO PIN |
| GPIOP1_29 | P1[29] | PIN_P1_29 | GPIO PIN |
| GPIOP1_31 | P1[31] | PIN_P1_31 | GPIO PIN |
| GPIOP1_32 | P1[32] | PIN_P1_32 | GPIO PIN |
| GPIOP1_33 | P1[33] | PIN_P1_33 | GPIO PIN |
| GPIOP1_35 | P1[35] | PIN_P1_25 | GPIO PIN |
| GPIOP1_37 | P1[37] | PIN_P1_37 | GPIO PIN |
| GPIOP1_38 | P1[38] | PIN_P1_38 | GPIO PIN |
| GPIOP1_40 | P1[40] | PIN_P1_40 | GPIO PIN |
| BOARD_ID | J7[BoardID] | PIN_BOARD_ID | GPIO PIN |
| QEI_A | J7[QEI_A] | PIN_QEI_A | GPIO PIN |
| QEI_B | J7[QEI_B] | PIN_QEI_B | GPIO PIN |
| QEI_Z | J7[QEI_Z] | PIN_QEI_Z | GPIO PIN |
| QEO_A | J7[QEO_A] | PIN_QEO_A | GPIO PIN |
| QEO_B | J7[QEO_B] | PIN_QEO_B | GPIO PIN |
| QEO_Z | J7[QEO_Z] | PIN_QEO_Z | GPIO PIN |

- UART
The UART0 pin is connected to a USB to UART chip, and the port is screen printed as USBDEBUG

| Function      | Position   |
| --------- | ------ |
| UART2.TXD | P1[8]  |
| UART2.RXD | P1[10] |
| UART2.DE  | P1[38] |


- SPI

| Function      | Position   |
| --------- | ------ |
| SPI1.CSN  | P1[24] |
| SPI1.SCLK | P1[23] |
| SPI1.MISO | P1[21] |
| SPI1.MOSI | P1[19] |

- I2C

| Function     | Position   |
| -------- | ------ |
| I2C0.SCL | P1[28] |
| I2C0.SDA | P1[27] |
| I2C1.SCL | P1[5] |
| I2C1.SDA | P1[3] |

## Programmer and debugger support
### Prgrammer

Supported JLink and CMSIS_DAP/FT2232 using jtag interface to upload program to board

### Debugger

Only supported CMSIS_DAP to debug the program