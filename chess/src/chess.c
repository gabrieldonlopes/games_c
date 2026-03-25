#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "graph.h"
#include "input.h"
#include "game.h"
#include "debug.h"

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

// usando variavel global fds
int piece_select = 0;
int piece_clicked[2] = {-1,-1};

int main(int argc, char *argv[]){
    if (setupWindow(&window, &renderer) != 0) {
        return 1;
    }

    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // permitindo opacidade
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
        else if (event.type == SDL_MOUSEBUTTONDOWN){
            int mouse_x = event.button.x;
            int mouse_y = event.button.y;
            handleMouseClick(cell, mouse_x, mouse_y,&piece_select,piece_clicked);
        }
        else if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.scancode == SDL_SCANCODE_D){
                debugBoard(cell);
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_M){
                debugMoves(cell);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_C){
                debugCell(cell[piece_clicked[0]][piece_clicked[1]]);
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
                // pegando a textura da peça baseado no seu tipo e cor
                int index = cell[row][col].piece.type * 2 + cell[row][col].piece.color;
                drawPiece(renderer,textures[index],
               cell[row][col].cx,
               cell[row][col].cy);
            }
            if (cell[row][col].can_move&&cell[row][col].oc){  // circulo cheio e verde onde não tem peça
                drawSelectionBox(renderer, cell[row][col]);
            } else if (cell[row][col].can_move){ // circulo vazio e vermelho onde tem peça
                fillCircle(renderer, cell[row][col].cx, cell[row][col].cy, 10);
                
            }
        }
    }
    // mostrar frame
    SDL_RenderPresent(renderer);
}

