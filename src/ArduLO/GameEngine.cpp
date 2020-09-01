// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <avr/pgmspace.h>

#include "GameEngine.h"

const uint32_t LevelLights[] PROGMEM = {
    0x1A005400UL, 0x195A82B5UL, 0x18ADEF6AUL, 0x19B88360UL, 0x19BC5EEFUL,
    0xDEEAD400UL, 0x5CF8C62FUL, 0x5CAAA880UL, 0x5C7D3BEAUL, 0xDE0039CEUL,
    0x22EAD6B5UL, 0x20A76D5FUL, 0x2022AA88UL, 0x22210800UL, 0x20010040UL,
    0xE7F08421UL, 0xE7F71000UL, 0xE6455544UL, 0xE7505415UL, 0x64004400UL,
    0x2821385EUL, 0x28E8C62EUL, 0x28467000UL, 0x2B2FC400UL, 0x29E79C61UL,
    0xEF18FE31UL, 0xEE4211C4UL, 0xEFCE7000UL, 0xEE000040UL, 0xEE001000UL,
    0x331CD671UL, 0x33F1111FUL, 0x3198D508UL, 0x33EB4634UL, 0x320AC558UL,
    0x751FC544UL, 0xF60739C0UL, 0xF7555555UL, 0xF6A60C2AUL, 0x74002800UL,
    0x3A421151UL, 0x3A749D27UL, 0x38E11D71UL, 0x3AE27F60UL, 0x3B57F0AEUL,
    0xFE477DC4UL, 0xFF0917E4UL, 0xFE089220UL, 0xFF151151UL, 0xFFFFFFFFUL
};

GameEngine::GameEngine()
{
    loadLevel(0);
}

void GameEngine::loadLevel(const int8_t level)
{
    m_level = max(level, 0) % LEVELCOUNT;

    m_lights = pgm_read_dword(LevelLights + m_level);
    m_par = 6 + (m_level / 5);

    m_moves = 0;

    selectLight(0, 0);
}

bool GameEngine::getLight(const int8_t x, const int8_t y)
{
    if (x >= 0 && x < PUZZLESIZE && y >= 0 && y < PUZZLESIZE)
    {
        return bitRead(m_lights, y * PUZZLESIZE + x);
    }

    return false;
}

void GameEngine::selectLight(const int8_t x, const int8_t y)
{
    m_selectedX = max(0, min(x, PUZZLESIZE - 1));
    m_selectedY = max(0, min(y, PUZZLESIZE - 1));
}

void GameEngine::toggleSelectedLight()
{
    toggleLight(m_selectedX, m_selectedY);
    toggleLight(m_selectedX + 1, m_selectedY);
    toggleLight(m_selectedX, m_selectedY + 1);
    toggleLight(m_selectedX -1 , m_selectedY);
    toggleLight(m_selectedX, m_selectedY - 1);
    m_moves++;
}

bool GameEngine::isCompleted()
{
    for (uint8_t x = 0; x < PUZZLESIZE; x++)
    {
        for (uint8_t y = 0; y < PUZZLESIZE; y++)
        {
            if (getLight(x, y))
            {
                return false;
            }
        }
    }

    return true;
}

void GameEngine::toggleLight(const int8_t x, const int8_t y)
{
    if (x >= 0 && x < PUZZLESIZE && y >= 0 && y < PUZZLESIZE)
    {
        bitToggle(m_lights, y * PUZZLESIZE + x);
    }
}
