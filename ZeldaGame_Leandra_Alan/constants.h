#ifndef CONSTANTS.H
#define CONSTANTS.H

#include <raylib.h>

#define INCREMENTO_MOV_MONSTRO 2
#define largura 1200
#define altura 860
#define NUM_NIVEIS 2
#define PATH Texturas

//menu:
enum GAME {
    MENU,
    NOVO_JOGO,
    SCOREBOARD,
    SAIR,
    JOGO_EM_ANDAMENTO,
    VITORIA
};

enum DIRECAO_JOGADOR{
    DIRECAO_CIMA,
    DIRECAO_BAIXO,
    DIRECAO_ESQUERDA,
    DIRECAO_DIREITA
};

//score
typedef struct tipo_score
{
    char nome[20];
    int score;
} TIPO_SCORE;

// Estrutura para representar um monstro
typedef struct {
    Vector2 posicao;
    bool active;
    Vector2 orientacao;
    int textura;
} Monstros;

// Estrutura para representar o jogador
typedef struct {
    Vector2 posicao;
    int saude;
    int score;
    int vidas;
    bool espada;
    char orientacao;
    int nivel;
    int textura;
} Jogador;

typedef struct
{
    char layout[16][24]; //16 linhas por 24 colunas,
}Nivel;


#endif
