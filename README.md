# AVR-MLX90614
A simple AVR library for the Melexis MLX90614 non-contact infrared temperature sensor.

### Table of Contents
 * [Dependencies](#dependencies)
 * [Building](#building)
 * [Demo](#demo)
 * [Credits](#credits)

---

##### Dependencies

In order to build this library, you must have the following applications installed on your system:

 - make
 - avr-g++
 - avr-binutils
 - avr-libc

##### Building

When building this project, use the included Makefile by invoking the following command in your terminal:

`make`

Upon completion, lib/libMLX90614.a will have been generated!

##### Demo

Included with the source for this library is a small demo application that can be built using the following command:

`make all`

Upon completion, bin/MLX90614_demo.hex will have been generated!
This file can be flashed onto the AVR of your choice using avrdude or some alternative.

##### Credits

Big thanks to [scttnlsn](https://github.com/scttnlsn) for the AVR TWI HAL. The rest of the code has been written by me and is licensed using the GPLv2 license. Note that this software comes with NO WARRANTY and I am NOT LIABLE for any problems with the software. With that being said, feel free to submit issues as they are encountered.
