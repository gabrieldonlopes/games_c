#ifndef DEBUG_H
#define DEBUG_H

#include "game.h"

// imprime tabuleiro com peças
void debugBoard(Cell board[8][8]);

// imprime casas onde can_move = 1
void debugMoves(Cell board[8][8]);

// imprime dados completos de uma célula
void debugCell(Cell c);

// converte peça para caractere
char pieceToChar(Piece p, int oc);

#endif