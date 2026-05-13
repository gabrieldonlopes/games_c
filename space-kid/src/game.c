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

int updatePlayerPosition(player_s *player, float delta, input *input_k, Plataform plats[MAX_PLATFORMS], 
                         int count, int screen, SDL_Window *window, int *running) {
    
    // Aplica gravidade
    player->vy += GRAVITY * delta;
    
    // Aplica input
    if (*input_k == RIGHT)
        player->vx = 200;
    else if (*input_k == LEFT)
        player->vx = -200;
    else if (*input_k == UP && player->fuel > 0) {
        player->vy = -210; 
        player->fuel -= 100 * delta;
        if (player->fuel < 0) player->fuel = 0;
        
        // Ao pular, desgruda da plataforma
        player->current_platform = NULL;
        player->on_ground = 0;
    }
    else if (*input_k == NONE) {
        // força de atrito
        if (player->vx < 0) {
            player->vx += 10;
            if (player->vx > 0) player->vx = 0;
        } else if (player->vx > 0) {
            player->vx -= 10;
            if (player->vx < 0) player->vx = 0;
        }
    }
    
    // Guarda posição antiga para resolver colisões
    float old_x = player->x;
    float old_y = player->y;
    
    // Aplica movimento
    player->x += player->vx * delta;
    player->y += player->vy * delta;
    
    // Atualiza rect para colisão
    player->rect.x = (int)roundf(player->x);
    player->rect.y = (int)roundf(player->y);
    
    // Resolve colisões
    handlePlatformCollision(player, plats, count, screen, window, running);
    
    // Se o jogador está em uma plataforma e ela se moveu, ajusta a posição
    if (player->current_platform && player->on_ground) {
        // A posição já deve estar correta por causa da ordem de atualização
        // Mas garantimos que o rect está sincronizado
        player->rect.x = (int)roundf(player->x);
        player->rect.y = (int)roundf(player->y);
    }
    
    return 0;
}

void updatePlatformPosition(Plataform plats[MAX_PLATFORMS], float delta){
    for (int i = 0; i < MAX_PLATFORMS; i++){
        if (plats[i].type != MOVABLE) continue;

        plats[i].mov.last_x = plats[i].x;
        plats[i].mov.last_y = plats[i].y;

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