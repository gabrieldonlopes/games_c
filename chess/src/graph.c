#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h> 
#include <math.h>
#include "graph.h"
#include "game.h"

/* 
--------------------------------------------------------
# graph.c
#
# Description: funcoes de renderização gráfica
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

const int background_color[3] = {207, 233, 250};
const int cell_color[2][3] = {{209, 199, 182},{122, 90, 34}};

int setupWindow(SDL_Window** window,SDL_Renderer** renderer,TTF_Font **font){
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { // 
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    *window = SDL_CreateWindow(
        "xadrez", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN
    );

    if (!*window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() < 0) { // 
        printf("Erro ao inicializar as fontes: %s\n", SDL_GetError());
        return 1;
    }
    *font = TTF_OpenFont("assets/font.ttf", 30);
    if (!font){
        printf("Erro ao carregar fonte: %s\n", TTF_GetError());
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    
    return 0;
}

void drawText(SDL_Renderer *renderer, TTF_Font *font,
              char *text, int x, int y)
{
    SDL_Color color = {5,5,5};

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect dest = {x, y, surface->w, surface->h};

    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void initTextures(SDL_Renderer *renderer, SDL_Texture** textures){
    char buffer[100];

    for (int i = 0; i < 12; i++)
    {
        SDL_Surface *surface;
        char color = (i % 2 == 0) ? 'b' : 'w';

        snprintf(buffer, sizeof(buffer),
                 "assets/%d_%c.png", i, color);

        surface = IMG_Load(buffer);
        if (!surface){
            printf("Erro carregando %s: %s\n", buffer, IMG_GetError());
            textures[i] = NULL;
            continue;
        }

        textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        printf("%s carregado com sucesso\n", buffer);

        SDL_FreeSurface(surface);

        if (!textures[i]){
            printf("Erro criando texture %s\n", buffer);
        }
    }
}

void destroyTextures(SDL_Texture** textures){
    for (int i = 0; i < 12; i++){
        if (textures[i] != NULL){
            SDL_DestroyTexture(textures[i]);
        }
    }
}

void drawBoard(SDL_Renderer *renderer, TTF_Font *font, Cell cell[8][8])
{
    int margin = 40;
    int thickness = 2;

    int board_size = WIDTH - 2 * margin;
    int cell_size = board_size / 8;

    // background
    SDL_SetRenderDrawColor(renderer,
        background_color[0],
        background_color[1],
        background_color[2],
        255
    );

    // pintando casas
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            if (row%2==0&&col%2==0||row%2!=0&&col%2!=0){
                SDL_SetRenderDrawColor(renderer, // casas brancas
                cell_color[0][0],
                cell_color[0][1],
                cell_color[0][2],
                255
                );
            } else {
                SDL_SetRenderDrawColor(renderer, // casas pretas
                cell_color[1][0],
                cell_color[1][1],
                cell_color[1][2],
                255
                ); 
            }
            SDL_Rect cell_rect = {
                (margin + 1) + col * cell_size,
                (margin + 1) + row * cell_size,
                cell_size - 1,
                cell_size - 1,
            };

            // inicializando board
            cell[row][col].cx = cell_rect.x + cell_rect.w / 2;
            cell[row][col].cy = cell_rect.y + cell_rect.h / 2;

            cell[row][col].x1 = cell_rect.x;
            cell[row][col].y1 = cell_rect.y;
            cell[row][col].x2 = cell_rect.x + cell_rect.w;
            cell[row][col].y2 = cell_rect.y + cell_rect.h;

            SDL_RenderFillRect(renderer, &cell_rect);
            
            // testando se deu tudo certo
            //drawCenter(renderer, cell[row][col].cx, cell[row][col].cy);
        }
    }

    // cor das linhas
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // preto

    // borda externa
    SDL_Rect border = {
        margin,
        margin,
        board_size,
        board_size
    };
    SDL_RenderDrawRect(renderer, &border);

    // linhas internas (verticais + horizontais)
    for (int i = 1; i < 8; i++){
        int offset = i * cell_size;

        // verticais
        SDL_RenderDrawLine(renderer,
            margin + offset, margin,
            margin + offset, margin + board_size
        );

        // horizontais-
        SDL_RenderDrawLine(renderer,
            margin, margin + offset,
            margin + board_size, margin + offset
        );
    }

    // NOTE: codigo movido a gambiarra, hardcodado pra caralho

    // letras e numeros
    char letter[2] = "a";
    for(int i = 0; i < 8; i++){
        letter[0] = 'a' + i;
        drawText(renderer,  font, letter, ((margin+cell_size/2)+cell_size*i)-12, (margin-30)/2);
    }

    char number[2] = "8";

    for(int i = 0; i < 8; i++){
        number[0] = '8' - i;
        drawText(renderer, font, number, (margin-20)/2, ((margin+cell_size/2)+cell_size*i)-16);
    }
}

void drawPiece(SDL_Renderer* renderer, SDL_Texture* texture, int cx, int cy){
    int size = 60;

    SDL_Rect rect = {
        cx - size/2,
        cy - size/2,
        size,
        size
    };

    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

// desenhando um circulo com magia negra
int fillCircle(SDL_Renderer *prenderer, int x, int y, int radius,type_m type_m){
    if (type_m == MOVE){
        SDL_SetRenderDrawColor(prenderer,5, 125, 37,255); 
    } else if (type_m == CASTLING){
        SDL_SetRenderDrawColor(prenderer,25, 44, 252,255); 
    }

    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;
    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(prenderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(prenderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(prenderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(prenderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

void drawSelectionBox(SDL_Renderer *renderer, Cell c){
    SDL_SetRenderDrawColor(renderer, 153, 15, 15, 255);

    int x1 = c.x1;
    int y1 = c.y1;
    int x2 = c.x2;
    int y2 = c.y2;

    int size = 10;      // tamanho das linhas
    int thickness = 5;  // espessura

    for (int t = 0; t < thickness; t++)
    {
        // canto superior esquerdo
        SDL_RenderDrawLine(renderer, x1, y1+t, x1+size, y1+t);
        SDL_RenderDrawLine(renderer, x1+t, y1, x1+t, y1+size);

        // canto superior direito
        SDL_RenderDrawLine(renderer, x2-size, y1+t, x2, y1+t);
        SDL_RenderDrawLine(renderer, x2-t, y1, x2-t, y1+size);

        // canto inferior esquerdo
        SDL_RenderDrawLine(renderer, x1, y2-t, x1+size, y2-t);
        SDL_RenderDrawLine(renderer, x1+t, y2-size, x1+t, y2);

        // canto inferior direito
        SDL_RenderDrawLine(renderer, x2-size, y2-t, x2, y2-t);
        SDL_RenderDrawLine(renderer, x2-t, y2-size, x2-t, y2);
    }
}