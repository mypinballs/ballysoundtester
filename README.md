# Bally Sound Board Tester

Copyright 2015-2019 myPinballs Electronics, Orange Cloud Software Ltd

Written by Jim Askey

A Library and Sketch to allow control and testing of a range of Bally Pinball Sound Boards including the AS-2518-51 Computer Sound Board & the AS-2518-61 Squawk & Talk Sound Board.

# Boards Supported

1) Computer Sound Board - AS-2518-51
2) Squawk & Talk Sound Board - AS-2518-61
3) Cheap Squeak Sound Board - A080-91603-B000
4) Turbo Cheap Squeak - A080-91855-E000
5) Sounds Deluxe (Sounds Good) Sound Board - A080-91864-C000


To select the sound board in use in the sketch use the following defines in the constructor:

1) Computer Sound Board

CSB
CSB6
COMPUTER_SOUND_BOARD
COMPUTER_SOUND_BOARD_6

2) Computer Sound Board 7 Digit

CSB7
COMPUTER_SOUND_BOARD_7

3) Squawk & Talk Sound Board

SANDT
SQUAWK_AND_TALK

4) Cheap Squeak Sound Board

CS
CHEAP_SQUEAK
NASTY

5) Turbo Cheap Squeak

TURBO_CHEAP_SQUEAK
TCS 

6) Sounds Deluxe (Sounds Good) Sound Board

SOUNDS_DELUXE
SOUNDS_GOOD
SD
BIG_68000_MONSTER


# Control

Commands to control the sound board via the serial monitor are:

p xx where xx is the sound id - Plays the single sound then stops. If the sound is a continuous sound then the sound will play forever until manually stopped using the stop id for the roms. Usually id 0 so p 0

f - Play the sounds one at a time incrementing by 1 each time.

r - Play the sounds one at a time decreasing by 1 each time

s - Stop the auto inc/dec of sound ids and remain at the last id played


We hope this set fo tools is useful. We built this software to aid our own repair original sound boards and the recreation of embedded controller products for bally pinball games .myPinballs Electronics
