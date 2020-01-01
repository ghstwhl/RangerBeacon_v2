# RangerBeacon_v2
Super simple code for lighting some APA102 LEDs for a sign.

Code has two modes, constant and pulsing, and switches between modes upon each boot.  This eliminates the need for a button or switch to set state.

Note:  State is saved via EEPROM, so there is a theoretical limit to the number of power cycles the ATTiny85 can handle before it gets stuck in default mode.

Copyright 2020 - Chris Knight - merlin@ghostwheel.com

Released under the [CC BY-NC-SA license](https://creativecommons.org/licenses/by-nc-sa/4.0/)
