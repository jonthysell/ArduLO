// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Common.h"
#include "Bitmaps.h"
#include "GameEngine.h"
#include "Scenes.h"

uint16_t LevelCompleteAnimationFrames = 0;

const uint8_t PlayfieldMargin = 2;
const uint8_t PlayfieldX = PlayfieldMargin;
const uint8_t PlayfieldY = PlayfieldMargin;
const uint8_t PlayfieldWidth = (WIDTH / 2) - (2 * PlayfieldMargin);
const uint8_t PlayfieldHeight = HEIGHT - (2 * PlayfieldMargin);

const uint8_t LightPadding = 3;

const uint8_t TextPadding = 4;

#define LevelString "LEVEL"
#define MinMovesString "MIN MOVES"
#define PausedString "PAUSED"
#define CompleteString "COMPLETE"
#define PerfectString "PERFECT"
#define ScoreString "SCORE"

#define PressAToContinueString "(A) - CONTINUE"
#define PressBToRetryString "(B) - RETRY"

extern Arduboy2 arduboy;

GameEngine game;

uint16_t score;

enum GameModeId : uint8_t {
    LoadLevel,
    Play,
    Paused,
    LevelComplete,
};

GameModeId currentGameModeId;

void initGame()
{
    frameCount = 0;
    currentGameModeId = GameModeId::LoadLevel;
    game.loadLevel(0);
    score = 0;
}

SceneId updateGame()
{
    arduboy.pollButtons();

    if (currentGameModeId == GameModeId::LoadLevel)
    {
        if (arduboy.justReleased(A_BUTTON))
        {
            // Animation end, go to game
            frameCount = 0;
            currentGameModeId = GameModeId::Play;
            return SceneId::Game;
        }
    }
    else if (currentGameModeId == GameModeId::Play)
    {
        if (game.isCompleted()) 
        {
            // Go to level complete
            frameCount = 0;
            currentGameModeId = GameModeId::LevelComplete;
            return SceneId::Game;
        }

        if (arduboy.justReleased(A_BUTTON))
        {
            game.toggleSelectedLight();
        }

        if (arduboy.justReleased(B_BUTTON))
        {
            // Pause game
            frameCount = 0;
            currentGameModeId = GameModeId::Paused;
            arduboy.setFrameRate(PausedFrameRate);
            return SceneId::Game;
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
    }
    else if (currentGameModeId == GameModeId::Paused)
    {
        if (arduboy.justReleased(A_BUTTON))
        {
            // Unpause game
            frameCount = 0;
            currentGameModeId = GameModeId::Play;
            arduboy.setFrameRate(FrameRate);
            return SceneId::Game;
        }

        if (arduboy.justReleased(B_BUTTON))
        {
            // Reset puzzle
            frameCount = 0;
            currentGameModeId = GameModeId::Play;
            game.loadLevel(game.getLevel());
            arduboy.setFrameRate(FrameRate);
            return SceneId::Game;
        }
    }
    else if (currentGameModeId == GameModeId::LevelComplete)
    {
        if (frameCount < LevelCompleteAnimationFrames)
        {
            if (arduboy.justReleased(A_BUTTON | B_BUTTON))
            {
                // Skip to animation end
                frameCount = LevelCompleteAnimationFrames;
            }
        }
        else
        {
            if (arduboy.justReleased(A_BUTTON))
            {
                // Go to next level
                frameCount = 0;
                currentGameModeId = GameModeId::LoadLevel;
                score += game.getStars();
                game.loadLevel(game.getLevel() + 1);
                return SceneId::Game;
            }
            
            if (arduboy.justReleased(B_BUTTON))
            {
                // Retry level
                frameCount = 0;
                currentGameModeId = GameModeId::LoadLevel;
                game.loadLevel(game.getLevel());
                return SceneId::Game;
            }
        }
    }

    frameCount++;

    return SceneId::Game;
}

void drawGame()
{
    arduboy.clear();

    uint8_t displayLevel = 1 + game.getLevel();

    if (currentGameModeId == GameModeId::LoadLevel)
    {
        arduboy.setTextSize(2);
        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(LevelString) + StringLength(SpaceString) + (displayLevel >= 10 ? 2 : 1))) / 2);
        arduboy.setCursorY((HEIGHT - (4 * CharPixelHeight + 2 * TextPadding)) / 2);
        arduboy.print(F(LevelString));
        arduboy.print(F(SpaceString));
        arduboy.println(displayLevel, 10);

        uint16_t displayPar = game.getPar();

        arduboy.setTextSize(1);
        arduboy.setCursorX((WIDTH - getTextWidth((displayPar >= 10 ? 2 : 1) + StringLength(SpaceString) + StringLength(MinMovesString))) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.print(displayPar, 10);
        arduboy.print(F(SpaceString));
        arduboy.println(F(MinMovesString));

        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(PressAToContinueString))) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.print(F(PressAToContinueString));
    }
    else if (currentGameModeId == GameModeId::Play)
    {
        // Draw Playfield
        arduboy.drawRoundRect(PlayfieldX, PlayfieldY, PlayfieldWidth, PlayfieldHeight, 1, WHITE);

        for (int8_t x = 0; x < PuzzleSize; x++)
        {
            for (int8_t y = 0; y < PuzzleSize; y++)
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

        arduboy.setTextSize(1);
        arduboy.setCursorX(WIDTH - (WIDTH / 4) - getTextWidth(StringLength(LevelString) + StringLength(SpaceString) + (displayLevel >= 10 ? 2 : 1)) / 2);
        arduboy.setCursorY((HEIGHT - (4 * CharPixelHeight + 2 * TextPadding)) / 2);
        arduboy.print(F(LevelString));
        arduboy.print(F(SpaceString));
        arduboy.println(displayLevel, 10);

        uint16_t remainingMoves = game.getPar() - min(game.getPar(), game.getMoves());

        arduboy.setTextSize(2);
        arduboy.setCursorX(WIDTH - (WIDTH / 4) - getTextWidth((remainingMoves >= 10 ? 2 : 1)) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.println(remainingMoves, 10);

        arduboy.setTextSize(1);
        arduboy.setCursorX(WIDTH - (WIDTH / 4) - getTextWidth(StringLength(ScoreString) + StringLength(SpaceString) + (displayLevel >= 10 ? 2 : 1)) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.print(F(ScoreString));
        arduboy.print(F(SpaceString));
        arduboy.println(score, 10);
    }
    else if (currentGameModeId == GameModeId::Paused)
    {
        arduboy.setTextSize(2);
        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(PausedString))) / 2);
        arduboy.setCursorY((HEIGHT - (4 * CharPixelHeight + 2 * TextPadding)) / 2);
        arduboy.println(F(PausedString));

        arduboy.setTextSize(1);
        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(PressAToContinueString))) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.println(F(PressAToContinueString));

        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(PressBToRetryString))) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.println(F(PressBToRetryString));
    }
    else if (currentGameModeId == GameModeId::LevelComplete)
    {
        uint8_t displayStars = game.getStars();

        arduboy.setTextSize(1);
        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(LevelString) + StringLength(SpaceString) + (displayLevel >= 10 ? 2 : 1) + StringLength(SpaceString) + (displayStars >= MaxStars ? StringLength(PerfectString) : StringLength(CompleteString)))) / 2);
        arduboy.setCursorY((HEIGHT - (3 * CharPixelHeight + LightSize + 3 * TextPadding)) / 2);
        arduboy.print(F(LevelString));
        arduboy.print(F(SpaceString));
        arduboy.print(displayLevel, 10);
        arduboy.print(F(SpaceString));
        arduboy.println(displayStars >= MaxStars ? F(PerfectString) : F(CompleteString));

        const uint8_t px = (WIDTH - MaxStars * (LightSize + TextPadding) - TextPadding) / 2;
        const uint8_t py = arduboy.getCursorY() + TextPadding;

        for (uint8_t star = 0; star < MaxStars; star++)
        {
            arduboy.drawBitmap(px + star * (LightSize + TextPadding), py, star < displayStars ? LitBitmap : UnlitBitmap, LightSize, LightSize, WHITE);
        }
        arduboy.setCursorY(py + LightSize);

        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(PressAToContinueString))) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.println(F(PressAToContinueString));

        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(PressBToRetryString))) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.println(F(PressBToRetryString));
    }
}
