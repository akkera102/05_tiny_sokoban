#!/bin/bash

export avrdudeconf=/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf
export uart=/dev/tty.usbmodem1421
export hexfile=test_arduboy_10.hex

avrdude -C${avrdudeconf} -v -patmega32u4 -cavr109 -P${uart} -b57600 -D -Uflash:w:${hexfile}:i
