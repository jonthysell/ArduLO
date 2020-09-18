// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#ifndef COMMON_H
#define COMMON_H

const uint8_t FrameRate = 15;

const uint16_t InputDisabledFrames = FrameRate / 4;

const uint8_t CharPixelHeight = 8;
const uint8_t CharPixelWidth = 6;

extern Arduboy2 arduboy;

extern uint16_t frameCount;
extern bool useSetB;

#define blinkOneSecond ((frameCount / FrameRate) % 2 == 0)

#define PressToStartString "PRESS A TO START"
#define SpaceString " "
#define StringLength(STR) (sizeof(STR) - 1)

uint8_t getTextWidth(const uint8_t charCount);
uint8_t getTextHeight();

float boundedMap(float x, float in_min, float in_max, float out_min, float out_max);

#endif
