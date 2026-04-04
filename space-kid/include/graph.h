#ifndef GRAPH_H
#define GRAPH_H

#define WIDTH 600
#define HEIGHT 600

#include <stdio.h>
#include <SDL2/SDL.h>
#include "game.h"

int setupWindow(SDL_Window **window, SDL_Renderer **renderer);
void drawBackground(SDL_Renderer *renderer);
void drawGround(SDL_Renderer *renderer, SDL_Rect* ground_rect);
void drawPlayer(SDL_Renderer *renderer, player_s *player);
void drawFire(SDL_Renderer *renderer, player_s *player);

#endif
