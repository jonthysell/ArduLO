// Copyright (c) Jon Thysell <http://jonthysell.com>
// Licensed under the MIT License.

#ifndef SCENES_H
#define SCENES_H

enum SceneId : uint8_t
{
    Title,
    Game,
};

void initTitle();
SceneId updateTitle();
void drawTitle();

void initGame();
SceneId updateGame();
void drawGame();

#endif