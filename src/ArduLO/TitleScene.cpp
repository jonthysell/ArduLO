// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Common.h"

#include "Bitmaps.h"
#include "Scenes.h"

const int16_t TitleMargin = (WIDTH - TitleBitmapWidth) / 2;

const uint16_t TitleAnimationFrames = FrameRate;
const uint16_t TitleMaxFrames = FrameRate * 15;

const int16_t SetXMargin = (WIDTH - SetABitmapWidth - SetBBitmapWidth) / 3;
const int16_t SetYMargin = (HEIGHT - TitleBitmapHeight - TitleMargin - TitleMargin - SetABitmapHeight) / 2;

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
            useSetB = false;
        }
        else if (arduboy.justReleased(RIGHT_BUTTON))
        {
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

    const int16_t titleX = TitleMargin;
    const int16_t titleY = (int16_t)boundedMap(frameCount, 0, TitleAnimationFrames, -TitleBitmapHeight, TitleMargin);

    arduboy.drawBitmap(titleX, titleY, TitleBitmap, TitleBitmapWidth, TitleBitmapHeight, WHITE);

    if (frameCount > TitleAnimationFrames)
    {
        const int16_t setY = (titleY + TitleBitmapHeight + TitleMargin) + SetYMargin;

        const int16_t setAX = SetXMargin;
        arduboy.drawBitmap(setAX, setY, SetABitmap, SetABitmapWidth, SetABitmapHeight, WHITE);

        const int16_t setBX = SetXMargin + SetABitmapWidth + SetXMargin;
        arduboy.drawBitmap(setBX, setY, SetBBitmap, SetBBitmapWidth, SetBBitmapHeight, WHITE);

        const int16_t highlightX = (useSetB ? setBX : setAX) - 2;
        const int16_t highlightY = setY - 2;
        arduboy.drawRoundRect(highlightX, highlightY, SetABitmapWidth + 4, SetABitmapHeight + 4, 1, WHITE);
    }
}
