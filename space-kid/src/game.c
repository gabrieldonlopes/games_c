#include "game.h"
#include "physics.h"

/* 
--------------------------------------------------------
# game.c
#
# Description: conjunto de funções de tratamento do estado do jogo
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

void changeScreen(player_s *player,int *screen){
    
    // indo para direita
    if (player->rect.x+player->rect.w >= WIDTH){
       *screen += WIDTH;

        // teleporta pro outro lado
        player->x = 0;
        player->rect.x = player->x;
   }

    // indo pra esquerda
    else if (player->rect.x <= 0){
        *screen -= WIDTH;


        player->x = WIDTH - player->rect.w;
        player->rect.x = player->x;
    }
}

void checkDeathByFall(player_s *player, int *running,SDL_Window *window){
    if (player->rect.y >= HEIGHT) {
        SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_INFORMATION,
            "Se fudeu",
            "Caiu para fora do mundo!",
            window
        );
        *running = 0;
    }
}

void checkDeathByPlataform(SDL_Window *window, int *running, Plataform plats){
    if (plats.type == DAMAGE){
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_INFORMATION,
                "Se fudeu",
                "Bateu na parede errada!",
                window
            );
        *running = 0;
    }
} 

int updatePlayerPosition(player_s *player, float delta, input *input_k,Plataform plats[MAX_PLATFORMS], 
                         int count,int screen,SDL_Window *window, int *running){
    player->vy += GRAVITY * delta;
    
    if (*input_k == RIGHT)
        player->vx = 200;
    else if (*input_k == LEFT)
        player->vx = -200;
    else if (*input_k == UP && player->fuel > 0){ // só sobe caso tenha combustível
        player->vy = -210 ; 
        player->fuel -= 100 * delta;  // consumo por segundo
    }
    else if (*input_k == NONE)
    {
        if (player->vx < 0)
            player->vx += 10;
        else if (player->vx > 0)
            player->vx -= 10;
        else
            player->vx = 0;
    }

    player->x += player->vx * delta;
    player->rect.x = player->x;

    collisionPlatX(player, plats, count,screen,window,running);

    player->y += player->vy * delta;
    player->rect.y = player->y;

    collisionPlatY(player, plats, count,screen,window,running);

    return 0;
}

void updatePlatformPosition(Plataform plats[MAX_PLATFORMS], float delta){
    for (int i = 0; i < MAX_PLATFORMS; i++){
        if (plats[i].type != MOVABLE) continue;

        plats[i].x += plats[i].mov.vx * delta;
        plats[i].y += plats[i].mov.vy * delta;

        if(plats[i].mov.x1 != -1 && plats[i].mov.x2 != -1){
            if (plats[i].x <= plats[i].mov.x1) {
                plats[i].x = plats[i].mov.x1;
                plats[i].mov.vx *= -1;
            }

            if (plats[i].x + plats[i].rect.w >= plats[i].mov.x2) {
                plats[i].x = plats[i].mov.x2 - plats[i].rect.w;
                plats[i].mov.vx *= -1;
            }   
        }

        if(plats[i].mov.y1 != -1 && plats[i].mov.y2 != -1){
            if (plats[i].y <= plats[i].mov.y1) {
                plats[i].y = plats[i].mov.y1;
                plats[i].mov.vy *= -1;
            }

            if (plats[i].y + plats[i].rect.h >= plats[i].mov.y2) {
                plats[i].y = plats[i].mov.y2 - plats[i].rect.h;
                plats[i].mov.vy *= -1;
            }
        }

        plats[i].rect.x = (int)plats[i].x;
        plats[i].rect.y = (int)plats[i].y;
    }
}