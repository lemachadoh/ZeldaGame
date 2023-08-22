#include "gameon.h"
#include "constants.h"

// Implementação da função de inicialização dos monstros
void InicializarMonstros(Monstros *monsters, int numMonstros) {
    for (int i = 0; i < numMonstros; i++) {
        monsters[i].posicao = (Vector2){GetRandomValue(200, 600), GetRandomValue(150, 400)};
        monsters[i].active = true;
    }
}

//incializa o jogador
void InicializarJogador(Jogador *jogador){
    // Inicialização do jogador
    jogador.posicao = (Vector2){100, 100};
    jogador.saude = 100;
    jogador.score = 0; // atualiza com o arquivo score
    jogador.vidas = 3;
    jogador.espada = false;
    jogador.orientacao = 'N';
    jogador.nivel = 1;
}

//movimentar o jogador
void MoverJogador(Jogador *jogador, Nivel nivel){
    // Verificação de limites para o jogador
        if (jogador.posicao.x < 0)
        {
            jogador.posicao.x = 0;
        }
        if (jogador.posicao.y < 60)
        {
            jogador.posicao.y = 60;
        }
        if (jogador.posicao.x > largura - jogador.tamanho.x)
        {
            jogador.posicao.x = largura - jogador.tamanho.x;
        }
        if (jogador.posicao.y > altura - jogador.tamanho.y)
        {
            jogador.posicao.y = altura - jogador.tamanho.y;
        }

        // Movimentação do jogador
        if (IsKeyDown((KEY_RIGHT && KEY_D)) && !IsCollision((Vector2){jogador.posicao.x + 2, jogador.posicao.y}, nivel))
        {
            jogador.posicao.x += 2;
            jogador->textura = DIRECAO_DIREITA;
        }
        else
        {
            // jogador colidiu com uma pedra, não há movimentos
        }
        if (IsKeyDown((KEY_LEFT && KEY_A)) && !IsCollision((Vector2){jogador.posicao.x - 2, jogador.posicao.y}, nivel))
        {
            jogador.posicao.x -= 2;
            jogador->textura = DIRECAO_ESQUERDA;   
        }
        else
        {
            // jogador colidiu com uma pedra, não há movimentos
        }
        if (IsKeyDown((KEY_DOWN && KEY_S)) && !IsCollision((Vector2){jogador.posicao.x, jogador.posicao.y + 2}, nivel))
        {
            jogador.posicao.y += 2;
            jogador->textura = DIRECAO_BAIXO;
        }
        else
        {
            // jogador colidiu com uma pedra, não há movimentos
        }
        if (IsKeyDown((KEY_UP && KEY_W)) && !IsCollision((Vector2){jogador.posicao.x, jogador.posicao.y - 2}, nivel))
        {
            jogador.posicao.y -= 2;
            ogador->textura = DIRECAO_CIMA;
        }
        else
        {
            // jogador colidiu com uma pedra, não há movimentos
        }
}

//movimenta monstro
void MoverMonstros(Monstros *monsters, int numMonstros, Nivel nivel){
    // movimentação dos monstros
        for (int i = 0; i < numMonstros; i++)
        {
            if (monsters[i].active)
            {
                int movX = 0;
                int movY = 0;

                int direcaoMovimentoMonstro = GetRandomValue(0, 3); // 0 para cima, 1 para baixo, 2 para esquerda, 3 para direita
                switch (direcaoMovimentoMonstro) {
                case 0:
                    movY = -INCREMENTO_MOV_MONSTRO; // Movimentar para cima
                    monsters->textura = DIRECAO_CIMA;
                    break;
                case 1:
                    movY = INCREMENTO_MOV_MONSTRO; // Movimentar para baixo
                    monsters->textura = DIRECAO_BAIXO;
                    break;
                case 2:
                    movX = -INCREMENTO_MOV_MONSTRO; // Movimentar para a esquerda
                    monsters->textura = DIRECAO_ESQUERDA;
                    break;
                case 3:
                    movX = INCREMENTO_MOV_MONSTRO; // Movimentar para a direita
                    monsters->textura = DIRECAO_DIREITA;
                    break;
            }
                // verifica se ha colicao com a pedra
                if (!IsCollision((Vector2){monsters[i].posicao.x + movX, monsters[i].posicao.y + movY}, nivel))
                {
                    monsters[i].posicao.x += movX;
                    monsters[i].posicao.y += movY;
                }
                else
                {
                    // monstro colidiu com a pedra, não há movimentação
                }

                // Verificar limites do cenário para os monstros
                if (monsters[i].posicao.x < 0)
                {
                    monsters[i].posicao.x = 0;
                }
                if (monsters[i].posicao.y < 60)
                {
                    monsters[i].posicao.y = 60;
                }
                if (monsters[i].posicao.x > largura)
                {
                    monsters[i].posicao.x = largura;
                }
                if (monsters[i].posicao.y > altura)
                {
                    monsters[i].posicao.y = altura;
                }
            }
        }
}

//verifica se o jogador colide com o monstro, em caso de perda de todas as vidas. GameOver = TRUE;
void VerificarColisaoMonstros(Jogador *jogador, Monstros *monsters, int numMonstros, bool *gameOver){
    // Verificar colisão do jogador com os monstros
    for (int i = 0; i < numMonstros; i++){
        if (!(&gameOver) && monsters[i].active && CheckCollisionCircles(jogador->posicao, 10, monsters[i].posicao, 20)){
            jogador->posicao = (Vector2){100, 100};

            for (int j = 0; j < numMonstros; j++){
                monsters[j].posicao = (Vector2){GetRandomValue(200, 600), GetRandomValue(150, 400)};
                monsters[j].active = true;
            }

            jogador.vidas--;
            if (jogador.vidas <= 0){
                    *gameOver = true;
            }
        }
    }
}

bool IsCollision(Vector2 position, Nivel nivel)
{
    int col = (int)(position.x / 50);
    int row = (int)((position.y - 60) / 50); // Subtrai 60 para compensar a barra de status

    if (col >= 0 && col < 24 && row >= 0 && row < 16)
    {
        char cell = nivel.layout[row][col];
        return cell == 'P'; // Verifica se há uma pedra na posição
    }

    return false;
}

void AtivaEspada(Jogador *jogador, Monstros *monstros, int *numMonstros)
{
    if (!jogador->espada)
    {
        jogador->espada = true;
        Vector2 swordTarget;
        switch (jogador->orientacao){
        case 'N':
            swordTarget = (Vector2){jogador->posicao.x, jogador->posicao.y - 3};
            jogador->textura = DIRECAO_CIMA;
            break;
        case 'S':
            swordTarget = (Vector2){jogador->posicao.x, jogador->posicao.y + 3};
            jogador->textura = DIRECAO_BAIXO;
            break;
        case 'L':
            swordTarget = (Vector2){jogador->posicao.x + 3, jogador->posicao.y};
            jogador->textura = DIRECAO_DIREITA;
            break;
        case 'O':
            swordTarget = (Vector2){jogador->posicao.x - 3, jogador->posicao.y};
            jogador->textura = DIRECAO_ESQUERDA;
            break;
        }
        for (int i = 0; i < numMonstros; i++)
        {
            if (monstros[i].active && CheckCollisionCircles(swordTarget, 10, monstros[i].posicao, 20))
            {
                monstros[i].active = false;
                jogador->score += 100;
                (*numMonstros)--;
            }
        }
    }
}