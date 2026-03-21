#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

/* 
# jogo-da-velha.c
#
# Description: jogo da velha simplificado
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

#define WIDTH 600
#define HEIGHT 600
#define BC_RED 185
#define BC_GREEN 199
#define BC_BLUE 189

typedef struct {
  int cx;
  int cy;
  int gap [2][2];//x1,x2 e y1,y2
  char mark;
} sq;

void drawCircleTrig(SDL_Renderer *prenderer, int cx,int cy);
void drawX(SDL_Renderer *prenderer, int cx, int cy);
int verify_sq(int x,int y);
int winner(int idx,char player,sq *winners);

sq grid[9]; // inicializando grid
sq winners[3];

int main(int argc, char* argv[]) {
    
    // tamanho de cada quadrado no grid
    int w = WIDTH / 3; 
    int h = HEIGHT / 3;

    for (int i = 0; i < 9; i++) {
        int row = i / 3; 
        int col = i % 3;

        grid[i].gap[0][0] = col * w;
        grid[i].gap[0][1] = (col + 1) * w;

        grid[i].gap[1][0] = row * h;
        grid[i].gap[1][1] = (row + 1) * h;

        grid[i].cx = (grid[i].gap[0][0] + grid[i].gap[0][1]) / 2;
        grid[i].cy = (grid[i].gap[1][0] + grid[i].gap[1][1]) / 2;

        grid[i].mark = '.';
    }
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) { // 
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "jogo da velha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    
    // desenhando background
    SDL_SetRenderDrawColor(renderer, BC_RED, BC_GREEN, BC_BLUE, 255); 
    SDL_RenderClear(renderer);
    
    // desenhando linhas
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderDrawLine(renderer,
        (int)WIDTH/3.0,10,
        (int)WIDTH/3.0,HEIGHT-10);
    SDL_RenderDrawLine(renderer,
        2*((int)WIDTH/3.0),10,
        (2*(int)WIDTH/3.0),HEIGHT-10);
    SDL_RenderDrawLine(renderer,
        10,(int)HEIGHT/3.0,
          WIDTH-10,(int)HEIGHT/3.0);
    SDL_RenderDrawLine(renderer,
        10,2*((int)HEIGHT/3.0),
        WIDTH-10,2*((int)HEIGHT/3.0));

    SDL_RenderPresent(renderer);

    int running = 1;
    int turn = 1; // 1=X, 0=O
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
              int mouse_x = event.button.x;
              int mouse_y = event.button.y;
            
              int idx = verify_sq(mouse_x,mouse_y);
              if (idx != -1) {

              if(turn){
                grid[idx].mark = 'X'; 
                drawX(renderer,grid[idx].cx,grid[idx].cy);
                turn=0;
              }else{
                grid[idx].mark = 'O';
                drawCircleTrig(renderer,grid[idx].cx,grid[idx].cy);
                turn=1;
              }
              
              if (winner(idx,grid[idx].mark,winners)){
                SDL_SetRenderDrawColor(renderer, 0, 255,0 ,255);
                SDL_RenderDrawLine(renderer,winners[0].cx,winners[0].cy,winners[2].cx,winners[2].cy);
              }
              
              SDL_RenderPresent(renderer);
              }
            }
        }
        

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void drawCircleTrig(SDL_Renderer *prenderer, int cx, int cy) {
  SDL_SetRenderDrawColor(prenderer,255,0,0,255); // circulos de cor vermelha
  const int steps = 360;
  const int radius = 80;

  for (int i = 0; i < steps; i++) {
    double theta = i * 2.0 * M_PI / steps;
    int x = cx + (int)(radius * cos(theta));
    int y = cy + (int)(radius * sin(theta));
    SDL_RenderDrawPoint(prenderer,x,y);
   }
}

void drawX(SDL_Renderer *prenderer, int cx, int cy){
  SDL_SetRenderDrawColor(prenderer,0,0,255,255); // x de cor azul
  const int size = 60; // tamanho do X hardcoded
  
  SDL_RenderDrawLine(prenderer,cx-size,cy-size,cx+size,cy+size);
  SDL_RenderDrawLine(prenderer,cx-size,cy+size,cx+size,cy-size);
  
}

int verify_sq(int x,int y){
  int valid = 1;
  for (int i = 0; i < 9; i++){
    if (grid[i].gap[0][0]<x && grid[i].gap[0][1]>x && grid[i].gap[1][0]<y && grid[i].gap[1][1]>y && grid[i].mark=='.'){
      return i;
    }
  }
  return -1;
}

int winner(int idx,char player,sq *winners){
  // verificando linhas
  int row  = idx / 3; // descobrir qual linha foi jogada
  int col = idx % 3; // descobrir qual coluna foi jogada
 
  // verificando linhas
  if (grid[row*3+0].mark == player && 
    grid[row*3+1].mark == player &&
    grid[row*3+2].mark == player) {
    
    winners[0]=grid[row*3+0];
    winners[1]=grid[row*3+1];
    winners[2]=grid[row*3+2];
    return 1;
  }

  // verificando colunas
  if (grid[0*3+col].mark == player &&
    grid[1*3+col].mark == player &&
    grid[2*3+col].mark == player){
    
    winners[0]=grid[0*3+col];
    winners[1]=grid[1*3+col];
    winners[2]=grid[2*3+col];
    return 1;
  } 
  
  // diagonal principal
  if (idx == 0 || idx == 4 || idx == 8){
    if (grid[0].mark == player &&
        grid[4].mark == player &&
        grid[8].mark == player){
    
      winners[0] = grid[0];
      winners[1] = grid[4];
      winners[2] = grid[8];
      return 1;
    }
  }

  // diagonal secundaria
  if (idx == 2 || idx == 4 || idx == 6){  
    if (grid[2].mark == player &&
        grid[4].mark == player &&
        grid[6].mark == player){

      winners[0] = grid[2];
      winners[1] = grid[4];
      winners[2] = grid[6];
      return 1;
    }
  } 

  return 0;
}
