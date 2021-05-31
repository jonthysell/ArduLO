// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include "Common.h"

#include "Scenes.h"

SceneId currentScene;

void setup()
{
    arduboy.begin();
    arduboy.setFrameRate(FrameRate);
    arduboy.initRandomSeed();
    arduboy.audio.on();
}

void loop()
{
    if (!(arduboy.nextFrame()))
    {
        return;
    }

    SceneId nextScene;

    switch (currentScene)
    {
    case (SceneId::Title):
        nextScene = updateTitle();
        drawTitle();
        break;
    case (SceneId::Game):
        nextScene = updateGame();
        drawGame();
        break;
    }

    arduboy.display();

    if (currentScene != nextScene)
    {
        currentScene = nextScene;
        switch (currentScene)
        {
        case (SceneId::Title):
            initTitle();
            break;
        case (SceneId::Game):
            initGame();
            break;
        }
    }
}
