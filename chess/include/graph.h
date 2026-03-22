#ifndef GRAPH_H
#define GRAPH_H

#define WIDTH 600
#define HEIGHT 600

#include <SDL2/SDL.h>
#include "game.h"

int setupWindow(SDL_Window** window, SDL_Renderer** renderer);
void drawBoard(SDL_Renderer* renderer,Cell cell [8][8]);
void drawCenter(SDL_Renderer *renderer, int cx, int cy);

#endif