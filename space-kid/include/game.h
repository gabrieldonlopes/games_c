#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

typedef struct{
    int x, y;
    float vx, vy;

    SDL_Rect rect;

    int on_ground;
    int is_alive;
} player_s;

#endif