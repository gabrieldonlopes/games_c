#ifndef GAME_H
#define GAME_H
#include <SDL_image.h>

typedef struct {
    SDL_Texture *texture;
    // outra abordagem útil seria pegar a texture no render
    // guardando o TYPE e COLOR aqui, e 
    // int index = piece.type * 2 + piece.color;

    // adicionar regra de movimentoint int index = piece.type * 2 + piece.color;index = piece.type * 2 + piece.color;
    
    char color; // w ou b
} Piece;

typedef struct {
    int cx, cy; // centro da célula,
    int x1, y1, x2, y2; // intervalos onde o jogador pode clicar
    Piece piece;
    int oc;
} Cell;

void initBoard(Cell cell[8][8],SDL_Texture** textures);

#endif