// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Common.h"

Arduboy2Base arduboy;

uint16_t frameCount;

float boundedMap(const float x, const float in_min, const float in_max, const float out_min, const float out_max)
{
    return min(out_max, max(out_min, ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)));
}

