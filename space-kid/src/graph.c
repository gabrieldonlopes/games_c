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
const int ground_color[3][3] = {{79, 62, 33}, // GROUND
                                {189, 28, 17}, // DAMAGE
                                {79, 62, 33}}; // MOVABLE
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

void drawGround(SDL_Renderer *renderer, Plataform plat[MAX_PLATFORMS],int screen){
    for (int i = 0; i < MAX_PLATFORMS;i++)
    {
        if(plat[i].screen == screen){ // renderizando apenas plataformas que estão na tela atual
            
            if (plat[i].type == GROUND){
                SDL_SetRenderDrawColor(renderer,
                    ground_color[0][0], 
                    ground_color[0][1],
                    ground_color[0][2],
                    255
                );
            } else if (plat[i].type == DAMAGE){
                SDL_SetRenderDrawColor(renderer,
                    ground_color[1][0], 
                    ground_color[1][1],
                    ground_color[1][2],
                    255
                );
            } else if (plat[i].type == MOVABLE){
                SDL_SetRenderDrawColor(renderer,
                    ground_color[2][0], 
                    ground_color[2][1],
                    ground_color[2][2],
                    255
                );
            }
            
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