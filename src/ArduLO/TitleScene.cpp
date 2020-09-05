// Copyright (c) 2020 Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#include <Arduboy2.h>

#include "Constants.h"
#include "Scenes.h"

extern Arduboy2 arduboy;

void initTitle()
{

}

SceneId updateTitle()
{
    return SceneId::Game;
}

void drawTitle()
{
    arduboy.clear();
}
