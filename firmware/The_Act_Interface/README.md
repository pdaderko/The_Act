# The Act Interface Firmware
This contains a simple Arduino sketch for the Teensy 3.2 to emulate a USB keyboard (for button/switch inputs) and mouse (for spinner control).

The firmware is mostly a copy/paste from provided example sketches for a rotary encoder and button debouncing.  I even left many of the default comments to help beginners better understand the code.

This has only been tested on a Teensy 3.2, but it should work directly, or maybe with minor changes on a Teensy 4.0 (it compiles without any errors).  
I'm aware that the Teensy 3.2 has been discontinued, but I had several on-hand, so that's what I used.  I'll try a Teensy 4.0 if I end up getting one someday.

In order to build/run, you need to install the Arduino and Teensyduino software.  Then select the appropriate Teensy board from the menu, and then "Keyboard + Mouse + Joystick" under USB Type.  And finally, select Upload.

The button mapping is:
- 1 and 2 - credit
- 3, 4, and enter - start
- s - settings
- p - pause
- right arrow - skip scene
- 0 - reset game
- Esc - restart program
- f - toggles a small vertical bar at top left, not sure what it does

The spinner sensitivity is selectable using the "ROTARY DIV" button.  Clicking the button will increase the divider (decrease sensitivity) from /1 to /10.  Pressing and holding the button for >2 seconds will save the current setting to non-volatile memory.  If you hold the button when powered up, the divider will reset to the default of /1 (most sensitive).

There are two additional buttons labeled "CUSTOM1" and "CUSTOM2" which are currently undefined.  I included these to provide an option for things like shutdown, to launch an app, adjust volume, etc.  If you look at the sketch, it should be obvious where to put your custom code if you want to use these buttons.
