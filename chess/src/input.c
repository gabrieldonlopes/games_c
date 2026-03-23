#include "game.h"

void handleMouseClick(Cell cell[8][8],int mouse_x,int mouse_y){
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            if(!cell[row][col].oc){
                if(mouse_x > cell[row][col].x1 && mouse_x < cell[row][col].x2 
                && mouse_y > cell[row][col].y1 && mouse_y < cell[row][col].y2){
                    cell[row][col].oc = 1;
                    //printf("cx=%d,cy=%d,row=%d,col=%d,oc=%d\n", cell[row][col].cx, cell[row][col].cy, row, col, cell[row][col].oc);
                }
            }
        }
    }
}