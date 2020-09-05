// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Constants.h"
#include "GameEngine.h"
#include "Scenes.h"

#define MARGIN 3
#define LIGHTSIZE 9

extern Arduboy2 arduboy;

GameEngine game;

void initGame()
{
    game.loadLevel(0);
}

SceneId updateGame()
{
    if (game.isCompleted()) 
    {
        game.loadLevel(game.getLevel()  + 1);
        return SceneId::Game;
    }

    arduboy.pollButtons();

    if (arduboy.justReleased(A_BUTTON))
    {
        game.toggleSelectedLight();
    }

    if (arduboy.justReleased(B_BUTTON))
    {
        game.loadLevel(game.getLevel());
    }

    if (arduboy.justReleased(UP_BUTTON))
    {
        game.selectLight(game.getSelectedX(), game.getSelectedY() - 1);
    }

    if (arduboy.justReleased(DOWN_BUTTON))
    {
        game.selectLight(game.getSelectedX(), game.getSelectedY() + 1);
    }

    if (arduboy.justReleased(LEFT_BUTTON))
    {
        game.selectLight(game.getSelectedX() - 1, game.getSelectedY());
    }

    if (arduboy.justReleased(RIGHT_BUTTON))
    {
        game.selectLight(game.getSelectedX() + 1, game.getSelectedY());
    }

    return SceneId::Game;
}

void drawGame()
{
    arduboy.clear();

    for (int8_t x = 0; x < PUZZLESIZE; x++)
    {
        for (int8_t y = 0; y < PUZZLESIZE; y++)
        {
            if (x == game.getSelectedX() && y == game.getSelectedY())
            {
                arduboy.drawRect(x * (MARGIN + LIGHTSIZE) - 2, y * (MARGIN + LIGHTSIZE) - 2, LIGHTSIZE + 4, LIGHTSIZE + 4, WHITE);
            }

            bool lit = game.getLight(x, y);
            if (lit)
            {
                arduboy.fillRect(x * (MARGIN + LIGHTSIZE), y * (MARGIN + LIGHTSIZE), LIGHTSIZE, LIGHTSIZE, WHITE);
            }
            else
            {
                arduboy.drawRect(x * (MARGIN + LIGHTSIZE), y * (MARGIN + LIGHTSIZE), LIGHTSIZE, LIGHTSIZE, WHITE);
            }
        }
    }

    arduboy.setCursor(70, 10);
    arduboy.println(F("LVL:"));

    arduboy.setCursor(100, 10);
    arduboy.println(game.getLevel() + 1, DEC);

    arduboy.setCursor(70, 20);
    arduboy.println(F("MOV:"));

    arduboy.setCursor(100, 20);
    arduboy.println(game.getMoves(), DEC);

    arduboy.setCursor(70, 30);
    arduboy.println(F("PAR:"));

    arduboy.setCursor(100, 30);
    arduboy.println(game.getPar(), DEC);
}
