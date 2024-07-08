# I2C主机模式读取

- 本示例演示I2C作为主机模式读取数据。

- 例程会周期性请求读取I2C从机发送的数据。

## 硬件配置：
- 根据开发板的引脚索引信息，将I2C主机和I2C从机的板子连接起来。
- 必须先启动I2C从机，再启动I2C主机。

[开发板引脚信息](https://github.com/hpmicro/arduino/blob/main/variants)
```
I2C master read sample
hello hello hello hello hello hello hello hello hello hello 

```
