#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "defs.h"
#include "game.h"

int setupWindow(SDL_Window **window, SDL_Renderer **renderer);
void drawBackground(SDL_Renderer *renderer);
void drawGround(SDL_Renderer *renderer, Plataform plat[MAX_PLATFORMS], int screen);
void drawPlayer(SDL_Renderer *renderer, player_s *player);
void drawFire(SDL_Renderer *renderer, player_s *player);
void initPlataforms(Plataform plat[MAX_PLATFORMS]);

#endif
