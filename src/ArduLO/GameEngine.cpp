// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "GameEngine.h"

GameEngine::GameEngine()
{
}

void GameEngine::loadLevel(const int8_t level, const bool setB)
{
    m_level = boundLevel(level);

    m_lights = getLightsForLevel(m_level, setB);
    m_par = getParForLevel(m_level);

    m_moves = 0;

    selectLight(0, 0);
}

bool GameEngine::getLight(const int8_t x, const int8_t y)
{
    if (x >= 0 && x < PuzzleSize && y >= 0 && y < PuzzleSize)
    {
        return bitRead(m_lights, y * PuzzleSize + x);
    }

    return false;
}

void GameEngine::selectLight(const int8_t x, const int8_t y)
{
    m_selectedX = max(0, min(x, PuzzleSize - 1));
    m_selectedY = max(0, min(y, PuzzleSize - 1));
}

void GameEngine::toggleSelectedLight()
{
    toggleLight(m_selectedX, m_selectedY);
    toggleLight(m_selectedX + 1, m_selectedY);
    toggleLight(m_selectedX, m_selectedY + 1);
    toggleLight(m_selectedX - 1, m_selectedY);
    toggleLight(m_selectedX, m_selectedY - 1);
    m_moves++;
}

uint8_t GameEngine::getHalfStars()
{
    uint8_t halfStarsLost = m_moves <= m_par ? 0 : max(0, (1 + m_moves - m_par) / 2);
    return max(MinHalfStars, MaxHalfStars - halfStarsLost);
}

void GameEngine::toggleLight(const int8_t x, const int8_t y)
{
    if (x >= 0 && x < PuzzleSize && y >= 0 && y < PuzzleSize)
    {
        bitToggle(m_lights, y * PuzzleSize + x);
    }
}
