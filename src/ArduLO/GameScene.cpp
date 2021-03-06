// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include <limits.h>

#include "Common.h"

#include "Bitmaps.h"
#include "Sounds.h"
#include "GameEngine.h"
#include "Scenes.h"

const uint16_t LevelCompleteAnimationFrames = FrameRate / 2;

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

GameEngine game;

uint16_t score;
bool useSetB;

enum GameModeId : uint8_t
{
    Play,
    Paused,
    LevelComplete,
    GameComplete,
};

GameModeId currentGameModeId;

void initGame()
{
    frameCount = 0;
    selectedIndex = 0;
    currentGameModeId = GameModeId::Play;
    game.loadLevel(0, useSetB);
    score = 0;
}

void moveSelectedLight(const int8_t dx, const int8_t dy)
{
    frameCount = 0;
    if (game.selectLight(game.getSelectedX() + dx, game.getSelectedY() + dy))
    {
        sound.tone(MoveSound, MoveSoundDuration);
    }
}

SceneId updateGame()
{
    // Game Mode Init
    if (frameCount == 0)
    {
        if (currentGameModeId == GameModeId::LevelComplete)
        {
            switch(game.getHalfStars())
            {
            case 1:
                sound.tones(LevelComplete1Sound);
                break;
            case 2:
                sound.tones(LevelComplete2Sound);
                break;
            case 3:
                sound.tones(LevelComplete3Sound);
                break;
            case 4:
                sound.tones(LevelComplete4Sound);
                break;
            case 5:
                sound.tones(LevelComplete5Sound);
                break;
            case 6:
                sound.tones(LevelComplete6Sound);
                break;
            }
        }
        else if (currentGameModeId == GameModeId::GameComplete)
        {
            sound.tones(GameCompleteSound);
        }
    }

    // Process Inputs
    arduboy.pollButtons();

    // Disable input for a few frames for extra de-bounce
    if (frameCount >= InputDisabledFrames)
    {
        if (currentGameModeId == GameModeId::Play)
        {
            if (game.isCompleted())
            {
                // Go to level complete
                frameCount = 0;
                selectedIndex = 0;
                currentGameModeId = GameModeId::LevelComplete;
                return SceneId::Game;
            }

            // Check up-down directionals
            if (arduboy.pressed(UP_BUTTON))
            {
                moveSelectedLight(0, -1);
                return SceneId::Game;
            }
            else if (arduboy.pressed(DOWN_BUTTON))
            {
                moveSelectedLight(0, 1);
                return SceneId::Game;
            }

            // Check left-right directionals
            if (arduboy.pressed(LEFT_BUTTON))
            {
                moveSelectedLight(-1, 0);
                return SceneId::Game;
            }
            else if (arduboy.pressed(RIGHT_BUTTON))
            {
                moveSelectedLight(1, 0);
                return SceneId::Game;
            }

            // Check buttons
            if (arduboy.justReleased(B_BUTTON))
            {
                frameCount = 0;
                game.toggleSelectedLight();
                sound.tone(ToggleSound, ToggleSoundDuration);
                return SceneId::Game;
            }
            else if (arduboy.justReleased(A_BUTTON))
            {
                // Pause game
                frameCount = 0;
                selectedIndex = 0;
                sound.tone(ToggleSound, ToggleSoundDuration);
                currentGameModeId = GameModeId::Paused;
                return SceneId::Game;
            }
        }
        else if (currentGameModeId == GameModeId::Paused)
        {
            // Check buttons
            if (arduboy.justReleased(LEFT_BUTTON))
            {
                moveSelection(0, -1, 2);
                return SceneId::Game;
            }
            else if (arduboy.justReleased(RIGHT_BUTTON))
            {
                moveSelection(0, 1, 2);
                return SceneId::Game;
            }

            if (arduboy.justReleased(A_BUTTON))
            {
                // Unpause game
                frameCount = 0;
                sound.tone(ToggleSound, ToggleSoundDuration);
                currentGameModeId = GameModeId::Play;
                return SceneId::Game;
            }
            else if (arduboy.justReleased(B_BUTTON))
            {
                frameCount = 0;
                sound.tone(ToggleSound, ToggleSoundDuration);
                if (selectedIndex == 0)
                {
                    // Unpause game
                    currentGameModeId = GameModeId::Play;
                }
                else if (selectedIndex == 1)
                {
                    // Reset puzzle
                    currentGameModeId = GameModeId::Play;
                    game.loadLevel(game.getLevel(), useSetB);
                }
                else if (selectedIndex == 2)
                {
                    // Toggle audio
                    toggleSound();
                }
                return SceneId::Game;
            }
        }
        else if (currentGameModeId == GameModeId::LevelComplete)
        {
            if (frameCount < LevelCompleteAnimationFrames)
            {
                if (arduboy.justReleased(B_BUTTON))
                {
                    // Skip to animation end
                    frameCount = LevelCompleteAnimationFrames;
                    sound.noTone();
                    return SceneId::Game;
                }
            }
            else
            {
                // Check buttons
                if (arduboy.justReleased(LEFT_BUTTON))
                {
                    moveSelection(LevelCompleteAnimationFrames, -1, 1);
                    return SceneId::Game;
                }
                else if (arduboy.justReleased(RIGHT_BUTTON))
                {
                    moveSelection(LevelCompleteAnimationFrames, 1, 1);
                    return SceneId::Game;
                }

                if (arduboy.justReleased(B_BUTTON))
                {
                    frameCount = 0;
                    sound.tone(ToggleSound, ToggleSoundDuration);
                    if (selectedIndex == 0)
                    {
                        score += game.getHalfStars();
                        int8_t nextLevel = game.getLevel() + 1;
                        currentGameModeId = nextLevel == LevelCount ? GameModeId::GameComplete : GameModeId::Play;
                        game.loadLevel(nextLevel, useSetB);
                        
                    }
                    else if (selectedIndex == 1)
                    {
                        currentGameModeId = GameModeId::Play;
                        game.loadLevel(game.getLevel(), useSetB);
                    }
                    return SceneId::Game;
                }
            }
        }
        else if (currentGameModeId == GameModeId::GameComplete)
        {
            // Check buttons
            if (arduboy.justReleased(B_BUTTON))
            {
                // Restart game
                frameCount = 0;
                sound.noTone();
                return SceneId::Title;
            }
        }
    }

    frameCount = frameCount == USHRT_MAX ? InputDisabledFrames : frameCount + 1;

    return SceneId::Game;
}

uint8_t getBigNumberWidth(const uint8_t number)
{
    switch (number)
    {
    case 0:
        return Number0BitmapWidth;
    case 1:
        return Number1BitmapWidth;
    case 2:
        return Number2BitmapWidth;
    case 3:
        return Number3BitmapWidth;
    case 4:
        return Number4BitmapWidth;
    case 5:
        return Number5BitmapWidth;
    case 6:
        return Number6BitmapWidth;
    case 7:
        return Number7BitmapWidth;
    case 8:
        return Number8BitmapWidth;
    case 9:
        return Number9BitmapWidth;
    }
    return 0;
}

uint8_t drawBigNumber(const int16_t x, const int16_t y, const uint8_t number)
{
    switch (number)
    {
    case 0:
        arduboy.drawBitmap(x, y, Number0Bitmap, Number0BitmapWidth, CharBitmapHeight, WHITE);
        break;
    case 1:
        arduboy.drawBitmap(x, y, Number1Bitmap, Number1BitmapWidth, CharBitmapHeight, WHITE);
        break;
    case 2:
        arduboy.drawBitmap(x, y, Number2Bitmap, Number2BitmapWidth, CharBitmapHeight, WHITE);
        break;
    case 3:
        arduboy.drawBitmap(x, y, Number3Bitmap, Number3BitmapWidth, CharBitmapHeight, WHITE);
        break;
    case 4:
        arduboy.drawBitmap(x, y, Number4Bitmap, Number4BitmapWidth, CharBitmapHeight, WHITE);
        break;
    case 5:
        arduboy.drawBitmap(x, y, Number5Bitmap, Number5BitmapWidth, CharBitmapHeight, WHITE);
        break;
    case 6:
        arduboy.drawBitmap(x, y, Number6Bitmap, Number6BitmapWidth, CharBitmapHeight, WHITE);
        break;
    case 7:
        arduboy.drawBitmap(x, y, Number7Bitmap, Number7BitmapWidth, CharBitmapHeight, WHITE);
        break;
    case 8:
        arduboy.drawBitmap(x, y, Number8Bitmap, Number8BitmapWidth, CharBitmapHeight, WHITE);
        break;
    case 9:
        arduboy.drawBitmap(x, y, Number9Bitmap, Number9BitmapWidth, CharBitmapHeight, WHITE);
        break;
    }

    return getBigNumberWidth(number);
}

void drawHalfStars(const int16_t x, const int16_t y, const uint8_t halfStars)
{
    for (uint8_t star = 0; star < MaxStars; star++)
    {
        arduboy.drawBitmap(x + star * (StarBitmapSize + TextPadding), y, HalfStarMap[halfStars][star],
                            StarBitmapSize, StarBitmapSize, WHITE);
    }
}

void drawGame()
{
    arduboy.clear();

    const uint8_t displayLevel = 1 + game.getLevel();
    const uint8_t displayHalfStars = game.getHalfStars();

    const int16_t starWidth = 3 * StarBitmapSize + 2 * TextPadding;
    const int16_t starHeight = StarBitmapSize;

    const int16_t levelTextWidth = (useSetB ? LetterBBitmapWidth : LetterABitmapWidth)
                                    + (displayLevel >= 10 ? getBigNumberWidth(displayLevel / 10) : 0)
                                    + getBigNumberWidth(displayLevel % 10);
    const int16_t levelTextHeight = CharBitmapHeight;

    int16_t drawX = 0;
    int16_t drawY = 0;

    if (currentGameModeId == GameModeId::Play)
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

        // Draw display level
        drawX = (WIDTH - (WIDTH / 4)) - (levelTextWidth / 2);
        drawY = (HEIGHT / 2) - ((levelTextHeight + TextPadding + starHeight) / 2);

        if (useSetB)
        {
            arduboy.drawBitmap(drawX, drawY, LetterBBitmap, LetterBBitmapWidth, CharBitmapHeight, WHITE);
            drawX += LetterBBitmapWidth;
        }
        else
        {
            arduboy.drawBitmap(drawX, drawY, LetterABitmap, LetterABitmapWidth, CharBitmapHeight, WHITE);
            drawX += LetterABitmapWidth;
        }

        if (displayLevel >= 10)
        {
            drawX += drawBigNumber(drawX, drawY, displayLevel / 10);
        }
        drawX += drawBigNumber(drawX, drawY, displayLevel % 10);

        // Draw current stars
        drawX = (WIDTH - (WIDTH / 4)) - (starWidth / 2);
        drawY += levelTextHeight + TextPadding;

        drawHalfStars(drawX, drawY, displayHalfStars);
    }
    else if (currentGameModeId == GameModeId::Paused)
    {
        // Draw paused
        drawX = (WIDTH / 2) - (PausedBitmapWidth / 2);
        drawY = (HEIGHT / 2) - ((PausedBitmapHeight + (2 * TextPadding) + max(ResumeBitmapHeight, RetryBitmapHeight)) / 2);

        arduboy.drawBitmap(drawX, drawY, PausedBitmap, PausedBitmapWidth, PausedBitmapHeight, WHITE);

        // Draw resume button
        drawX = (WIDTH / 4) - (ResumeBitmapWidth / 2);
        drawY += PausedBitmapHeight + (2 * TextPadding);

        arduboy.drawBitmap(drawX, drawY, ResumeBitmap, ResumeBitmapWidth, ResumeBitmapHeight, WHITE);

        if (selectedIndex == 0)
        {
            arduboy.drawRoundRect(drawX - 3, drawY - 2, ResumeBitmapWidth + 6, ResumeBitmapHeight + 4, 1, WHITE);    
        }

        // Draw retry button
        drawX = WIDTH - (WIDTH / 2) - (RetryBitmapWidth / 2);
        arduboy.drawBitmap(drawX, drawY, RetryBitmap, RetryBitmapWidth, RetryBitmapHeight, WHITE);

        if (selectedIndex == 1)
        {
            arduboy.drawRoundRect(drawX - 3, drawY - 2, RetryBitmapWidth + 6, RetryBitmapHeight + 4, 1, WHITE);    
        }

        // Draw sound button
        drawX = WIDTH - (WIDTH / 4) - ((SoundBitmapWidth + SoundBitmapWidth) / 2);
        drawY += (RetryBitmapHeight - SoundBitmapHeight) / 2;

        arduboy.drawBitmap(drawX, drawY, Sound0Bitmap, SoundBitmapWidth, SoundBitmapHeight, WHITE);
        if (arduboy.audio.enabled())
        {
            arduboy.drawBitmap(drawX + SoundBitmapWidth, drawY, Sound1Bitmap, SoundBitmapWidth, SoundBitmapHeight, WHITE);
        }

        if (selectedIndex == 2)
        {    
           arduboy.drawRoundRect(drawX - 3, drawY - 3, SoundBitmapWidth + SoundBitmapWidth + 6, SoundBitmapHeight + 6, 1, WHITE); 
        }
    }
    else if (currentGameModeId == GameModeId::LevelComplete)
    {
        // Draw display level
        drawX = (WIDTH / 2) - (levelTextWidth / 2);
        drawY = (HEIGHT / 2) - ((levelTextHeight + TextPadding + starHeight + TextPadding + max(NextBitmapHeight, RetryBitmapHeight)) / 2);

        if (useSetB)
        {
            arduboy.drawBitmap(drawX, drawY, LetterBBitmap, LetterBBitmapWidth, CharBitmapHeight, WHITE);
            drawX += LetterBBitmapWidth;
        }
        else
        {
            arduboy.drawBitmap(drawX, drawY, LetterABitmap, LetterABitmapWidth, CharBitmapHeight, WHITE);
            drawX += LetterABitmapWidth;
        }

        if (displayLevel >= 10)
        {
            drawX += drawBigNumber(drawX, drawY, displayLevel / 10);
        }
        drawX += drawBigNumber(drawX, drawY, displayLevel % 10);

        // Draw final stars
        drawX = (WIDTH / 2) - (starWidth / 2);
        drawY += levelTextHeight + TextPadding;

        drawHalfStars(drawX, drawY, min(displayHalfStars, (uint8_t)boundedMap(frameCount, 0, LevelCompleteAnimationFrames, 0, MaxHalfStars)));

        if (frameCount >= LevelCompleteAnimationFrames)
        {
            // Draw next button
            drawX = (WIDTH / 4) - (NextBitmapHeight / 2);
            drawY += starHeight + TextPadding;

            arduboy.drawBitmap(drawX, drawY, NextBitmap, NextBitmapWidth, NextBitmapHeight, WHITE);

            if (selectedIndex == 0)
            {
                arduboy.drawRoundRect(drawX - 3, drawY - 2, NextBitmapWidth + 6, NextBitmapHeight + 4, 1, WHITE);    
            }

            // Draw retry button
            drawX = (WIDTH - (WIDTH / 4)) - (RetryBitmapWidth / 2);
            arduboy.drawBitmap(drawX, drawY, RetryBitmap, RetryBitmapWidth, RetryBitmapHeight, WHITE);

            if (selectedIndex == 1)
            {
                arduboy.drawRoundRect(drawX - 3, drawY - 2, RetryBitmapWidth + 6, RetryBitmapHeight + 4, 1, WHITE);    
            }
        }
    }
    else if (currentGameModeId == GameModeId::GameComplete)
    {
        // Draw ending title
        drawX = (WIDTH / 2) - ((useSetB ? LetterBBitmapWidth : LetterABitmapWidth) / 2) - ((StarBitmapSize + TextPadding) / 2) - ((StarBitmapSize + TextPadding) / 2);
        drawY = (HEIGHT / 2) - ((2 * CharBitmapHeight + TextPadding) / 2);

        if (blinkOneSecond)
        {
            arduboy.drawBitmap(drawX, drawY + ((CharBitmapHeight - StarBitmapSize) / 2), StarBitmap2, StarBitmapSize, StarBitmapSize, WHITE);
        }

        drawX += StarBitmapSize + TextPadding;
        
        if (useSetB)
        {
            arduboy.drawBitmap(drawX, drawY, LetterBBitmap, LetterBBitmapWidth, CharBitmapHeight, WHITE);
            drawX += LetterBBitmapWidth + TextPadding;
        }
        else
        {
            arduboy.drawBitmap(drawX, drawY, LetterABitmap, LetterABitmapWidth, CharBitmapHeight, WHITE);
            drawX += LetterABitmapWidth + TextPadding;
        }

        if (blinkOneSecond)
        {
            arduboy.drawBitmap(drawX, drawY + ((CharBitmapHeight - StarBitmapSize) / 2), StarBitmap2, StarBitmapSize, StarBitmapSize, WHITE);
        }

        drawY += CharBitmapHeight + TextPadding;

        const int16_t scoreTextWidth = (score >= 100 ? getBigNumberWidth(score / 100) : 0)
                                    + (score >= 10 ? getBigNumberWidth((score % 100) / 10) : 0)
                                    + getBigNumberWidth(score % 10)
                                    + SlashBitmapWidth
                                    + (PerfectScore >= 100 ? getBigNumberWidth(PerfectScore / 100) : 0)
                                    + (PerfectScore >= 10 ? getBigNumberWidth((PerfectScore % 100) / 10) : 0)
                                    + getBigNumberWidth(PerfectScore % 10);
        const int16_t scoreTextHeight = CharBitmapHeight;

        // Draw final score
        drawX = (WIDTH / 2) - (scoreTextWidth / 2);

        if (score >= 100)
        {
            drawX += drawBigNumber(drawX, drawY, score / 100);
            drawX += drawBigNumber(drawX, drawY, (score % 100) / 10);
        }
        else if (score >= 10)
        {
            drawX += drawBigNumber(drawX, drawY, score / 10);
        }
        drawX += drawBigNumber(drawX, drawY, score % 10);

        arduboy.drawBitmap(drawX, drawY, SlashBitmap, SlashBitmapWidth, CharBitmapHeight, WHITE);
        drawX += SlashBitmapWidth;

        if (PerfectScore >= 100)
        {
            drawX += drawBigNumber(drawX, drawY, PerfectScore / 100);
            drawX += drawBigNumber(drawX, drawY, (PerfectScore % 100) / 10);
        }
        else if (PerfectScore >= 10)
        {
            drawX += drawBigNumber(drawX, drawY, PerfectScore / 10);
        }
        drawX += drawBigNumber(drawX, drawY, PerfectScore % 10);
    }
}
