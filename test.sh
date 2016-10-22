#!/bin/bash

if [ `uname -s` = "Darwin" ]; then
	export avrdudeconf=/Applications/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf
	export uart=/dev/tty.usbmodem1421
	python -c "import serial;ser=serial.Serial('/dev/tty.usbmodem1421',1200);ser.write('');ser.close()"
else
	export avrdudeconf=/opt/arduino/tools/avr/etc/avrdude.conf
	export uart=/dev/tty.usbserial
	python -c "import serial;ser=serial.Serial('/dev/tty.usbserial',1200);ser.write('');ser.close()"
fi

export hexfile=test.hex

sleep 2
avrdude -C${avrdudeconf} -v -patmega32u4 -cavr109 -P${uart} -b57600 -D -Uflash:w:${hexfile}:i

