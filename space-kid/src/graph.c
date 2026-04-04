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

int setupWindow(SDL_Window* window,SDL_Renderer* renderer){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { // 
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "space-kid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN
    );

    if (!window) {
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    return 0;
}