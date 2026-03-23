#ifndef GAME_H
#define GAME_H

typedef struct {
    int cx, cy; // centro da célula,
    int x1, y1, x2, y2; // intervalos onde o jogador pode clicar
    // adicionar peça

    int oc;
} Cell;

typedef struct {
    

} Piece;

void initBoard(Cell cell[8][8]);

#endif