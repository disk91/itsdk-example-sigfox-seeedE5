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

On the board, you can connect an FTDI on LPUART (9600) for console (device) interaction / configuration. You can connect FTDI on USART2 (9600) for logging

## Getting started

- This example is based on [Disk91 IoT SDK](https://github.com/disk91/stm32-it-sdk) wher you can find the documentation and more examples.
- The main program is in [project_main.c](https://github.com/disk91/itsdk-example-sigfox-seeedE5/blob/master/Core/Src/project_main.c)
- The SDK is based on configuration file for most of it's behavior, starting with [it_sdk/config.h](https://github.com/disk91/itsdk-example-sigfox-seeedE5/blob/master/Core/Inc/it_sdk/config.h)
- Interaction with device is made on serial console on LPUART, see [console documentation](https://github.com/disk91/stm32-it-sdk/blob/master/Doc/console.md)
- The console admin password is _changeme_, you can get the console command with commad **?** followed by [Enter] key

## Setup

The demo programme directly works transmitting a message every 10 minutes on sigfox network. It can be captured with RSA tools. 
- The default deviceID is 0x01020304
- the default deviceKey is public key

If you want to use it on the sigfox network you need to have your [own deviceID and deviceKEY](https://www.disk91.com/2019/technology/sigfox/murata-abz-sigfox-connectivity/)
Then you can setup these credentials into the device with the following console command:

configure Sigfox assuming
- Device ID like : 00D206AF
- Device PAC : 0000000000000000
- Device KEY : 42394514F99016C3A7334A12CFFD4A2C


```
changeme					# switch to admin mode
OK
SC:A:01						# configure for RC1 (Europe)
OK
SC:C:0000000000000000		# setup PAC
OK
SS:2:42394514F99016C3A7334A12CFFD4A2C # setup KEY
OK
SC:D:00D206AF				# setup ID
OK

```

Now you can watch the pending configuration by typing C command (Upper Case)
``` 
C
sdk.version : 17
sdk.activeNetwork : 1
sdk.activeRegion : 0000
sdk.sigfox.rcz : 1
sdk.sigfox.txPower : rcz default
sdk.sigfox.speed : rcz default
sdk.sigfox.sgfxKey : 0
sdk.sigfox.initialPac : [0000000000000000]
sdk.sigfox.deviceId : 00D206AF 
sdk.sigfox.rssiCal : 0
OK
```

Save your setup
```
S
[INFO] S 0x00000072
OK
```
