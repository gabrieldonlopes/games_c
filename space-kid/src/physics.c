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

int checkCollision(SDL_Rect *a, SDL_Rect *b)
{
    int epsilon = 2;

    return (
        a->x <= b->x + b->w &&
        a->x + a->w >= b->x &&

        a->y <= b->y + b->h + epsilon &&
        a->y + a->h >= b->y - epsilon
    );
}

void handlePlatformCollision(player_s *player, Plataform plats[MAX_PLATFORMS], 
                              int count, int screen, SDL_Window *window, int *running) {
    
    int grounded = 0;
    
    for (int i = 0; i < count; i++) {
        if (plats[i].screen != screen) continue;
        if (!checkCollision(&player->rect, &plats[i].rect)) continue;
        
        // Verifica morte por dano
        if (plats[i].type == DAMAGE) {
            SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_INFORMATION,
                "Se fudeu",
                "Bateu na parede errada!",
                window
            );
            *running = 0;
            return;  // Sai imediatamente
        }
        
        // Calcula sobreposições
        float overlapLeft = (player->x + player->rect.w) - plats[i].rect.x;
        float overlapRight = (plats[i].rect.x + plats[i].rect.w) - player->x;
        float overlapTop = (player->y + player->rect.h) - plats[i].rect.y;
        float overlapBottom = (plats[i].rect.y + plats[i].rect.h) - player->y;
        
        float minXOverlap = fmin(overlapLeft, overlapRight);
        float minYOverlap = fmin(overlapTop, overlapBottom);
        
        // Verifica se é colisão horizontal ou vertical
        if (minXOverlap < minYOverlap) {
            // Colisão horizontal
            if (overlapLeft < overlapRight) {
                player->x = plats[i].rect.x - player->rect.w;
            } else {
                player->x = plats[i].rect.x + plats[i].rect.w;
            }
            player->vx = 0;
        } else {
            // Colisão vertical - PRIORIZA COLOCAR O JOGADOR EM CIMA
            // Se o centro do jogador está acima do centro da plataforma
            float player_center_y = player->y + player->rect.h / 2;
            float plat_center_y = plats[i].rect.y + plats[i].rect.h / 2;
            
            // Decide se coloca em cima ou embaixo baseado na posição relativa
            if (player_center_y < plat_center_y || player->vy >= 0) {
                // Coloca o jogador em CIMA da plataforma
                player->y = plats[i].rect.y - player->rect.h;
                player->fuel = FUEL;
                grounded = 1;
                player->current_platform = &plats[i];
                
                // Só zera a velocidade se estiver descendo
                if (player->vy > 0) {
                    player->vy = 0;
                }
            } else {
                // Colisão por baixo (bateu a cabeça)
                player->y = plats[i].rect.y + plats[i].rect.h;
                if (player->vy < 0) {
                    player->vy = 0;
                }
            }
        }
        
        // Atualiza rect
        player->rect.x = (int)roundf(player->x);
        player->rect.y = (int)roundf(player->y);
    }
    
    player->on_ground = grounded;
    
    // Se não está no chão, limpa a referência da plataforma
    if (!grounded) {
        player->current_platform = NULL;
    }
}