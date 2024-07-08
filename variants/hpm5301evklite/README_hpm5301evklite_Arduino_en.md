# HPMicro Arduino HPM5301EVKLITE Description

HPM5301EVKLite is a development board based on Xianji's entry-level high-performance MCU HPM5301. HPM5301EVKLite provides a USB Type-C interface for high-speed USB-OTG functionality, with onboard buttons and LEDs for convenient user interaction. It also provides an extension interface that is compatible with Raspberry Pi and a standard JTAG debugging interface.

The main technical parameters are as follows:
| Name ||
| -------- |------ |
| Microcontroller |HPM5301xEGx |
| Board Power Supply (USB/VIN) | 5V |
| MCU frequency | 480MHz |
| SRAM | 256K |
| FLASH | 1MB |
| LED number | 1 |
| User key number | 1 |
| GPIO number | 21 |
| PWM pin number | 2 |
| Analog input pin number | 8 |
| UART instance number | 2 |
| SPI instance number | 1 |
| I2C instance number | 1 |

- GPIO/ADC/PWM
The following is the corresponding relationship between the pin index and development board screen printing required by Arduino users to configure and operate pins during programming:

| Name |Position (silk screen) |Arduino Programming Index | Description |
| -------- |------ |----------------------- |---|
| LED | Onboard LED | LED_BUILTIN | Onboard LED |
| Key | USER KEY | PIN_PUSH_BUTTON | User key |
| PIN_J3_33 | J3[33] | PIN_J3_33 | PWM PIN/GPIO |
| PIN_J3_28 | J3[28] | PIN_J3_28 | ADC input PIN/PWM PIN/GPIO |
| PIN_J3_26 | J3[26] | PIN_J3_26 | ADC input PIN/GPIO |
| PIN_J3_13 | J3[13] | PIN_J3_13 | ADC input PIN/GPIO |
| PIN_J3_27 | J3[27] | PIN_J3_27 | ADC input PIN/GPIO |
| PIN_J3_10 | J3[10] | PIN_J3_10 | ADC input PIN/GPIO |
| PIN_J3_8 | J3[8] | PIN_J3_8 | ADC input PIN/GPIO |
| PIN_J3_7 | J3[7] | PIN_J3_7 | GPIO PIN |
| PIN_J3_11 | J3[11] | PIN_J3_11 | GPIO PIN |
| PIN_J3_19 | J3[19] | PIN_J3_19 | GPIO PIN |
| PIN_J3_21 | J3[21] | PIN_J3_21 | GPIO PIN |
| PIN_J3_23 | J3[23] | PIN_J3_23 | GPIO PIN |
| PIN_J3_24 | J3[24] | PIN_J3_24 | GPIO PIN |
| PIN_J3_29 | J3[29] | PIN_J3_29 | GPIO PIN |
| PIN_J3_31 | J3[31] | PIN_J3_31 | GPIO PIN |
| PIN_J3_32 | J3[32] | PIN_J3_32 | GPIO PIN |

- UART
The UART0 pin is connected to a USB to UART chip, and the port is screen printed as USBDEBUG

| Function      | Position   |
| --------- | ------ |
| UART3.TXD | J3[8]  |
| UART3.RXD | J3[10] |
| UART0.TXD | J3[36] |
| UART0.RXD | J3[38] |


- SPI

| Function      | Position   |
| --------- | ------ |
| SPI1.CSN  | J3[24] |
| SPI1.SCLK | J3[23] |
| SPI1.MISO | J3[21] |
| SPI1.MOSI | J3[19] |

- I2C

| Function     | Position   |
| -------- | ------ |
| I2C2.SCL | J3[5] |
| I2C2.SDA | J3[3] |

## Programmer and debugger support
### Prgrammer

Supported JLink and CMSIS_DAP/FT2232 using jtag interface to upload program to board

### Debugger

Only supported CMSIS_DAP to debug the program