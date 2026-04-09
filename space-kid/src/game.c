#include "game.h"

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