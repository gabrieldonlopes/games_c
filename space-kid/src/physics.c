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

// Função unificada de colisão
void handlePlatformCollision(player_s *player, Plataform plats[MAX_PLATFORMS], 
                              int count, int screen, SDL_Window *window, int *running) {
    for (int i = 0; i < count; i++) {
        if (plats[i].screen != screen) continue;
        
        if (!checkCollision(&player->rect, &plats[i].rect)) continue;
        
        // Calcula as sobreposições
        float overlapLeft = (player->x + player->rect.w) - plats[i].rect.x;
        float overlapRight = (plats[i].rect.x + plats[i].rect.w) - player->x;
        float overlapTop = (player->y + player->rect.h) - plats[i].rect.y;
        float overlapBottom = (plats[i].rect.y + plats[i].rect.h) - player->y;
        
        // Determina o menor eixo de sobreposição
        float minXOverlap = fmin(overlapLeft, overlapRight);
        float minYOverlap = fmin(overlapTop, overlapBottom);
        
        // Verifica morte por plataforma UMA ÚNICA VEZ
        checkDeathByPlataform(window, running, plats[i]);
        
        // Corrige na direção correta
        if (minXOverlap < minYOverlap) {
            // Colisão horizontal
            if (overlapLeft < overlapRight) {
                // Colidiu pela direita do player
                player->x = plats[i].rect.x - player->rect.w;
            } else {
                // Colidiu pela esquerda do player
                player->x = plats[i].rect.x + plats[i].rect.w;
            }
            player->vx = 0;
        } else {
            // Colisão vertical
            if (overlapTop < overlapBottom) {
                // Colidiu por cima (player descendo)
                player->y = plats[i].rect.y - player->rect.h;
                player->fuel = FUEL;
            } else {
                // Colidiu por baixo (player subindo)
                player->y = plats[i].rect.y + plats[i].rect.h;
            }
            player->vy = 0;
        }
        
        // Atualiza o rect
        player->rect.x = (int)player->x;
        player->rect.y = (int)player->y;
    }
}