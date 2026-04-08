#include "graph.h"
#include "physics.h"
#include "game.h"
#include "defs.h"

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

/* 
    nota: possuo duas abordagens disponíveis para o sistema:
        1. utilizar variavel normal em player e passar o endereço para as funções (stack)
        2. utilizar ponteiro para player e usar malloc/free no final do programa (heap)

    não entendo totalmente a diferença que existe entre essas duas abordagens, por isso 
    estou usando a mais simples

    o padrão que seguirei adiante é usar 
*/

player_s player;
input input_k;
SDL_Rect ground_rect;
Plataform plat [MAX_PLATFORMS]; // buffer contínuo que guarda todas plataformas

/*
    nota: como vou implementar um número prefixado de plataformas (vale pensar no futuro criar um gerador de 
    mapas automaticos tmb) posso guardar o endereço inicio das plataformas de determinada tela
*/

// representa a tela, cada plataforma está mapeada para uma tela diferente
// ao passar ou voltar a tela esse valor é acrescido ou decrescido com WIDTH 
int screen;  

void handleInput();
void render();
void updateGame();

int main (int argc, char *argv[]){
    if(setupWindow(&window, &renderer)){
        return 1;
    }

    initPlataforms(plat);

    // posição inicial
    player.x = WIDTH / 2;
    player.y = HEIGHT / 2;

    screen = 0;

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

        } else if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                input_k = RIGHT;
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
                input_k = LEFT;
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_UP){
                input_k = UP;
            }

        } else if (event.type == SDL_KEYUP){
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT){
                input_k = NONE;
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT){
                input_k = NONE;
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_UP){
                input_k = NONE;
            }
        }
    }
}

void render(){
    // limpar tela
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    // desenhando coisas
    drawBackground(renderer);
    drawGround(renderer,plat,screen);
    drawPlayer(renderer,&player);
    drawFire(renderer, &player);

    // mostrar frame
    SDL_RenderPresent(renderer);
}

void updateGame(){
    Uint32 now = SDL_GetTicks();
    delta = (now - last) / 1000.0f;
    last = now;

    updatePlayerPosition(&player, delta,&input_k,plat,MAX_PLATFORMS,screen);
    checkDeathByFall(&player, &running,window);
    changeScreen(&player, &screen);
}