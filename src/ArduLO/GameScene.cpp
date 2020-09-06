// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Common.h"
#include "Bitmaps.h"
#include "GameEngine.h"
#include "Scenes.h"

#define MARGIN 3
#define LIGHTSIZE 9

const uint8_t PlayfieldX = 2;
const uint8_t PlayfieldY = 2;
const uint8_t PlayfieldWidth = (WIDTH / 2) - (2 * PlayfieldX);
const uint8_t PlayfieldHeight = HEIGHT - (2 * PlayfieldY);

const uint8_t LightPadding = 3;

extern Arduboy2 arduboy;

GameEngine game;

void initGame()
{
    frameCount = 0;
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

    frameCount++;

    return SceneId::Game;
}

void drawGame()
{
    arduboy.clear();

    // Draw Playfield

    arduboy.drawRoundRect(PlayfieldX, PlayfieldY, PlayfieldWidth, PlayfieldHeight, 1, WHITE);

    for (int8_t x = 0; x < PUZZLESIZE; x++)
    {
        for (int8_t y = 0; y < PUZZLESIZE; y++)
        {
            const int8_t px = PlayfieldX + 1 + LightPadding + x * (LightPadding + LightSize);
            const int8_t py = PlayfieldY + 1 + LightPadding + y * (LightPadding + LightSize);

            if (x == game.getSelectedX() && y == game.getSelectedY())
            {
                arduboy.drawRoundRect(px - 2, py - 2, LightSize + 4, LightSize + 4, 1, WHITE);
            }

            arduboy.drawBitmap(px, py, game.getLight(x, y) ? LitBitmap : UnlitBitmap, LightSize, LightSize, WHITE);
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
