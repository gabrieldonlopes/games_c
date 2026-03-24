#include "game.h"

// caso o usario já tenha se movido ou clicado em outra peça
void resetCanMove(Cell cell[8][8]){
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8;col++){
            cell[row][col].can_move = 0;
        }
    }
}

void handleMouseClick(Cell cell[8][8],int mouse_x,int mouse_y,int* piece_selected){
    if ((*piece_selected)){
        resetCanMove(cell);
        *piece_selected = 0;
    }
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            if(cell[row][col].oc){
                if(mouse_x > cell[row][col].x1 && mouse_x < cell[row][col].x2 
                && mouse_y > cell[row][col].y1 && mouse_y < cell[row][col].y2){
                    showPossibleMoves(cell,row,col);
                    *piece_selected = 1;
                    return;
                }
            }
        }
    }
}