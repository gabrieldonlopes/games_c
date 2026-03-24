#ifndef INPUT_H
#define GRAPH_H

#include "game.h"

void handleMouseClick(Cell cell[8][8], int mouse_x, int mouse_y, int *piece_selected, int *piece_clicked);
void resetCanMove(Cell cell[8][8]);

#endif
