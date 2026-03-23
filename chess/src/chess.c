#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graph.h"
#include "input.h"
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
SDL_Texture* textures [12];

// nota: sei que é melhor usar enum, mas tenho preguiça de adaptar 
// nota2: sei também que não é legal ficar usando variaveis globais
// provavelmente o certo é 'encapsular' numa struct, ou algo do tipo
// mas honestamente: fodase

int running = 1;
SDL_Event event;

void handleInput();
void updateGame();
void render();

int num;

int main(int argc, char *argv[]){
    if (setupWindow(&window, &renderer) != 0) {
        return 1;
    }

    IMG_Init(IMG_INIT_PNG);
    initTextures(renderer, textures);

    initBoard(cell,textures);  

    while (running)
    {
        handleInput();
        updateGame();
        render();
    }

    destroyTextures(textures);
    SDL_DestroyWindow(window);
    IMG_Quit();
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
            num++;

            handleMouseClick(cell, mouse_x, mouse_y);
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
                drawPiece(renderer,cell[row][col].piece.texture,
               cell[row][col].cx,
               cell[row][col].cy);
            }
        }
    }
    // mostrar frame
    SDL_RenderPresent(renderer);
}

