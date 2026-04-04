#include "graph.h"

/* 
--------------------------------------------------------
# space-kid.c
#
# Description: programa de inicializacao do jogo space-kid
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

SDL_Window *window = NULL; // janela base
SDL_Renderer *renderer = NULL; // renderizador base
SDL_Event event;

Uint32 last;
int running = 1;
float delta;

Uint32 frameStart;
int frameTime;

int player_position[2] = {WIDTH / 2, HEIGHT / 2};

void handleInput();
void render();
void updateGame();

int main (int argc, char *argv[]){
    if(setupWindow(&window, &renderer)){
        return 1;
    }

    last = SDL_GetTicks();
    while(running){

        frameStart = SDL_GetTicks();

        handleInput();
        updateGame();
        render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < 16){
            SDL_Delay(16 - frameTime); // ~60 FPS
        }

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void handleInput(){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = 0;
        }
    }
}

void render(){
    // limpar tela
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    // desenhando coisas
    drawBackground(renderer);
    drawGround(renderer);
    drawPlayer(renderer,player_position);

    // mostrar frame
    SDL_RenderPresent(renderer);
}

void updateGame(){
    int vy = 500; // pixels por segundo

    Uint32 now = SDL_GetTicks();
    delta = (now - last) / 1000.0f;
    last = now;

    // atualizando a posição do player
    player_position[1] +=  vy * delta;

}