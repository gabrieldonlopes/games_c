#include <stdio.h>
#include <SDL2/SDL.h>
#include "graph.h"
#include "game.h"

void initBoard(Cell cell[8][8]) {
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            cell[row][col].oc = 0;
        }
    }
}