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

int inBoard(int row, int col){
    return row >= 0 && row < 8 && col >= 0 && col < 8;
}

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
        cell[1][col].piece.first_move = 1;

        
        cell[0][col].oc = 1;
        cell[0][col].piece.color = BLACK;
        cell[0][col].piece.type = 0 + black_row[col];
        cell[0][col].piece.first_move = 1;

    }

    int white_row[8] = {0, 1, 2, 3, 4, 2, 1, 0};
    // brancas
    for (int col = 0; col < 8; col++)
    {
        // peoes
        cell[6][col].oc = 1;
        cell[6][col].piece.color = WHITE;
        cell[6][col].piece.type = PAWN;
        cell[6][col].piece.first_move = 1;
        
        // outras pecas
        cell[7][col].oc = 1;
        cell[7][col].piece.type = white_row[col];
        cell[7][col].piece.color = WHITE;
        cell[7][col].piece.first_move = 1;

    }
}

void checkDirection(Cell board[8][8], int row, int col, int dRow, int dCol){
    for (int i = 1; i < 8; i++){
        int newRow = row + i * dRow;
        int newCol = col + i * dCol;

        if (!inBoard(newRow, newCol))
            break;

        if (board[newRow][newCol].oc){
            if (board[row][col].piece.color != board[newRow][newCol].piece.color){
                board[newRow][newCol].can_move = 1;
            }
            break;
        } else {
            board[newRow][newCol].can_move = 1;
        }
    }
}

Piece emptyPiece(){
    Piece p;
    p.type = -1;
    p.color = -1;
    return p;
}

int verifyEmptyCols (Cell board[8][8],int colA,int colB,int row){
    int start,end;

    if (colA < colB)
    {
        start = colA;
        end = colB;
    }
    else
    {
        start = colB;
        end = colA;
    }

    for (int i = start+1; i < end; i++)
    {
        if (board[row][i].oc){
            return 0;
        }
    }
    return 1;
}

void verifyCastling(Cell board[8][8],int row, int col){
    if (row != 0 && row != 7) return; // caso a peça não esteja na primeira linha
    if (!board[row][col].piece.first_move) return; // caso seja seu primeiro movimento

    int mod = (board[row][col].piece.color == WHITE) ? -1:1;

    if(board[row][col].piece.type== KING){
        if (board[row][col-(3*mod)].piece.type == ROOK && 
            board[row][col-(3*mod)].piece.first_move) {
            // roque curto
            if(verifyEmptyCols(board, col, col-(3*mod),row)){
                board[row][col - (2 * mod)].can_castling = 1;
            } 


        } 
        
        if (board[row][col+(4*mod)].piece.type == ROOK && 
                   board[row][col+(4*mod)].piece.first_move){
            // roque longo
            if(verifyEmptyCols(board, col, col+(4*mod),row)) {
                board[row][col + (2 * mod)].can_castling = 1;
            }

        }
    }
}

void showPossibleMoves(Cell board[8][8],int row,int col){
    int mod = 1;
    if (board[row][col].piece.color == WHITE)
    {
        mod = -1;
    }

    switch (board[row][col].piece.type)
    {
    case ROOK:

        checkDirection(board, row, col, -1,  0); // cima
        checkDirection(board, row, col,  1,  0); // baixo
        checkDirection(board, row, col,  0,  1); // direita
        checkDirection(board, row, col,  0, -1); // esquerda

        break;
    case KNIGHT:
        int moves_k[8][2] = { // conjunto de possibilidades do cavalo
            {2,  1}, {2,  -1},
            {-2, 1}, {-2, -1},
            {1,  2}, {1,  -2},
            {-1, 2}, {-1, -2}
        };
        for (int i = 0; i < 8; i++){
            int r = row + moves_k[i][0];
            int c = col + moves_k[i][1];

            if (inBoard(r, c) && (!board[r][c].oc ||
            board[r][c].piece.color != board[row][col].piece.color)) {
                board[r][c].can_move = 1;
            }
        }

        break;
    case BISHOP:

        checkDirection(board, row, col, -1,  1); // diagonal nordeste
        checkDirection(board, row, col,  1,  1); // diagonal sudeste
        checkDirection(board, row, col,  1, -1); // diagonal sudoeste
        checkDirection(board, row, col, -1, -1); // diagonal noroeste

        break;
    case QUEEN:
        int moves_q[8][2] = { // conjunto de possibilidades da rainha
            {-1, 0}, { 1,  0},
            { 0,-1}, { 0,  1},
            {-1, 1}, { 1, -1},
            {-1,-1}, { 1,  1}
        };
        for (int i = 0; i < 8;i++){
            int r = moves_q[i][0];
            int c = moves_q[i][1];

            checkDirection(board, row, col,  r, c); 
        }

    case KING:
        // basicamente a mesma movimentação da rainha, mas sem o loop
        
        int moves_king[8][2] = { // conjunto de possibilidades do rei
            {-1, 0}, { 1,  0},
            { 0,-1}, { 0,  1},
            {-1, 1}, { 1, -1},
            {-1,-1}, { 1,  1}
        };
        
        verifyCastling(board, row, col); // verificanod possibilidade de realizar roque

        for (int i = 0; i < 8; i++){
            int r = moves_king[i][0];
            int c = moves_king[i][1];

            int newRow = row + r;
            int newCol = col + c;
            if (!inBoard(newRow, newCol))
                continue;

            if (board[newRow][newCol].oc){
                if (board[row][col].piece.color != board[newRow][newCol].piece.color){
                    board[newRow][newCol].can_move = 1;
                }
            } else {
                board[newRow][newCol].can_move = 1;
            }
        }


        break;
    case PAWN: 
        // casa da frente
        if (inBoard(row + mod, col) && !board[row + mod][col].oc){
            board[row + mod][col].can_move = 1;

            // duas casas
            if (board[row][col].piece.first_move &&
                inBoard(row + 2*mod, col) &&
                !board[row + 2*mod][col].oc){
                
                board[row + 2*mod][col].can_move = 1;
            }
        }

        // diagonal direita
        if (inBoard(row + mod, col + 1) &&
            board[row + mod][col + 1].oc &&
            board[row + mod][col + 1].piece.color != board[row][col].piece.color){
            
            board[row + mod][col + 1].can_move = 1;
        }

        // diagonal esquerda
        if (inBoard(row + mod, col - 1) &&
            board[row + mod][col - 1].oc &&
            board[row + mod][col - 1].piece.color != board[row][col].piece.color){
            
            board[row + mod][col - 1].can_move = 1;
        }

        break;
    }

};