#ifndef GAME_H
#define GAME_H
#include <SDL_image.h>

typedef enum {
    BLACK,
    WHITE
} color_p;

typedef enum {
    ROOK,
    KNIGHT,
    BISHOP,
    QUEEN,
    KING,
    PAWN
} type_p;

typedef struct {
    color_p color;
    type_p type;    
} Piece;

typedef struct {
    int cx, cy; // centro da célula,
    int x1, y1, x2, y2; // intervalos onde o jogador pode clicar
    Piece piece;
    int oc;
} Cell;

void initBoard(Cell cell[8][8],SDL_Texture** textures);

#endif