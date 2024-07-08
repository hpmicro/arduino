# HPMicro Arduino HPM5300EVK 引脚定义一览

HPM5301EVKLite是基于先楫的入门级高性能MCU HPM5301的开发板。HPM5301EVKLite提供了一个USB Type-C接口实现高速的USB-OTG功能，板载的按键和LED方便用户交互，同时提供了一个适配了树莓派的扩展接口和一个标准的JTAG调试接口。

主要技术参数如下：
| 名称 ||
| -------- |------ |
| 处理器 |HPM5301xEGx |
| 外部供电 | 5V |
| 处理器主频 | 480MHz |
| 运行内存大小 | 256K |
| FLASH大小 | 1MB |
| LED数量 | 1 |
| 用户按键数量 | 1 |
| GPIO引脚数量 | 31 |
| PWM输出引脚数量 | 2 |
| 模拟信号输入引脚数量 | 8 |
| UART | 2 |
| SPI | 1 |
| I2C | 2 |

- GPIO/ADC/PWM引脚
以下是Arduino用户在编程时配置和操作引脚时需要的引脚索引和开发板丝印的对应关系：

| 名称 |位置(丝印) |Arduino编程索引   | 描述 |
| -------- |------ |----------------------- |---|
| LED | 板载LED | LED_BUILTIN | 板载LED |
| 按键 | 按键| PIN_PUSH_BUTTON | 用户按键|
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

- UART引脚
UART0引脚连接了USB转UART芯片，端口丝印为USB_DEBUG.

| 功能      | 位置   |
| --------- | ------ |
| UART3.TXD | J3[8]  |
| UART3.RXD | J3[10] |
| UART0.TXD | J3[36] |
| UART0.RXD | J3[38] |


- SPI引脚

| 功能      | 位置   |
| --------- | ------ |
| SPI1.CSN  | J3[24] |
| SPI1.SCLK | J3[23] |
| SPI1.MISO | J3[21] |
| SPI1.MOSI | J3[19] |

- I2C引脚

| 功能     | 位置   |
| -------- | ------ |
| I2C2.SCL | J3[5] |
| I2C2.SDA | J3[3] |

## 编程器和调试支持
### 编程器

支持JLink和CMSIS_DAP/FT2232使用jtag接口将程序下载到开发板上。

### 调试

只支持CMSIS_DAP进行调试。