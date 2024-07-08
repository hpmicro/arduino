# ButtonMouseControl

There are a total of 5 GPIO inputs, simulating mouse movement or clicked.

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
[Board Pin Infos](https://github.com/hpmicro/arduino/blob/main/variants)

When GPIO is connected to a high level, it indicates that the mouse is moving or clicked. For example, if upButton is connected to a high level, the mouse will move up.

