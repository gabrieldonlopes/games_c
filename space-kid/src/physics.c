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

int updatePlayerPosition(player_s *player, float delta, input *input_k){
    // gravidade
    player->vy += GRAVITY * delta;

    // movimento horizontal
    if (*input_k == RIGHT)
        player->vx = 200;
    else if (*input_k == LEFT)
        player->vx = -200;
    else if (*input_k == UP)
        player->vy = -200;
    else if (*input_k == NONE)
        if (player->vx < 0) {
            player->vx += 10;
        }
        else if (player->vx > 0)
        {
            player->vx -= 10;
        }
        else
        {
            player->vx = 0;
        }
        
    player->y += player->vy * delta;
    player->x += player->vx * delta;

    // atualizar rect
    player->rect.x = player->x;
    player->rect.y = player->y;
}