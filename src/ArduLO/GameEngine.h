// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Arduino.h"

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

const int8_t PuzzleSize = 5;
const int8_t LevelCount = 50;

const uint8_t MaxStars = 3;
const uint8_t AvgStars = 2;
const uint8_t MinStars = 1;

const uint8_t PerfectScore = LevelCount * MaxStars;

class GameEngine
{
    public:
        GameEngine();

        void loadLevel(const int8_t level);

        bool getLight(const int8_t x, const int8_t y);

        void selectLight(const int8_t x, const int8_t y);
        void toggleSelectedLight();

        bool isCompleted();

        int8_t getSelectedX() { return m_selectedX; }
        int8_t getSelectedY() { return m_selectedY; }

        int8_t getLevel() { return m_level; }
        uint16_t getPar() { return m_par; }
        uint16_t getMoves() { return m_moves; }

        uint8_t getStars();
    
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
