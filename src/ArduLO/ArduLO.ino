// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Constants.h"
#include "Scenes.h"

Arduboy2 arduboy;

SceneId currentScene;

void setup()
{
  arduboy.begin();
  arduboy.setFrameRate(FRAMERATE);
  arduboy.initRandomSeed();
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
