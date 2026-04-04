#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h> 
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
TTF_Font *font = NULL;         // fontes
Cell board[8][8];
SDL_Texture* textures [12];

// nota: sei que é melhor usar enum, mas tenho preguiça de adaptar 
// nota2: sei também que não é legal ficar usando variaveis globais
// provavelmente o certo é 'encapsular' numa struct, ou algo do tipo
// mas honestamente: fodase

int running = 1;
SDL_Event event;

void handleInput();
void render();

// usando variavel global fds
int game_finished = 0;
int piece_select = 0;
int piece_clicked[2] = {-1,-1};
color_p player_turn = WHITE;

int main(int argc, char *argv[]){
    if (setupWindow(&window, &renderer,&font) != 0) {
        return 1;
    }

    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // permitindo opacidade
    IMG_Init(IMG_INIT_PNG);
    initTextures(renderer, textures);

    initBoard(board,textures);  

    while (running)
    {
        handleInput();
        render();
        if (game_finished) resetGame(textures, &piece_select, &player_turn, board);
    }

    destroyTextures(textures);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
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
            handleMouseClick(window,board, mouse_x, mouse_y,&piece_select,piece_clicked,&player_turn,&game_finished);
        }
        else if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.scancode == SDL_SCANCODE_D){
                debugBoard(board);
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_M){
                debugMoves(board);
            }
            if (event.key.keysym.scancode == SDL_SCANCODE_C){
                debugCell(board[piece_clicked[0]][piece_clicked[1]]);
            }

            // reset da partida
            if (event.key.keysym.scancode == SDL_SCANCODE_R){
                resetGame(textures, &piece_select, &player_turn, board);
            }
        }
    }
}

void render(){
    // limpar tela
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    // desenhar board
    drawBoard(renderer,font, board);
    
    // desenhar peças ocupadas
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            if(board[row][col].oc){
                // pegando a textura da peça baseado no seu tipo e cor
                int index = board[row][col].piece.type * 2 + board[row][col].piece.color;
                drawPiece(renderer,textures[index],
               board[row][col].cx,
               board[row][col].cy);
            }
            if (board[row][col].can_move&&board[row][col].oc){ // casa onde uma peça come a outra
                drawSelectionBox(renderer, board[row][col]);
            } else if (board[row][col].can_move){  // casa onde uma peça pode se movimentar
                fillCircle(renderer, board[row][col].cx, board[row][col].cy, 10, MOVE);
            } else if (board[row][col].can_castling){ // casa onde uma peça pode fazer castling
                fillCircle(renderer, board[row][col].cx, board[row][col].cy, 10, CASTLING);
            }
        }
    }

    // mostrar frame
    SDL_RenderPresent(renderer);
}

