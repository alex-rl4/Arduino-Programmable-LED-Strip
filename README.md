# Arduino-Programmable-LED-Strip
Arduino Programmable LED Strip
Uses a 74HC595 Shift Register IC to allow for easy LED configuration, and efficient use of Digital I/O pins. LEDs are controlled by manipulating an 8-bit binary value to achieve a large amount of patterns and animations.

Implemented a buffer on button presses to avoid skipping over settings unintentionally. The function works by taking note of the last button press and checking whether 1.5 seconds have passed since the last press. While the button is blocked, the green LED indicator is set to HIGH and when the button becomes available the green LED turns OFF.

More settings can be easily programmed by editing the value of the constant integer "totalSettings" and programming your desired loop.

74HC595 Shift Register IC:

Serial Data Input (DS) pin connects to Digital pin 12 of Arduino.

Shift Reg Clock Input (SH_CP) pin connects to Digital pin 11 of Arduino.

Storage Reg Clock Input (ST_CP) pin connects to Digital pin 10 of Arduino.

Q0-Q7 pins output to resistors followed by LEDs.

GND and Output Enable (OE) pins are both connected to ground.

VCC and Master Reset (MR) pins are both connected to your voltage source (Arduino 5V) or (2-6 V DC).

Q7' is not required for this circuit.

**Note: Used pins are easily changeable. Simply change the values of integers "DS","SH_CP", and "ST_CP" in the ".ino" file.

Required Material:
  - Arduino Uno
  - Breadboard
  - 74HC595 Shift Register IC
  - Jumper wires
  - tactile button
  - 9 resistors (220 or 330)ohm recommended
  - 9 LEDs (one of them is used to indicate readiness of button)
