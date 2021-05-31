// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Common.h"

#include "Bitmaps.h"
#include "Sounds.h"
#include "Scenes.h"

const int16_t TitleMargin = (WIDTH - TitleBitmapWidth) / 2;

const uint16_t TitleAnimationFrames = FrameRate;
const uint16_t TitleMaxFrames = FrameRate * 15;

void initTitle()
{
    frameCount = 0;
    selectedIndex = 0;
}

SceneId updateTitle()
{
    arduboy.pollButtons();

    // Disable input for a few frames for extra de-bounce
    if (frameCount >= InputDisabledFrames)
    {
        if (arduboy.justReleased(LEFT_BUTTON))
        {
            moveSelection(TitleAnimationFrames, -1, 2);
            return SceneId::Title;
        }
        else if (arduboy.justReleased(RIGHT_BUTTON))
        {
            moveSelection(TitleAnimationFrames, 1, 2);
            return SceneId::Title;
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
                if (selectedIndex == 0 || selectedIndex == 1)
                {
                    // Start Game
                    useSetB = selectedIndex == 1;
                    sound.tone(ToggleSound, ToggleSoundDuration);
                    return SceneId::Game;

                }
                else if (selectedIndex == 2)
                {
                    // Toggle audio
                    frameCount = TitleAnimationFrames;
                    toggleSound();
                }
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
        drawX = (WIDTH / 4) - (LetterABitmapWidth / 2);
        drawY = ((HEIGHT + TitleMargin + TitleBitmapHeight + TitleMargin) / 2) - (CharBitmapHeight / 2);

        arduboy.drawBitmap(drawX, drawY, LetterABitmap, LetterABitmapWidth, CharBitmapHeight, WHITE);

        if (selectedIndex == 0)
        {
           arduboy.drawRoundRect(drawX - 2, drawY, LetterABitmapWidth + 4, CharBitmapHeight - 1, 1, WHITE); 
        }

        // Draw B button
        drawX = WIDTH - (WIDTH / 2) - (LetterBBitmapWidth / 2);
        drawY = ((HEIGHT + TitleMargin + TitleBitmapHeight + TitleMargin) / 2) - (CharBitmapHeight / 2);

        arduboy.drawBitmap(drawX, drawY, LetterBBitmap, LetterBBitmapWidth, CharBitmapHeight, WHITE);

        if (selectedIndex == 1)
        {
           arduboy.drawRoundRect(drawX - 2, drawY, LetterBBitmapWidth + 4, CharBitmapHeight - 1, 1, WHITE); 
        }

        // Draw sound button
        drawX = WIDTH - (WIDTH / 4) - ((SoundBitmapWidth + SoundBitmapWidth) / 2);
        drawY = ((HEIGHT + TitleMargin + TitleBitmapHeight + TitleMargin) / 2) - (SoundBitmapHeight / 2);

        arduboy.drawBitmap(drawX, drawY, Sound0Bitmap, SoundBitmapWidth, SoundBitmapHeight, WHITE);
        if (arduboy.audio.enabled())
        {
            arduboy.drawBitmap(drawX + SoundBitmapWidth, drawY, Sound1Bitmap, SoundBitmapWidth, SoundBitmapHeight, WHITE);
        }

        if (selectedIndex == 2)
        {    
           arduboy.drawRoundRect(drawX - 3, drawY - 3, SoundBitmapWidth + SoundBitmapWidth + 6, SoundBitmapHeight + 5, 1, WHITE); 
        }
    }
}
