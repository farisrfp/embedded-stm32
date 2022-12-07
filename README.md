# Embedded Systems Project

This is Embedded System Project, which is basic I/O, communication using UART and I2C, ADC, PWM, and etc. It uses the PlatformIO ecosystem and a custom environment to build and run the project on custom boards.

## Dependencies

- [PlatformIO Core](https://platformio.org)
- [STM32F4 Library](https://github.com/stm32duino/STM32F4)
- [ESP32/8266 Library](#)

## Environment

- Microcontroller: STM32F401CCU6 and ESP8266
- Board: 
    - Black Pill F401CC
    - NodeMCU ESP8266
- IDE: PlatformIO 5.0.3

## Getting Started

1. Install PlatformIO Core using the instructions at https://platformio.org/install
2. Clone this repository and navigate to the project directory
3. Install the dependencies using `pio lib install`
4. Build the project using `pio run`
5. Upload the project to the microcontroller using `pio run --target upload`
6. The LED should now start blinking