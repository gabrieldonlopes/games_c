#ifndef INPUT_H
#define GRAPH_H

#include "game.h"

void handleMouseClick(Cell cell[8][8], int mouse_x, int mouse_y, 
                       int *piece_selected, 
                       int *piece_clicked,
                       color_p* player_turn);

void resetCanMove(Cell cell[8][8]);

#endif
