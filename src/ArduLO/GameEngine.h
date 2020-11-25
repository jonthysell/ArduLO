// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Arduino.h"
#include "Levels.h"

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

const int8_t PuzzleSize = 5;

const uint8_t MaxStars = 3;
const uint8_t MaxHalfStars = 6;
const uint8_t MinHalfStars = 1;

const uint16_t PerfectScore = LevelCount * MaxHalfStars;

class GameEngine
{
  public:
    GameEngine();

    void loadLevel(const int8_t level, const bool setB);

    bool getLight(const int8_t x, const int8_t y);

    void selectLight(const int8_t x, const int8_t y);
    void toggleSelectedLight();

    bool isCompleted()
    {
        return m_lights == 0;
    }

    int8_t getSelectedX()
    {
        return m_selectedX;
    }
    int8_t getSelectedY()
    {
        return m_selectedY;
    }

    int8_t getLevel()
    {
        return m_level;
    }
    uint16_t getPar()
    {
        return m_par;
    }
    uint16_t getMoves()
    {
        return m_moves;
    }

    uint8_t getHalfStars();

  private:
    void toggleLight(const int8_t x, const int8_t y);

    int8_t m_level = -1;
    uint32_t m_lights = 0;

    uint16_t m_par = 0;
    uint16_t m_moves = 0;

    int8_t m_selectedX = 0;
    int8_t m_selectedY = 0;
};

#endif
