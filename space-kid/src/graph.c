#include "graph.h"

/* 
--------------------------------------------------------
# graph.c
#
# Description: funcoes de renderização gráfica
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

const int background_color[3] = {3, 9, 43};
const int ground_color[3] = {79, 62, 33};
const int player_color[3] = {7, 82, 3};



int setupWindow(SDL_Window** window,SDL_Renderer** renderer){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { // 
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow(
        "space-kid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN
    );

    if (!*window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    /*
    if (TTF_Init() < 0) { // 
        printf("Erro ao inicializar as fontes: %s\n", SDL_GetError());
        return 1;
    }
    *font = TTF_OpenFont("assets/font.ttf", 30);
    if (!font){
        printf("Erro ao carregar fonte: %s\n", TTF_GetError());
    }
    */

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    
    return 0;
}

// todo: colocar sprites de fundo e divisão do cenário
void drawBackground(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer,
        background_color[0],
        background_color[1],
        background_color[2],
        255
    );

    SDL_Rect background_rect = {0, 0, WIDTH, HEIGHT};
    SDL_RenderFillRect(renderer,&background_rect);
}

void drawGround(SDL_Renderer *renderer, SDL_Rect* ground_rect){
    int ground_y = HEIGHT / 4;
  
    SDL_SetRenderDrawColor(renderer,
        ground_color[0], 
        ground_color[1],
        ground_color[2],
        255
    );

    SDL_Rect ground = {0, WIDTH-ground_y, WIDTH, ground_y};
    *ground_rect = ground;

    SDL_RenderFillRect(renderer,&ground);
}

void drawPlayer(SDL_Renderer *renderer, player_s *player){
    int player_size = 50;
    

    SDL_SetRenderDrawColor(renderer,
        player_color[0],
        player_color[1],
        player_color[2],
        255
    );

    SDL_Rect player_rect = {
        player->x,
        player->y, 
        player_size / 2, 
        player_size};

    player->rect = player_rect;
    SDL_RenderFillRect(renderer, &player_rect);
}