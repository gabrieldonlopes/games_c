#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

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

#define WIDTH 600
#define HEIGHT 600

const int background_color[3] = {207, 233, 250};
const int cell_color[2][3] = {{209, 199, 182},{122, 90, 34}};

int setupWindow(SDL_Window** window,SDL_Renderer** renderer){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { // 
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow(
        "xadrez", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN
    );

    if (!*window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    
    return 0;
}

void drawBoard(SDL_Renderer** renderer){
    int margin = 40;
    int thickness = 2;

    int board_size = WIDTH - 2 * margin;
    int cell_size = board_size / 8;

    // background
    SDL_SetRenderDrawColor(*renderer,
        background_color[0],
        background_color[1],
        background_color[2],
        255
    );
    SDL_RenderClear(*renderer);

    // pintando casas
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            if (row%2==0&&col%2==0||row%2!=0&&col%2!=0){
                SDL_SetRenderDrawColor(*renderer, // casas brancas
                cell_color[0][0],
                cell_color[0][1],
                cell_color[0][2],
                255
                );
            } else {
                SDL_SetRenderDrawColor(*renderer, // casas pretas
                cell_color[1][0],
                cell_color[1][1],
                cell_color[1][2],
                255
                ); 
            }
            SDL_Rect cell = {
                (margin + 1) + col * cell_size,
                (margin + 1) + row * cell_size,
                cell_size - 1,
                cell_size - 1,
            };

            SDL_RenderFillRect(*renderer, &cell);
        }
    }

    // cor das linhas
    SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 255); // preto

    // borda externa
    SDL_Rect border = {
        margin,
        margin,
        board_size,
        board_size
    };
    SDL_RenderDrawRect(*renderer, &border);

    // linhas internas (verticais + horizontais)
    for (int i = 1; i < 8; i++){
        int offset = i * cell_size;

        // verticais
        SDL_RenderDrawLine(*renderer,
            margin + offset, margin,
            margin + offset, margin + board_size
        );

        // horizontais
        SDL_RenderDrawLine(*renderer,
            margin, margin + offset,
            margin + board_size, margin + offset
        );
    }
    
    SDL_RenderPresent(*renderer);
}
