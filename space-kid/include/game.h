#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

typedef struct{
    int x;
    int y;
    float vx;
    float vy;

    SDL_Rect rect;
    int is_alive;
} player_s;

#endif