#include "game.h"
/* 
--------------------------------------------------------
# input.c
#
# Description: funcoes de logica de controle de input do jogador
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

// caso o usario já tenha se movido ou clicado em outra peça
void resetCanMove(Cell cell[8][8]){
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8;col++){
            cell[row][col].can_move = 0;
        }
    }
}

void handleMouseClick(Cell cell[8][8], int mouse_x, int mouse_y,
                      int* piece_selected, int* piece_clicked,color_p* player_turn)
{
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            if(mouse_x > cell[row][col].x1 && mouse_x < cell[row][col].x2 &&
               mouse_y > cell[row][col].y1 && mouse_y < cell[row][col].y2){
                
                // CLICOU EM UMA CÉLULA
                if (*piece_selected){
                    // tentar mover peça
                    if(cell[row][col].can_move){

                        cell[row][col].oc = 1;
                        cell[row][col].piece = cell[piece_clicked[0]][piece_clicked[1]].piece;
                        if (cell[row][col].piece.type == PAWN){
                            cell[row][col].piece.first_move = 0;
                        }

                        cell[piece_clicked[0]][piece_clicked[1]].oc = 0;
                        cell[piece_clicked[0]][piece_clicked[1]].piece = emptyPiece();
                        
                        // ternario de troca de jogador
                        *player_turn = (*player_turn == WHITE) ? BLACK : WHITE; 
                    }

                    resetCanMove(cell);
                    *piece_selected = 0;
                    return;
                }
                else {
                    // selecionar peça
                    if(cell[row][col].oc){
                        if(*player_turn != cell[row][col].piece.color)
                            return;

                        showPossibleMoves(cell, row, col);
                        piece_clicked[0] = row;
                        piece_clicked[1] = col;
                        *piece_selected = 1;
                    }
                    return;
                }
            }
        }
    }
}