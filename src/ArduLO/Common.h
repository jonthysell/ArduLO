// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#ifndef COMMON_H
#define COMMON_H

const uint8_t FrameRate = 30;

const uint16_t InputDisabledFrames = FrameRate / 5;

extern Arduboy2Base arduboy;

extern uint16_t frameCount;
extern bool useSetB;

#define blinkOneSecond ((frameCount / FrameRate) % 2 == 0)

float boundedMap(const float x, const float in_min, const float in_max, const float out_min, const float out_max);

#endif
