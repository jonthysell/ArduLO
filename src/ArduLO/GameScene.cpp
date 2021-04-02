// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include <limits.h>

#include "Common.h"

#include "Bitmaps.h"
#include "GameEngine.h"
#include "Scenes.h"

const uint16_t LevelCompleteAnimationFrames = 0;

const uint8_t PlayfieldMargin = 2;
const uint8_t PlayfieldX = PlayfieldMargin;
const uint8_t PlayfieldY = PlayfieldMargin;
const uint8_t PlayfieldWidth = (WIDTH / 2) - (2 * PlayfieldMargin);
const uint8_t PlayfieldHeight = HEIGHT - (2 * PlayfieldMargin);

const uint8_t LightPadding = 3;

const uint8_t TextPadding = 4;

const uint8_t *HalfStarMap[][3] = {
    {StarBitmap0, StarBitmap0, StarBitmap0}, {StarBitmap1, StarBitmap0, StarBitmap0},
    {StarBitmap2, StarBitmap0, StarBitmap0}, {StarBitmap2, StarBitmap1, StarBitmap0},
    {StarBitmap2, StarBitmap2, StarBitmap0}, {StarBitmap2, StarBitmap2, StarBitmap1},
    {StarBitmap2, StarBitmap2, StarBitmap2},
};

#define LevelString "LEVEL"
#define AString "A"
#define BString "B"
#define MinMovesString "MIN MOVES"
#define PausedString "PAUSED"
#define CompleteString "COMPLETE"
#define PerfectString "PERFECT"
#define ScoreString "SCORE"
#define SlashString "/"
#define GameOverString "GAME OVER"

#define PressAToContinueString "(A) - CONTINUE"
#define PressBToRetryString "(B) - RETRY"

extern Arduboy2 arduboy;

GameEngine game;

uint16_t score;
bool useSetB;

enum GameModeId : uint8_t
{
    LoadLevel,
    Play,
    Paused,
    LevelComplete,
    GameComplete,
};

GameModeId currentGameModeId;

void initGame()
{
    frameCount = 0;
    currentGameModeId = GameModeId::LoadLevel;
    game.loadLevel(0, useSetB);
    score = 0;
}

SceneId updateGame()
{
    arduboy.pollButtons();

    // Disable input for a few frames for extra de-bounce
    if (frameCount >= InputDisabledFrames)
    {
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

            // Check up-down directionals
            if (arduboy.pressed(UP_BUTTON))
            {
                frameCount = 0;
                game.selectLight(game.getSelectedX(), game.getSelectedY() - 1);
            }
            else if (arduboy.pressed(DOWN_BUTTON))
            {
                frameCount = 0;
                game.selectLight(game.getSelectedX(), game.getSelectedY() + 1);
            }

            // Check left-right directionals
            if (arduboy.pressed(LEFT_BUTTON))
            {
                frameCount = 0;
                game.selectLight(game.getSelectedX() - 1, game.getSelectedY());
            }
            else if (arduboy.pressed(RIGHT_BUTTON))
            {
                frameCount = 0;
                game.selectLight(game.getSelectedX() + 1, game.getSelectedY());
            }

            // Check buttons
            if (arduboy.justReleased(A_BUTTON))
            {
                frameCount = 0;
                game.toggleSelectedLight();
            }
            else if (arduboy.justReleased(B_BUTTON))
            {
                // Pause game
                frameCount = 0;
                currentGameModeId = GameModeId::Paused;
                return SceneId::Game;
            }
        }
        else if (currentGameModeId == GameModeId::Paused)
        {
            // Check buttons
            if (arduboy.justReleased(A_BUTTON))
            {
                // Unpause game
                frameCount = 0;
                currentGameModeId = GameModeId::Play;
                return SceneId::Game;
            }
            else if (arduboy.justReleased(B_BUTTON))
            {
                // Reset puzzle
                frameCount = 0;
                currentGameModeId = GameModeId::Play;
                game.loadLevel(game.getLevel(), useSetB);
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
                // Check buttons
                if (arduboy.justReleased(A_BUTTON))
                {
                    // Go to next level / endgame
                    score += game.getHalfStars();
                    int8_t nextLevel = game.getLevel() + 1;

                    frameCount = 0;
                    currentGameModeId = nextLevel == LevelCount ? GameModeId::GameComplete : GameModeId::LoadLevel;
                    game.loadLevel(nextLevel, useSetB);
                    return SceneId::Game;
                }
                else if (arduboy.justReleased(B_BUTTON))
                {
                    // Retry level
                    frameCount = 0;
                    currentGameModeId = GameModeId::LoadLevel;
                    game.loadLevel(game.getLevel(), useSetB);
                    return SceneId::Game;
                }
            }
        }
        else if (currentGameModeId == GameModeId::GameComplete)
        {
            // Check buttons
            if (arduboy.justReleased(A_BUTTON))
            {
                // Restart game
                frameCount = 0;
                return SceneId::Title;
            }
        }
    }

    frameCount = frameCount == USHRT_MAX ? InputDisabledFrames : frameCount + 1;

    return SceneId::Game;
}

void drawGame()
{
    arduboy.clear();

    uint8_t displayLevel = 1 + game.getLevel();

    if (currentGameModeId == GameModeId::LoadLevel)
    {
        arduboy.setTextSize(2);
        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(LevelString) + StringLength(SpaceString) +
                                                 (useSetB ? StringLength(BString) : StringLength(AString)) +
                                                 (displayLevel >= 10 ? 2 : 1))) /
                           2);
        arduboy.setCursorY((HEIGHT - (4 * CharPixelHeight + 2 * TextPadding)) / 2);
        arduboy.print(F(LevelString));
        arduboy.print(F(SpaceString));
        arduboy.print(useSetB ? F(BString) : F(AString));
        arduboy.println(displayLevel, 10);

        uint16_t displayPar = game.getPar();

        arduboy.setTextSize(1);
        arduboy.setCursorX((WIDTH - getTextWidth((displayPar >= 10 ? 2 : 1) + StringLength(SpaceString) +
                                                 StringLength(MinMovesString))) /
                           2);
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
                const int8_t px = PlayfieldX + 1 + LightPadding + x * (LightPadding + LightBitmapSize);
                const int8_t py = PlayfieldY + 1 + LightPadding + y * (LightPadding + LightBitmapSize);

                if (x == game.getSelectedX() && y == game.getSelectedY())
                {
                    arduboy.drawRoundRect(px - 2, py - 2, LightBitmapSize + 4, LightBitmapSize + 4, 1, WHITE);
                }

                arduboy.drawBitmap(px, py, game.getLight(x, y) ? LightBitmap1 : LightBitmap0, LightBitmapSize,
                                   LightBitmapSize, WHITE);
            }
        }

        arduboy.setTextSize(1);
        arduboy.setCursorX(WIDTH - (WIDTH / 4) -
                           getTextWidth(StringLength(LevelString) + StringLength(SpaceString) +
                                        (useSetB ? StringLength(BString) : StringLength(AString)) +
                                        (displayLevel >= 10 ? 2 : 1)) /
                               2);
        arduboy.setCursorY((HEIGHT - (4 * CharPixelHeight + 2 * TextPadding)) / 2);
        arduboy.print(F(LevelString));
        arduboy.print(F(SpaceString));
        arduboy.print(useSetB ? F(BString) : F(AString));
        arduboy.println(displayLevel, 10);

        uint16_t remainingMoves = game.getPar() - min(game.getPar(), game.getMoves());

        arduboy.setTextSize(2);
        arduboy.setCursorX(WIDTH - (WIDTH / 4) - getTextWidth((remainingMoves >= 10 ? 2 : 1)) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.println(remainingMoves, 10);

        arduboy.setTextSize(1);
        arduboy.setCursorX(WIDTH - (WIDTH / 4) -
                           getTextWidth(StringLength(ScoreString) + StringLength(SpaceString) +
                                        (score >= 100 ? 3 : (score >= 10 ? 2 : 1))) /
                               2);
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
        uint8_t displayHalfStars = game.getHalfStars();

        arduboy.setTextSize(1);
        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(LevelString) + StringLength(SpaceString) +
                                                 (useSetB ? StringLength(BString) : StringLength(AString)) +
                                                 (displayLevel >= 10 ? 2 : 1) + StringLength(SpaceString) +
                                                 (displayHalfStars >= MaxHalfStars ? StringLength(PerfectString)
                                                                                   : StringLength(CompleteString)))) /
                           2);
        arduboy.setCursorY((HEIGHT - (3 * CharPixelHeight + StarBitmapSize + 3 * TextPadding)) / 2);
        arduboy.print(F(LevelString));
        arduboy.print(F(SpaceString));
        arduboy.print(useSetB ? F(BString) : F(AString));
        arduboy.print(displayLevel, 10);
        arduboy.print(F(SpaceString));
        arduboy.println(displayHalfStars >= MaxHalfStars ? F(PerfectString) : F(CompleteString));

        const uint8_t px = (WIDTH - MaxStars * (StarBitmapSize + TextPadding) - TextPadding) / 2;
        const uint8_t py = arduboy.getCursorY() + TextPadding;

        for (uint8_t star = 0; star < MaxStars; star++)
        {
            arduboy.drawBitmap(px + star * (StarBitmapSize + TextPadding), py, HalfStarMap[displayHalfStars][star],
                               StarBitmapSize, StarBitmapSize, WHITE);
        }
        arduboy.setCursorY(py + StarBitmapSize);

        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(PressAToContinueString))) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.println(F(PressAToContinueString));

        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(PressBToRetryString))) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.println(F(PressBToRetryString));
    }
    else if (currentGameModeId == GameModeId::GameComplete)
    {
        arduboy.setTextSize(2);
        arduboy.setCursorX((WIDTH - getTextWidth(StringLength(GameOverString))) / 2);
        arduboy.setCursorY((HEIGHT - (4 * CharPixelHeight + TextPadding)) / 2);
        arduboy.println(F(GameOverString));

        arduboy.setTextSize(2);
        arduboy.setCursorX(
            (WIDTH - getTextWidth((score >= 100 ? 3 : (score >= 10 ? 2 : 1)) + StringLength(SlashString) + 3)) / 2);
        arduboy.setCursorY(arduboy.getCursorY() + TextPadding);
        arduboy.print(score, 10);
        arduboy.print(F(SlashString));
        arduboy.println(PerfectScore, 10);
    }
}
