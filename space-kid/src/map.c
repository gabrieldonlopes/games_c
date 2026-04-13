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
    plat[i].rect = (SDL_Rect){0, HEIGHT - 100, 200, 100};
    plat[i].type = GROUND;
    plat[i++].screen = 0;

    // b
    plat[i].rect = (SDL_Rect){250, HEIGHT - 100, 100, 100};
    plat[i].type = GROUND;
    plat[i++].screen = 0;
    
    // c
    plat[i].rect = (SDL_Rect){400, HEIGHT - 200, 200, 200};
    plat[i].type = GROUND;
    plat[i++].screen = 0;

    // screen 2

    // d 
    plat[i].rect = (SDL_Rect){0, HEIGHT - 200, 100, 200};
    plat[i].type = GROUND;
    plat[i++].screen = WIDTH;

    // e
    plat[i].rect = (SDL_Rect){200, HEIGHT - 80, 50, 80};
    plat[i].type = MOVABLE;
    plat[i].mov = (Plataform_mov){0, 20, -1, HEIGHT - 260, -1, HEIGHT};
    plat[i++].screen = WIDTH;

    // f
    plat[i].rect = (SDL_Rect){300, HEIGHT - 250, 50, 250};
    plat[i].type = DAMAGE;
    plat[i++].screen = WIDTH;

    // g
    plat[i].rect = (SDL_Rect){300, 0, 50, 250};
    plat[i].type = DAMAGE;
    plat[i++].screen = WIDTH;

    // l
    plat[i].rect = (SDL_Rect){400, HEIGHT - 200, 200, 200};
    plat[i].type = GROUND;
    plat[i++].screen = WIDTH;
}

