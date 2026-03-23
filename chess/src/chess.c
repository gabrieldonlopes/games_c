#include <stdio.h>
#include <SDL2/SDL.h>
#include "graph.h"
#include "game.h"

/* 
--------------------------------------------------------
# chess.c
#
# Description: programa de inicializacao do sistema
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

SDL_Window *window = NULL; // janela base
SDL_Renderer *renderer = NULL; // renderizador base
Cell cell[8][8];

int running = 1;
SDL_Event event;

void handleInput();
void updateGame();
void render();

int main(int argc, char* argv[]) {
    if (setupWindow(&window, &renderer) != 0) {
        return 1;
    }
    initBoard(cell);
    while (running)
    {
        handleInput();
        updateGame();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void handleInput(){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN){
            int mouse_x = event.button.x;
            int mouse_y = event.button.y;
            
            for (int row = 0; row < 8; row++){
                for (int col = 0; col < 8; col++){
                    if(!cell[row][col].oc){
                        if(mouse_x > cell[row][col].x1 && mouse_x < cell[row][col].x2 
                        && mouse_y > cell[row][col].y1 && mouse_y < cell[row][col].y2){
                            cell[row][col].oc = 1;
                            printf("cx=%d,cy=%d,row=%d,col=%d,oc=%d\n", cell[row][col].cx, cell[row][col].cy, row, col, cell[row][col].oc);
                        }
                    }
                }
            }
        }
    }
}

void updateGame(){

}

void render(){
    // limpar tela
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);
    // desenhar
    drawBoard(renderer, cell);
    // desenhar peças ocupadas
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            if(cell[row][col].oc){
                drawCenter(renderer, cell[row][col].cx, cell[row][col].cy);
            }
        }
    }
    // mostrar frame
    SDL_RenderPresent(renderer);
}

