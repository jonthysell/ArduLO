// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#ifndef COMMON_H
#define COMMON_H

#define FRAMERATE 30

const uint8_t CharPixelHeight = 8;
const uint8_t CharPixelWidth = 6;

extern Arduboy2 arduboy;

extern uint16_t frameCount;

#define blinkOneSecond ((frameCount / FRAMERATE) % 2 == 0)

uint8_t getTextWidth(const uint8_t charCount);
uint8_t getTextHeight();

#endif
