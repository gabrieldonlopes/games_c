# ❌⭕ Jogo da Velha em C

[![C](https://img.shields.io/badge/C-98.6%25-00599C.svg)]()

Clássico jogo da velha para dois jogadores rodando com interface gráfica.

##  Headers utilizadas
- SDL.h
- SDL_Image.h
- SDL_ttf.h

## Funcionalidades
- Tabuleiro 3x3 interativo
- Dois jogadores alternam entre 'X' e 'O'
- Verificação automática de vitória (linhas, colunas, diagonais)
- Detecção de empate
- Opção de reiniciar ou sair após cada partida

## Como Jogar

### Compilar e Executar
```bash
cd games_c/jogo-da-velha
gcc -o velha main.c
./velha