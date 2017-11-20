# Arduino_PPM_Joystick
RC PPM signal to Joystick interface for wireless transmitter use in simulators etc.

Based on the code from http://code.google.com/p/read-any-ppm and added the USB features.

Requires Arduino 1.6.5 or lower (newer versions implement USB Joystick differently)
You will need the updated USB profiles (USBAPI.h and HID.cpp) to be placed in the Arduino\hardware\arduino\avr\cores\arduino folder.

Write to an arduino Pro Micro (Not Mini or Uno/Mega) or equivalent such as Freetronics Leostick or Arduino Leonardo with the Atmega32u4

Connect PPM out from RX to Pin 3 of the Arduino (must be an interrupt pin)

Program as normal.
