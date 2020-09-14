// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <avr/pgmspace.h>

#ifndef LEVELS_H
#define LEVELS_H

const int8_t LevelCount = 50;

#define boundLevel(x) (max(x, 0) % LevelCount)

const uint32_t LevelLights[] PROGMEM = {
    0x0005400UL,
    0x15A82B5UL,
    0x0ADEF6AUL,
    0x1B88360UL,
    0x1BC5EEFUL,
    0x0EAD400UL,
    0x0F8C62FUL,
    0x0AAA880UL,
    0x07D3BEAUL,
    0x00039CEUL,
    0x0EAD6B5UL,
    0x0A76D5FUL,
    0x022AA88UL,
    0x0210800UL,
    0x0010040UL,
    0x1F08421UL,
    0x1F71000UL,
    0x0455544UL,
    0x1505415UL,
    0x0004400UL,
    0x021385EUL,
    0x0E8C62EUL,
    0x0467000UL,
    0x12FC400UL,
    0x1E79C61UL,
    0x118FE31UL,
    0x04211C4UL,
    0x1CE7000UL,
    0x0000040UL,
    0x0001000UL,
    0x11CD671UL,
    0x1F1111FUL,
    0x198D508UL,
    0x1EB4634UL,
    0x00AC558UL,
    0x11FC544UL,
    0x00739C0UL,
    0x1555555UL,
    0x0A60C2AUL,
    0x0002800UL,
    0x0421151UL,
    0x0749D27UL,
    0x0E11D71UL,
    0x0E27F60UL,
    0x157F0AEUL,
    0x0477DC4UL,
    0x10917E4UL,
    0x0089220UL,
    0x1151151UL,
    0x1FFFFFFUL,
};

static uint32_t getLightsForLevel(const int8_t level)
{
    return pgm_read_dword(LevelLights + boundLevel(level));
}

static uint16_t getParForLevel(const int8_t level)
{
    return 6 + (boundLevel(level) / 5);
}

#endif
