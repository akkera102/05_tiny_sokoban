Tiny Sokoban for Arduboy - Includes 52 levels 

## Description
Tiny Sokoban is Sokoban(1982) clone.
It use Yoshio Murase Levels. These levels are very small (no more than 8x8).
But difficult and interesting.

First game, I hope to you play lv3 or lv4. Lv1-2 is hell.


## Installation
Request : Arduino IDE 1.6.x

1. download from github
2. pls edit test.bat(windows) or test.sh(osx) for your computer(must change COM port number)
3. execute test.bat
4. play it


## Controls
dir : move
A   : prev (max history is 50)
B   : quit


## Solve
My project/solve.txt. Don't tell to anyone. :)
 


## Development
compiler        : windows Arduino IDE 1.6.8(avr-gcc) + 1.0.6(make.exe)
image converter : python 2.6 + PIL
etc             : Visual Studio 2015 C#


## History
v1.02 2016/05/17    support osx. thank you kubatyszko!
v1.01 2016/05/15    support arduboy 1.0
v1.00 2016/03/23    first version


## Document
Thank you keep a document. I was able to walk easily.

Level format
http://sokobano.de/wiki/

Yoshio Murase Levels
http://sneezingtiger.com/sokoban/levels.html

Sokoban Automatic Solver
http://www.ic-net.or.jp/home/takaken/e/soko/


Arduboy 1.0 infomation.

AVR Memory Usage
----------------
Device: atmega32u4

Program:   19958 bytes (60.9% Full)
(.text + .data + .bootloader)

Data:       1793 bytes (70.0% Full)
(.data + .bss + .noinit)
