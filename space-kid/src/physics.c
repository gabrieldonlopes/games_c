#include "physics.h"

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

void collisionPlatX(player_s *player, Plataform plats[MAX_PLATFORMS], 
                    int count, int screen,SDL_Window *window, int *running) {
    for (int i = 0; i < count; i++) {
        
        // checagem de plataformas na tela atual
        if(plats[i].screen != screen){
            continue;
        }

        if (checkCollision(&player->rect, &plats[i].rect)) {
            if (player->vx > 0) { // indo pra direita
                checkDeathByPlataform(window, running, plats[i]);

                player->x = plats[i].rect.x - player->rect.w;
            } else if (player->vx < 0) { // indo pra esquerda
                checkDeathByPlataform(window, running, plats[i]);

                player->x = plats[i].rect.x + plats[i].rect.w;
            }

            player->vx = 0;
            player->rect.x = player->x;
        }
    }
}

void collisionPlatY(player_s *player, Plataform plats[MAX_PLATFORMS], 
                    int count, int screen,SDL_Window *window, int *running) {
    for (int i = 0; i < count; i++) {
        
        // checagem de plataformas na tela atual
        if(plats[i].screen != screen){
            continue;
        }

        if (checkCollision(&player->rect, &plats[i].rect)) {

            if (player->vy > 0) { // descendo
                checkDeathByPlataform(window, running, plats[i]);

                player->y = plats[i].rect.y - player->rect.h;
                player->fuel = FUEL; // caso o player toque no chão o fuel recarrega                
            } else if (player->vy < 0) { // subindo
                checkDeathByPlataform(window, running, plats[i]);

                player->y = plats[i].rect.y + plats[i].rect.h;
            }

            player->vy = 0;
            player->rect.y = player->y;
        }
    }
}