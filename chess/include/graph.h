#ifndef GRAPH_H
#define GRAPH_H

#define WIDTH 600
#define HEIGHT 600

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "game.h"


int setupWindow(SDL_Window** window, SDL_Renderer** renderer);
void drawBoard(SDL_Renderer* renderer,Cell cell [8][8]);
void drawPiece(SDL_Renderer *renderer, SDL_Texture *texture, int cx, int cy);
void initTextures(SDL_Renderer *renderer, SDL_Texture **textures);
void destroyTextures(SDL_Texture **textures);
int fillCircle(SDL_Renderer *prenderer, int x, int y, int radius,type_m type_m);
void drawSelectionBox(SDL_Renderer *renderer, Cell c);

#endif