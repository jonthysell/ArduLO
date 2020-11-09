// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Common.h"
#include "Bitmaps.h"
#include "Scenes.h"

const int16_t TitleMargin = (WIDTH - TitleBitmapWidth) / 2;

const uint16_t TitleAnimationFrames = FrameRate;
const uint16_t TitleMaxFrames = FrameRate * 15;

const int16_t PressAToStartMargin = (WIDTH - PressAToStartBitmapWidth) / 2;

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
        if (arduboy.justReleased(A_BUTTON))
        {
            if (frameCount < TitleAnimationFrames)
            {
                // Skip to animation end
                frameCount = TitleAnimationFrames;
            }
            else
            {
                // Start Game
                useSetB = arduboy.pressed(B_BUTTON);
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

    if (frameCount > TitleAnimationFrames && blinkOneSecond)
    {
        arduboy.drawBitmap(PressAToStartMargin, HEIGHT - PressAToStartBitmapHeight - PressAToStartMargin, PressAToStartBitmap, PressAToStartBitmapWidth, PressAToStartBitmapHeight, WHITE);
    }
}
