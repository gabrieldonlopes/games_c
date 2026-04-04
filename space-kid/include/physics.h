#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "game.h"

#define GRAVITY 500

int updatePlayerPosition(player_s *player, float delta);
int checkCollision(SDL_Rect *a, SDL_Rect *b);

#endif
