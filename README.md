# ArduLO #

ArduLO is a clone of the puzzle game [Lights Out](https://en.wikipedia.org/wiki/Lights_Out_(game)) for the [Arduboy](https://arduboy.com/).

## Build ##

To build ArduoLO from source, you'll need to install:

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [Arduboy2 Library](https://github.com/MLXXXp/Arduboy2)

For more help on setting up the a Arduboy development environment, see [Learning to Program the Arduboy](https://arduboy.com/download-and-learn-arduino/).

Then, within the Arduino IDE, open src/ArduLO/ArduLO.ino, and run Sketch > Verify/Compile.

## Play ##

The objective is to turn off all of the lights in as few moves as possible. Toggling a light will cause the lights directly connected to also toggle, in the shape of a plus.

Use the D-Pad to select the light you want to toggle, and press B to toggle the light. Press A to pause.

There are two sets of 50 puzzles each. Select either "Set A" or "Set B" at the title screen.

## Errata ##

ArduLO is open-source under the MIT license.

Copyright (c) 2020-2021 Jon Thysell
