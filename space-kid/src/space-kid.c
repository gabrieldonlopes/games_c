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
int running = 1;

void handleInput();

int main (int argc, char *argv[]){
    if(setupWindow(window, renderer)){
        return 1;
    }

    while(running){
        handleInput();
    }

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