// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Common.h"

#include "Sounds.h"

Arduboy2Base arduboy;
ArduboyTones sound(arduboy.audio.enabled);

uint16_t frameCount;

int8_t selectedIndex;

void toggleSound()
{
    if (arduboy.audio.enabled())
    {
        arduboy.audio.off();
    }
    else
    {
        arduboy.audio.on();
    }
    sound.tone(ToggleSound, ToggleSoundDuration);
}

void moveSelection(const uint16_t newFrameCount, const int8_t deltaIndex, const int8_t maxIndex)
{
    frameCount = newFrameCount;

    int8_t oldIndex = selectedIndex;
    selectedIndex = max(0, min(maxIndex, selectedIndex + deltaIndex));
    if (oldIndex != selectedIndex)
    {
        sound.tone(MoveSound, MoveSoundDuration);
    }
}

float boundedMap(const float x, const float in_min, const float in_max, const float out_min, const float out_max)
{
    return min(out_max, max(out_min, ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)));
}

