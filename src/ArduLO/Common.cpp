// Copyright (c) Jon Thysell <http://jonthysell.com>
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

float boundedMap(float x, float in_min, float in_max, float out_min, float out_max)
{
    return min(out_max, max(out_min, ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)));
}
