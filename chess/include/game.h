#ifndef GAME_H
#define GAME_H
#include <SDL_image.h>

typedef enum {
    BLACK,
    WHITE
} color_p;

typedef enum {
    MOVE,
    CASTLING,
    PROMOTION
} type_m;

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
    int first_move;
} Piece;

typedef struct {
    int cx, cy; // centro da célula,
    int x1, y1, x2, y2; // intervalos onde o jogador pode clicar
    Piece piece; // peça que ocupa a casa
    int oc; // ocupada ou não
    int can_move;
    int can_castling;
} Cell;

int inBoard(int row, int col);
void initBoard(Cell cell[8][8], SDL_Texture **textures);
void showPossibleMoves(Cell board[8][8], int row, int col);
Piece emptyPiece();

#endif