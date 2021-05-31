// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>
#include <ArduboyTones.h>

#ifndef COMMON_H
#define COMMON_H

const uint8_t FrameRate = 30;

const uint16_t InputDisabledFrames = FrameRate / 5;

extern Arduboy2Base arduboy;
extern ArduboyTones sound;

extern uint16_t frameCount;
extern bool useSetB;

extern int8_t selectedIndex;

#define blinkOneSecond ((frameCount / FrameRate) % 2 == 0)

void toggleSound();

void moveSelection(const uint16_t newFrameCount, const int8_t deltaIndex, const int8_t maxIndex);

float boundedMap(const float x, const float in_min, const float in_max, const float out_min, const float out_max);

#endif
