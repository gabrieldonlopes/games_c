#ifndef GRAPH_H
#define GRAPH_H

#define WIDTH 600
#define HEIGHT 600

#include <stdio.h>
#include <SDL2/SDL.h>

int setupWindow(SDL_Window **window, SDL_Renderer **renderer);
void drawBackground(SDL_Renderer *renderer);
void drawGround(SDL_Renderer *renderer);
void drawPlayer(SDL_Renderer *renderer, int *player_position);

#endif
