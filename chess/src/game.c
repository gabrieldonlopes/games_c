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

void initBoard(Cell cell[8][8]) {
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            cell[row][col].oc = 0;
        }
    }
}