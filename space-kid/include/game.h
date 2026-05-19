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
    BULLET,
    MONSTER
} Entity_type;

typedef enum
{
    MOVABLE,
    DAMAGE,
    GROUND,
} Plataform_type;

typedef struct {
    float last_x, last_y;
    float vx, vy;

    // limites de movimento
    int x1, y1;
    int x2, y2;
} Plataform_mov;

typedef struct
{
    float x, y;
    
    SDL_Rect rect;
    int screen;
    Plataform_type type;
    Plataform_mov mov;
} Plataform;

typedef struct{
    int x, y;
    float vx, vy;

    SDL_Rect rect;
    Plataform *current_platform;

    int on_ground;
    int fuel;
} player_s;

typedef struct{
    int x, y;
    float vx, vy;

    int screen;
    SDL_Rect rect;

    Entity_type type;
} entity;

void changeScreen(player_s *player, int *screen);
void checkDeathByFall(player_s *player, int *running, SDL_Window *window);
void checkDeathByPlataform(SDL_Window *window, int *running, Plataform plats);
int updatePlayerPosition(player_s *player, float delta, input *input_k, Plataform plats[MAX_PLATFORMS], int count,int screen,SDL_Window *window, int *running);
void updatePlatformPosition(Plataform plats[MAX_PLATFORMS], float delta);

#endif