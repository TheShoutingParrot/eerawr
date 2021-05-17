# eerawr

EEprom Read And WRite


eerawr is a program for the raspberry pi for reading data from and writing data to an AT28C256 eeprom. eerawr uses the [shiftr](https://github.com/TheShoutingParrot/shiftr) library for controlling the shift registers (for the ROM's address) and the [bcm2835](https://www.airspayce.com/mikem/bcm2835/) library for controlling the gpio pins.


To use eerawr you must connect your raspberry pi's gpio pins to a 16(/15)-bit shift register or 2 8-bit shift registers that are connected to eachother, these shift registers must be connected to the ROMs address pins. The gpios must also be directly connected to the ROMs I/O pins. The program's pins are se in the [include/eerawr.h](include/eerawr.h) header file.

## Compilation and installation

To compile eerawr, run `make` in this directory which will create an executable called "eerawr". To install just run `make install`. This will install the program to PREFIX/bin. The PREFIX variable is set in the [Makefile](Makefile).

## Usage

eerawr must be given a command to do something to the eeprom (write to it, read from it, etc). 

Here's a list of commands for eerawr:
|command |arguments |description|
|--- | --- | ---|
|`read` |-a ADDRESS |reads a byte from ADDRESS|
|`write DATA`|-a ADDRESS |writes byte DATA to ADDRESS|
|`readall` |-a ADDRESS, -m MAX -f FILE |reads all the data in the ROM from ADDRESS to MAX and writes the data to the FILE, if a file has been provided. ADDRESS and MAX are optional arguments too|
|`writefile` |-f FILE |writes the data in the FILE to the eeprom|

There's also the `-h` argument, which provides additional help for using eerawr.

### Usage examples

`eerawr read -a 0x0100`

This reads a byte from address 0x0100 and prints it as hex.


`eerawr write 0x88 -a 0x0020`

This command writes 0x88 to address 0x0020.


`eerawr readall -f rom.bin`

This command reads everything from the eeprom and puts it into the rom.bin file.


`eerawr writefile -f rom.txt`

This command writes the contents of rom.txt to the eeprom.
