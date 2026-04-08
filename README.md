# 🎮 Games em C

[![Linguagem](https://img.shields.io/badge/C-98.6%25-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![CMake](https://img.shields.io/badge/CMake-1.4%25-green.svg)](https://cmake.org/)
[![Status](https://img.shields.io/badge/status-ativo-brightgreen.svg)]()

Repositório com jogos clássicos desenvolvidos na linguagem C, rodando utilizando  a biblioteca gráfica SDL.

Estes projetos foram desenvolvidos com finalidade de entretenimento e aprendizado, por isso, foram construídos com mínimo apoio de LLMs e possuem péssimas decisões de design e estrutura.

## Jogos Incluídos

| Jogo | Descrição | Status |
|------|-----------|--------|
| [**Jogo da Velha**](./jogo-da-velha) | Jogo da velha para dois jogadores| ✅ Funcional |
| [**Xadrez (chess)**](./chess) | Jogo de xadrez completo com movimentação de peças e notação algébrica | ✅ Funcional |
| [**space kid**](./chess) | Jogo de plataforma 2D | Em construção |


## Como Executar

### Pré-requisitos
- Compilador GCC ou Clang
- CMake 
- Terminal Linux/macOS ou WSL no Windows

### Passos gerais
```bash
# Clone o repositório
git clone https://github.com/gabrieldonlopes/games_c.git
cd games_c

# Entre na pasta do jogo desejado
cd chess   # ou cd jogo-da-velha

# Compile com GCC
cmake --build build

# Execute
./build/chess
