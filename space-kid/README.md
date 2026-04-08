# 🚀 Spacekid

**C**

Jogo de plataforma 2D desenvolvido com SDL, com foco em movimentação fluida, sistema de colisão e estrutura modular para expansão futura.

> **Nota:** o projeto ainda está em desenvolvimento. A base de movimentação, colisão e sistema de telas já está funcional, mas ainda pretendo adicionar mais mecânicas, efeitos visuais e talvez um sistema de progressão (quem sabe até fases geradas proceduralmente).

---

## Headers utilizadas

- SDL.h  
- SDL_image.h  

---

## Funcionalidades

- Sistema de movimentação com gravidade e controle por input  
- Colisão com plataformas (resolução por eixo X e Y)  
- Estrutura de múltiplas telas (screens)  
- Renderização otimizada por tela atual  
- Sistema de plataformas baseado em array contínuo  
- Transição entre telas (horizontal)  
- Base preparada para expansão (novas fases, inimigos, etc.)  

---

## Compilar e Executar

```bash
cd games_c/spacekid
cmake --build build
build/spacekid