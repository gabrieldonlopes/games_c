#include <stdio.h>
#include "debug.h"
#include "game.h"

/* 
--------------------------------------------------------
# debug.c
#
# Description: funcoes para debugar e visualizar
# Autor: chatGPT
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

// converte peça em caractere
char pieceToChar(Piece p, int oc)
{
    if (!oc) return '.';

    char c;

    switch (p.type)
    {
        case ROOK:   c = 'R'; break;
        case KNIGHT: c = 'N'; break;
        case BISHOP: c = 'B'; break;
        case QUEEN:  c = 'Q'; break;
        case KING:   c = 'K'; break;
        case PAWN:   c = 'P'; break;
        default:     c = '?';
    }

    if (p.color == BLACK)
        c = c + 32; // minúsculo

    return c;
}

// imprime o tabuleiro
void debugBoard(Cell board[8][8])
{
    printf("\n");

    for (int row = 0; row < 8; row++)
    {
        printf("%d  ", 8 - row);

        for (int col = 0; col < 8; col++)
        {
            char c = pieceToChar(board[row][col].piece,
                                 board[row][col].oc);

            printf("%c ", c);
        }

        printf("\n");
    }

    printf("\n   a b c d e f g h\n\n");
}

// imprime movimentos possíveis
void debugMoves(Cell board[8][8])
{
    printf("\nPossible moves:\n\n");

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (board[row][col].can_move)
                printf("x ");
            else
                printf(". ");
        }
        printf("\n");
    }

    printf("\n");
}

// imprime dados completos de uma célula
void debugCell(Cell c)
{
    printf("\nCell debug info:\n");
    printf("Occupied: %d\n", c.oc);
    printf("Can move: %d\n", c.can_move);
    printf("Click area: (%d,%d) -> (%d,%d)\n", c.x1, c.y1, c.x2, c.y2);
    printf("Center: (%d,%d)\n", c.cx, c.cy);

    if (c.oc)
    {
        printf("Piece type: %d\n", c.piece.type);
        printf("Piece color: %d\n", c.piece.color);
        printf("First move: %d\n", c.piece.first_move);
    }

    printf("\n");
}