// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Common.h"

#include "Bitmaps.h"
#include "Scenes.h"

const int16_t TitleMargin = (WIDTH - TitleBitmapWidth) / 2;

const uint16_t TitleAnimationFrames = FrameRate;
const uint16_t TitleMaxFrames = FrameRate * 15;

void initTitle()
{
    frameCount = 0;
}

SceneId updateTitle()
{
    arduboy.pollButtons();

    // Disable input for a few frames for extra de-bounce
    if (frameCount >= InputDisabledFrames)
    {
        if (arduboy.justReleased(LEFT_BUTTON))
        {
            frameCount = TitleAnimationFrames;
            useSetB = false;
        }
        else if (arduboy.justReleased(RIGHT_BUTTON))
        {
            frameCount = TitleAnimationFrames;
            useSetB = true;
        }

        if (arduboy.justReleased(B_BUTTON))
        {
            if (frameCount < TitleAnimationFrames)
            {
                // Skip to animation end
                frameCount = TitleAnimationFrames;
            }
            else
            {
                // Start Game
                return SceneId::Game;
            }
        }
    }

    frameCount = (frameCount + 1) % TitleMaxFrames;

    return SceneId::Title;
}

void drawTitle()
{
    arduboy.clear();

    // Draw title
    int16_t drawX = TitleMargin;
    int16_t drawY = (int16_t)boundedMap(frameCount, 0, TitleAnimationFrames, -TitleBitmapHeight, TitleMargin);

    arduboy.drawBitmap(drawX, drawY, TitleBitmap, TitleBitmapWidth, TitleBitmapHeight, WHITE);

    if (frameCount > TitleAnimationFrames)
    {
        // Draw A button
        drawX = WIDTH / 4 - (LetterABitmapWidth / 2);
        drawY = HEIGHT - (HEIGHT / 4) - (CharBitmapHeight / 2);

        arduboy.drawBitmap(drawX, drawY, LetterABitmap, LetterABitmapWidth, CharBitmapHeight, WHITE);

        if (!useSetB)
        {
           arduboy.drawRoundRect(drawX - 1, drawY, LetterABitmapWidth + 2, CharBitmapHeight - 1, 1, WHITE); 
        }

        // Draw B button
        drawX = WIDTH - (WIDTH / 4) - (LetterBBitmapWidth / 2);
        drawY = HEIGHT - (HEIGHT / 4) - ((CharBitmapHeight) / 2);

        arduboy.drawBitmap(drawX, drawY, LetterBBitmap, LetterBBitmapWidth, CharBitmapHeight, WHITE);

        if (useSetB)
        {
           arduboy.drawRoundRect(drawX - 1, drawY, LetterBBitmapWidth + 2, CharBitmapHeight - 1, 1, WHITE); 
        }
    }
}
