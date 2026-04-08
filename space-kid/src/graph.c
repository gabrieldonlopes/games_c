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

void initPlataforms(Plataform plat[MAX_PLATFORMS]){
    int i = 0;

    // screen 1

    // a
    plat[i].rect = (SDL_Rect){0, HEIGHT - 100, 200, 100};
    plat[i++].screen = 0;

    // b
    plat[i].rect = (SDL_Rect){250, HEIGHT - 100, 100, 100};
    plat[i++].screen = 0;
    
    // c
    plat[i].rect = (SDL_Rect){400, HEIGHT - 200, 200, 200};
    plat[i++].screen = 0;

    // screen 2

    // d 
    plat[i].rect = (SDL_Rect){0, HEIGHT - 200, 100, 200};
    plat[i++].screen = WIDTH;

    // e
    plat[i].rect = (SDL_Rect){200, HEIGHT - 80, 50, 80};
    plat[i++].screen = WIDTH;

    // f
    plat[i].rect = (SDL_Rect){300, HEIGHT - 270, 50, 270};
    plat[i++].screen = WIDTH;

    // g
    plat[i].rect = (SDL_Rect){300, 0, 50, 270};
    plat[i++].screen = WIDTH;

    // l
    plat[i].rect = (SDL_Rect){400, HEIGHT - 200, 200, 200};
    plat[i++].screen = WIDTH;
}


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

void drawGround(SDL_Renderer *renderer, Plataform plat[MAX_PLATFORMS],int screen){
  
    SDL_SetRenderDrawColor(renderer,
        ground_color[0], 
        ground_color[1],
        ground_color[2],
        255
    );

    for (int i = 0; i < MAX_PLATFORMS;i++)
    {
        if(plat[i].screen == screen){ // renderizando apenas plataformas que estão na tela atual
            SDL_RenderFillRect(renderer, &plat[i].rect);
        }
    }
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

void drawFire(SDL_Renderer *renderer, player_s *player){
    if(player->vy >= 0) return; // só quando estiver subindo

    int player_base = player->rect.y + player->rect.h;
    int center_x = player->rect.x + player->rect.w / 2;

    int num_rects = (-player->vy) / 70;
    if(num_rects > 8) num_rects = 8;
    if(num_rects < 1) num_rects = 1;

    int spacing = 5;     // distância entre retângulos
    int width = 15;
    int height = 3;

    SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);

    for(int i = 1; i <= num_rects; i++){
        SDL_Rect r = {
            center_x - width/2,
            player_base + i * spacing,
            width,
            height
        };

        SDL_RenderFillRect(renderer, &r);

        // próximo retângulo menor
        width *= 0.75;
    }
}