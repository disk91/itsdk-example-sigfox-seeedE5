## Seeed LoRaE5 module (STM32WLE5) / Sigfox project template

This is a project template for Sigfox communications on Seeed LoRaE5 module based on STM32WLE5 chip. This template is based on [Disk91 IoT SDK repository](https://github.com/disk91/stm32-it-sdk).
The hardware configuration comes from CubeMX, project **ioc** file can be modified and source can be regenerated.

## Dependencies
* This template requires [ST CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) the ST-Microelectronic free IDE based on Eclipse + GCC
* This template has been tested on [Seeed LoRa E5 Dev Board](https://wiki.seeedstudio.com/LoRa_E5_Dev_Board/)

## Installation

Get project and associated submodules
 
```
git clone --recurse-submodules git@github.com:disk91/itsdk-example-sigfox-seeedE5.git
```

On the board, you can connect an FTDI on LPUART for console (device) interaction / configuration. You can connect FTDI on USART2 for logging

## Setup

The demo programme directly works transmitting a message every 10 minutes on sigfox network. It can be captured with RSA tools. 
- The default deviceID is 0x01020304
- the default deviceKey is public key

If you want to use it on the sigfox network you need to have you own deviceID and deviceKEY
