![ArduLO Demo](./.github/demo.gif)

# ArduLO #

ArduLO is a clone of the puzzle game [Lights Out](https://en.wikipedia.org/wiki/Lights_Out_(game)) for the [Arduboy](https://arduboy.com/).

## Build ##

To build ArduoLO from source, you'll need to install:

* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [Arduboy2 Library](https://github.com/MLXXXp/Arduboy2)
* [ArduboyTones Library](https://github.com/MLXXXp/ArduboyTones)

For more help on setting up the a Arduboy development environment, see [Learning to Program the Arduboy](https://arduboy.com/download-and-learn-arduino/).

Then, within the Arduino IDE, open src/ArduLO/ArduLO.ino, and run Sketch > Verify/Compile.

## Play ##

![ArduLO Title Screenshot](./.github/screenshots/title.gif)

ArduLO contains two sets of 50 puzzles. At the title screen you can select either set "A" or "B" with the D-Pad. Then press the B button to start the game.

![ArduLO Game Screenshot](./.github/screenshots/game.gif)

The objective is to turn off all of the lights in as few moves as possible. Use the D-Pad to select the light you want to toggle, and press the B button to toggle. Toggling a light will cause the nearby lights to toggle in the shape of a plus.

![ArduLO Paused Screenshot](./.github/screenshots/paused.gif)

Pressing the A button will pause the game. Within the pause menu you can also choose to restart the puzzle.

![ArduLO Level Done Screenshot](./.github/screenshots/leveldone.gif)

After finshing a puzzle, you'll be given a score in one to three stars. Here you can either move on to the next puzzle or retry for a better score. Try to get three stars on all 50 levels in the set!

## Errata ##

ArduLO is open-source under the MIT license.

Copyright (c) 2020-2021 Jon Thysell
