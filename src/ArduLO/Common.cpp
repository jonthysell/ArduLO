// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Common.h"

Arduboy2 arduboy;

uint16_t frameCount;

uint8_t getTextWidth(const uint8_t charCount)
{
    return charCount * CharPixelWidth * arduboy.getTextSize();
}

uint8_t getTextHeight()
{
    return CharPixelHeight * arduboy.getTextSize();
}
