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

void collisionPlatX(player_s *player, Plataform plats[MAX_PLATFORMS], int count, int screen) {
    for (int i = 0; i < count; i++) {
        
        // checagem de plataformas na tela atual
        if(plats[i].screen != screen){
            continue;
        }

        if (checkCollision(&player->rect, &plats[i].rect)) {

            if (player->vx > 0) { // indo pra direita
                player->x = plats[i].rect.x - player->rect.w;
            } else if (player->vx < 0) { // indo pra esquerda
                player->x = plats[i].rect.x + plats[i].rect.w;
            }

            player->vx = 0;
            player->rect.x = player->x;
        }
    }
}

void collisionPlatY(player_s *player, Plataform plats[MAX_PLATFORMS], int count, int screen) {
    for (int i = 0; i < count; i++) {
        
        // checagem de plataformas na tela atual
        if(plats[i].screen != screen){
            continue;
        }

        if (checkCollision(&player->rect, &plats[i].rect)) {

            if (player->vy > 0) { // descendo
                player->y = plats[i].rect.y - player->rect.h;

                player->fuel = FUEL; // caso o player toque no chão o fuel recarrega
                
            } else if (player->vy < 0) { // subindo
                player->y = plats[i].rect.y + plats[i].rect.h;
            }

            player->vy = 0;
            player->rect.y = player->y;
        }
    }
}

int updatePlayerPosition(player_s *player, float delta, input *input_k,Plataform plats[MAX_PLATFORMS], int count,int screen){
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

    collisionPlatX(player, plats, count,screen);

    player->y += player->vy * delta;
    player->rect.y = player->y;

    collisionPlatY(player, plats, count,screen);

    return 0;
}