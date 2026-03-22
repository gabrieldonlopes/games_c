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

void handleInput();
void updateGame();
void render();

int main(int argc, char* argv[]) {
    if (setupWindow(&window, &renderer) != 0) {
        return 1;
    }

    int running = 1;
    SDL_Event event;

    drawBoard(renderer,cell);

    while (running)
    {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
    }
        }
        
        updateGame();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void handleInput(){

}

void updateGame(){

}

void render(){
    // limpar tela
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    // desenhar
    drawBoard(renderer, cell);

    // mostrar frame
    SDL_RenderPresent(renderer);
}

