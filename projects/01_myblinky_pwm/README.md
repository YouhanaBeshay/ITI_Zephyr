# Zephyr Blinky PWM  example

- This is a Zephyr application that blinks the LED using a PWM signal.
- Its based on the zephyr project sample [blinky_pwm](https://github.com/zephyrproject-rtos/zephyr/tree/main/samples/basic/blinky_pwm).
---
- Check [overlay file](./boards/stm32f401cc.overlay) for helpfull comments oon understanding the how to use the dts file
- --
# Building
- move to the project directory
```bash
cd projects/01_myblinky_pwm
```
- source the venv
```bash
source ~/zephyrproject/.venv/bin/activate
```
- build the project
```bash
west build -p always -b blackpill_f401cc . --extra-dtc-overlay boards/stm32f401cc.overlay
```
- flash the project using openocd
- <small> press the reset button on the board for 1 sec then remove it </small>
```bash
west flash --runner openocd
```
- reset the board