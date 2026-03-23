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
    
    int back_row[8] = {0, 2, 4, 6, 8, 4, 2, 0};

    // pretas
    for (int col = 0; col < 8; col++)
    {
        cell[1][col].oc = 1;
        cell[1][col].piece.texture = textures[10];
        cell[1][col].piece.color = 'b';

        cell[0][col].oc = 1;
        cell[0][col].piece.texture = textures[back_row[col]];
        cell[0][col].piece.color = 'b';
    }

    // brancas
    for (int col = 0; col < 8; col++)
    {
        cell[6][col].oc = 1;
        cell[6][col].piece.texture = textures[11];
        cell[6][col].piece.color = 'w';

        cell[7][col].oc = 1;
        cell[7][col].piece.texture = textures[back_row[col] + 1];
        cell[7][col].piece.color = 'w';
    }
}