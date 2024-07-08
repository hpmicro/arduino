# SPI从机功能

- 本示例演示SPI从机收发 

- 例程会周期性接收以及发送定长数据。

## 硬件配置：
- 根据开发板的引脚索引信息，将SPI主机和SPI从机的板子连接起来。
- 两个板子必须相连双方GND进行共地，保证信号传输。
- 必须先启动SPI从机，再启动SPI主机。

[开发板引脚信息](https://github.com/hpmicro/arduino/blob/main/variants)
```
SPI-Slave Transfer Example

Slave, Hello World!!
Slave, Hello World!!
Slave, Hello World!!
Slave, Hello World!!
Slave, Hello World!!
Slave, Hello World!!
Slave, Hello World!!
Slave, Hello World!!
Slave, Hello World!!
Slave, Hello World!!
Slave, Hello World!!


```
