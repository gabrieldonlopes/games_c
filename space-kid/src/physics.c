#include "physics.h"
#include "game.h"

/* 
--------------------------------------------------------
# physics.c
#
# Description: funcoes de física do projeto
# Autor: gdon - gabriellopes.zip@gmail.com
# Version: 1.0
# Data: 
--------------------------------------------------------
*/

int checkCollision(SDL_Rect *a, SDL_Rect *b){
    return (a->x < b->x + b->w &&
            a->x + a->w > b->x &&
            a->y < b->y + b->h &&
            a->y + a->h > b->y);
}

int updatePlayerPosition(player_s *player, float delta){
    // gravidade
    player->vy += GRAVITY * delta;

    // mover
    player->y += player->vy * delta;

    // atualizar rect
    player->rect.x = player->x;
    player->rect.y = player->y;
}