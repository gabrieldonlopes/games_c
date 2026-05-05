#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "game.h"
#include <math.h>
#include "defs.h"

int checkCollision(SDL_Rect *a, SDL_Rect *b);
void handlePlatformCollision(player_s *player, Plataform plats[MAX_PLATFORMS],
                             int count, int screen, SDL_Window *window, int *running);

#endif