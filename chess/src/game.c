#include <stdio.h>
#include <SDL2/SDL.h>
#include "graph.h"
#include "game.h"
/* 
--------------------------------------------------------
# game.c
#
# Description: funcoes de logica do jogo
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

void initBoard(Cell cell[8][8],SDL_Texture** textures) {
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            cell[row][col].oc = 0;
        }
    }
    
    int black_row[8] = {0, 1, 2, 4, 3, 2, 1, 0};
    // pretas
    for (int col = 0; col < 8; col++) {
        // peoes
        cell[1][col].oc = 1;
        cell[1][col].piece.color = BLACK;
        cell[1][col].piece.type = PAWN;

        
        cell[0][col].oc = 1;
        cell[0][col].piece.color = BLACK;
        cell[0][col].piece.type = 0 + black_row[col];
    }

    int white_row[8] = {0, 1, 2, 3, 4, 2, 1, 0};
    // brancas
    for (int col = 0; col < 8; col++)
    {
        // peoes
        cell[6][col].oc = 1;
        cell[6][col].piece.color = WHITE;
        cell[6][col].piece.type = PAWN;

        // outras pecas
        cell[7][col].oc = 1;
        cell[7][col].piece.type = white_row[col];
        cell[7][col].piece.color = WHITE;
    }
}

void showPossibleMoves(Cell board[8][8],int row,int col){ // recebendo o board inteiro e as coordenadas da peça que quer se mover
    // caso exemplo para peoes brancos
    if (!board[row-1][col].oc){ // caso casa da frente esteja liberada
        board[row - 1][col].can_move = 1;
        board[row - 2][col].can_move = 1;
    }
};

Piece emptyPiece(){
    Piece p;
    p.type = -1;
    p.color = -1;
    return p;
}