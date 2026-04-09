#ifndef GAME_H
#define GAME_H

#include "defs.h"
#include <SDL2/SDL.h>

typedef enum
{
    NONE,
    UP,
    DOWN,
    RIGHT,
    LEFT 
    
} input;

typedef enum
{
    MOVABLE,
    DAMAGE,
    GROUND,
} Plataform_type;

typedef struct
{
    SDL_Rect rect;
    int screen;
    Plataform_type type;
} Plataform;

typedef struct{
    int x, y;
    float vx, vy;

    SDL_Rect rect;

    int on_ground;
    int fuel;
} player_s;

void changeScreen(player_s *player, int *screen);
void checkDeathByFall(player_s *player, int *running, SDL_Window *window);
void checkDeathByPlataform(SDL_Window *window, int *running, Plataform plats);

#endif