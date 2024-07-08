# ButtonMouseControl

总共有5个gpio输入，模拟鼠标移动和点击。

## HPM5300EVK

|GPIO      |Function      |
|----      |----      |
| PIN_P1_7 | upButton |
| PIN_P1_8 | downButton |
| PIN_P1_11 | leftButton |
| PIN_P1_12 | rightButton |
| PIN_P1_10 | mouseButton |

## HPM5301EVKLITE

|GPIO      |Function      |
|----      |----      |
| PIN_J3_27 | upButton |
| PIN_J3_28 | downButton |
| PIN_J3_7 | leftButton |
| PIN_J3_8 | rightButton |
| PIN_J3_10 | mouseButton |

[开发板引脚信息](https://github.com/hpmicro/arduino/blob/main/variants)

当GPIO接高电平时，表示鼠标移动或按下。例如upButton接高电平，则鼠标向上移动。

