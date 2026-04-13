#include "map.h"

/* 
--------------------------------------------------------
# map.c
#
# Description: conjunto de funções de manipulação e implementação do mapa
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

void initPlataforms(Plataform plat[MAX_PLATFORMS]){
    int i = 0;

    // screen 1

    // a
    plat[i].x = 0;
    plat[i].y = HEIGHT - 100;
    plat[i].rect = (SDL_Rect){(int)plat[i].x, (int)plat[i].y, 200, 100};
    plat[i].type = GROUND;
    plat[i++].screen = 0;

    // b
    plat[i].x = 250;
    plat[i].y = HEIGHT - 100;
    plat[i].rect = (SDL_Rect){(int)plat[i].x, (int)plat[i].y, 100, 100};
    plat[i].type = GROUND;
    plat[i++].screen = 0;

    // c
    plat[i].x = 400;
    plat[i].y = HEIGHT - 200;
    plat[i].rect = (SDL_Rect){(int)plat[i].x, (int)plat[i].y, 200, 200};
    plat[i].type = GROUND;
    plat[i++].screen = 0;

    // screen 2

    // d
    plat[i].x = 0;
    plat[i].y = HEIGHT - 200;
    plat[i].rect = (SDL_Rect){(int)plat[i].x, (int)plat[i].y, 100, 200};
    plat[i].type = GROUND;
    plat[i++].screen = WIDTH;

    // e (movable)
    plat[i].x = 150;
    plat[i].y = HEIGHT - 80;
    plat[i].rect = (SDL_Rect){(int)plat[i].x, (int)plat[i].y, 100, 80};
    plat[i].type = MOVABLE;
    plat[i].mov = (Plataform_mov){0, 100, -1, HEIGHT - 260, -1, HEIGHT};
    plat[i++].screen = WIDTH;

    // f
    plat[i].x = 300;
    plat[i].y = HEIGHT - 250;
    plat[i].rect = (SDL_Rect){(int)plat[i].x, (int)plat[i].y, 50, 250};
    plat[i].type = DAMAGE;
    plat[i++].screen = WIDTH;

    // g
    plat[i].x = 300;
    plat[i].y = 0;
    plat[i].rect = (SDL_Rect){(int)plat[i].x, (int)plat[i].y, 50, 250};
    plat[i].type = DAMAGE;
    plat[i++].screen = WIDTH;

    // l
    plat[i].x = 400;
    plat[i].y = HEIGHT - 200;
    plat[i].rect = (SDL_Rect){(int)plat[i].x, (int)plat[i].y, 200, 200};
    plat[i].type = GROUND;
    plat[i++].screen = WIDTH;
}
