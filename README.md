# FourDigital #
Arduino program using a 4 digit 7-segment display led.

## Schema ##
![Schema](https://github.com/Otsoko/FourDigital/raw/master/FourDigital_bb.png)

## Description ##
This program reads the value of two 10k potentiometers in `A0` and `A1`, sum their values, and displays the result in a 4 digit 7-segment display led.

Digital pins `2-5` control the specific led to enable.

Four 220 ohm resistors are connected to those pins.