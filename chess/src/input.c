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
void resetCanMove(Cell board[8][8]){
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8;col++){
            board[row][col].can_move = 0;
            board[row][col].can_castling = 0;
        }
    }
}

void handleMouseClick(Cell board[8][8], int mouse_x, int mouse_y,
                      int* piece_selected, int* piece_clicked,color_p* player_turn)
{
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            if(mouse_x > board[row][col].x1 && mouse_x < board[row][col].x2 &&
               mouse_y > board[row][col].y1 && mouse_y < board[row][col].y2){
                
                // CLICOU EM UMA CÉLULA
                if (*piece_selected){
                    // tentar mover peça
                    if(board[row][col].can_move || board[row][col].can_castling){

                        board[row][col].oc = 1;
                        board[row][col].piece = board[piece_clicked[0]][piece_clicked[1]].piece;
                        
                        if (board[row][col].piece.type == PAWN || // peças que o primeiro movimento pode ser especial
                            board[row][col].piece.type == KING ||
                            board[row][col].piece.type == ROOK
                        ){
                            board[row][col].piece.first_move = 0;
                        }

                        board[piece_clicked[0]][piece_clicked[1]].oc = 0;
                        board[piece_clicked[0]][piece_clicked[1]].piece = emptyPiece();
                        

                        // verificar se foi roque
                        if (board[row][col].can_castling && 
                            board[row][col].piece.type == KING) {

                            int oldCol = piece_clicked[1];
                            int newCol = col;

                            // roque curto (rei foi para a direita)
                            if (newCol > oldCol) {
                                // torre está à direita
                                int rookCol = 7; // coluna da torre
                                int newRookCol = newCol - 1;

                                board[row][newRookCol].oc = 1;
                                board[row][newRookCol].piece = board[row][rookCol].piece;
                                board[row][newRookCol].piece.first_move = 0;

                                board[row][rookCol].oc = 0;
                                board[row][rookCol].piece = emptyPiece();
                            }
                            // roque longo (rei foi para a esquerda)
                            else {
                                int rookCol = 0;
                                int newRookCol = newCol + 1;

                                board[row][newRookCol].oc = 1;
                                board[row][newRookCol].piece = board[row][rookCol].piece;
                                board[row][newRookCol].piece.first_move = 0;

                                board[row][rookCol].oc = 0;
                                board[row][rookCol].piece = emptyPiece();
                            }
                        }

                        // ternario de troca de jogador
                        *player_turn = (*player_turn == WHITE) ? BLACK : WHITE; 
                    }

                    resetCanMove(board);
                    *piece_selected = 0;
                    return;
                }
                else {
                    // selecionar peça
                    if(board[row][col].oc){
                        if(*player_turn != board[row][col].piece.color)
                            return;

                        showPossibleMoves(board, row, col);
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