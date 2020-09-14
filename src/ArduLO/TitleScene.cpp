// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Common.h"
#include "Bitmaps.h"
#include "Scenes.h"

const uint8_t TitleMargin = 4;

const uint16_t TitleAnimationFrames = FrameRate * 2;
const uint16_t TitleMaxFrames = FrameRate * 30;

void initTitle()
{
    frameCount = 0;
}

SceneId updateTitle()
{
    arduboy.pollButtons();
    
    if (arduboy.justReleased(A_BUTTON | B_BUTTON))
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

    frameCount = (frameCount + 1) % TitleMaxFrames;

    return SceneId::Title;
}

void drawTitle()
{
    arduboy.clear();

    arduboy.drawBitmap(TitleMargin, TitleMargin - (TitleAnimationFrames - min(frameCount, TitleAnimationFrames)), TitleBitmap, TitleBitmapWidth, TitleBitmapHeight, WHITE);

    if (frameCount > TitleAnimationFrames && blinkOneSecond)
    {
        arduboy.setTextSize(1);

        arduboy.setCursor((WIDTH - getTextWidth(StringLength(PressToStartString))) / 2, HEIGHT - (TitleMargin + getTextHeight()));

        arduboy.println(F(PressToStartString));
    }
}
