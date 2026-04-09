#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "defs.h"

int updatePlayerPosition(player_s *player, float delta, input *input_k, Plataform plats[MAX_PLATFORMS],
                         int count,int screen,SDL_Window *window, int *running);
int checkCollision(SDL_Rect *a, SDL_Rect *b);
void collisionPlatX(player_s *player, Plataform plats[MAX_PLATFORMS], 
                    int count, int screen,SDL_Window *window, int *running);
void collisionPlatY(player_s *player, Plataform plats[MAX_PLATFORMS], 
                    int count, int screen,SDL_Window *window, int *running);

#endif
