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