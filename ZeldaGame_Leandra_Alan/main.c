#include <stdio.h>
#include <C:/raylib/raylib/src/raylib.h>
#include "constants.h"
#include "functions.h"
#include "gameon.h"
#include <stdbool.h>

// renderizar as pedras, a princesa e as espadas.

int main()
{

    int GAME = MENU;
    int selecaoMenu = 0;
    int NivelAtual = 1;
    bool gameOver = false;
    char ArquivoNivel[100];

    InitWindow(largura, altura, "Zelda - INF");
    SetTargetFPS(60);

    while (WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (GAME == MENU)
        {
            DrawText("Bem-vindo ao Jogo!", 100, 100, 30, WHITE);
            DrawText("Novo jogo", 100, 200, 20, (selecaoMenu == 0) ? RED : WHITE);
            DrawText("Scoreboard", 100, 240, 20, (selecaoMenu == 1) ? RED : WHITE);
            DrawText("Sair", 100, 280, 20, (selecaoMenu == 2) ? RED : WHITE);

            if (IsKeyPressed(KEY_DOWN))
            {
                selecaoMenu++;
                if (selecaoMenu > 2)
                {
                    selecaoMenu = 0;
                }
            }

            switch (selecaoMenu)
            {
            case 0:
                if (IsKeyPressed(KEY_ENTER))
                {
                    GAME = NOVO_JOGO;
                }
                break;
            case 1:
                if (IsKeyPressed(KEY_ENTER))
                {
                    GAME = SCOREBOARD;
                }
                break;
            case 2:
                if (IsKeyPressed(KEY_ENTER))
                {
                    GAME = SAIR;
                }
                break;
            }
        }
        else if (GAME == NOVO_JOGO)
        {
            int numMonstros = 10;
            Nivel nivel;
            Vector2 PosicaoPrincesa = {700, 300};
            bool PrincesaResgate = false;
            Monstros monsters[10] = {0}; // maximo 10 monstros
            Jogador jogador = {0};
            TIPO_SCORE pontuacoes[5];

            Texture2D backGround = LoadTexture("Texturas/Ground.png");
            Texture2D pedra = LoadTexture("Texturas/Obstacle.png");

            Texture2D jogadorDireita = LoadTexture("Texturas/Link_right.png");
            Texture2D jogadorEsquerda = LoadTexture("Texturas/Link_left.png");
            Texture2D jogadorBaixo = LoadTexture("Texturas/Link_down.png");
            Texture2D jogadorCima = LoadTexture("Texturas/Link_up.png");

            Texture2D monstroCima = LoadTexture("Texturas/Enemy_back.png");
            Texture2D monstroBaixo = LoadTexture("Texturas/Enemy_front.png");
            Texture2D monstroDireita = LoadTexture("Texturas/Enemy_right.png");
            Texture2D monstroEsquerda = LoadTexture("Texturas/Enemy_left.png");

            Texture2D espadaCima = LoadTexture("Texturas/Attack_up.png");
            Texture2D espadaBaixo = LoadTexture("Texturas/Attack_down.png");
            Texture2D espadaEsquerda = LoadTexture("Texturas/Attack_left.png");
            Texture2D espadaDireita = LoadTexture("Texturas/Attack_right.png");

            CarregarPontuacoes(pontuacoes);
            CarregaNivel(&nivel, ArquivoNivel); // Carrega o arquivo do próximo nível

            for (int i = 0; i < 16; i++)
            {
                for (int j = 0; j < 24; j++)
                {
                    char cell = nivel.layout[i][j];
                    if (cell == 'P')
                        DrawTexture(pedra, (j * largura - 60) / 50, (i * altura) / 50, WHITE);
                }
            }

            // inicializar os monstros usando a função definida em gameon.h
            InicializarMonstros(monsters, numMonstros); // O segundo argumento é o número de monstros
            InicializarJogador(&jogador);
            if (!gameOver)
            {
                GAME = JOGO_EM_ANDAMENTO;
                // Renderizar plano de fundo do cenário
                DrawTexture(backGround, 0, 0, WHITE);

                if (!PrincesaResgate)
                {
                    MoverJogador(&jogador, nivel); // movimenta jogador
                    // DrawTexture(jogadorTexture, jogador.posicao.x, jogador.posicao.y, WHITE);
                    switch (jogador.textura)
                    {
                    case DIRECAO_DIREITA:
                        DrawTexture(jogadorDireita, jogador.posicao.x, jogador.posicao.y, WHITE);
                        break;

                    case DIRECAO_ESQUERDA:
                    {
                        DrawTexture(jogadorEsquerda, jogador.posicao.x, jogador.posicao.y, WHITE);
                        break;
                    }
                    case DIRECAO_BAIXO:
                    {
                        DrawTexture(jogadorBaixo, jogador.posicao.x, jogador.posicao.y, WHITE);
                        break;
                    }
                    case DIRECAO_CIMA:
                    {
                        DrawTexture(jogadorCima, jogador.posicao.x, jogador.posicao.y, WHITE);
                        break;
                    }
                    }

                    MoverMonstros(monsters, numMonstros, nivel); // movimenta monstros
                    for (int i = 0; i < numMonstros; i++)
                    {
                        if (monsters[i].active)
                        {
                            switch (monsters[i].textura)
                            {
                            case DIRECAO_DIREITA:
                                DrawTexture(monstroDireita, jogador.posicao.x, jogador.posicao.y, WHITE);
                                break;

                            case DIRECAO_ESQUERDA:
                            {
                                DrawTexture(monstroEsquerda, jogador.posicao.x, jogador.posicao.y, WHITE);
                                break;
                            }
                            case DIRECAO_BAIXO:
                            {
                                DrawTexture(monstroBaixo, jogador.posicao.x, jogador.posicao.y, WHITE);
                                break;
                            }
                            case DIRECAO_CIMA:
                            {
                                DrawTexture(monstroCima, jogador.posicao.x, jogador.posicao.y, WHITE);
                                break;
                            }
                            }
                        }
                    }

                    // verifica resgate da princesa e se ainda existem monstros
                    if (CheckCollisionCircles(jogador.posicao, 10, PosicaoPrincesa, 20) && (numMonstros == 0))
                    {
                        PrincesaResgate = true;
                    }

                    // verifica se o jogador colide com o monstro, em caso de perda de todas as vidas. GameOver = TRUE;
                    VerificarColisaoMonstros(&jogador, monsters, numMonstros, &gameOver);

                    // Ativar espada
                    if (IsKeyPressed(KEY_J))
                    {
                        AtivaEspada(&jogador, monsters, &numMonstros); // Chamar a função AtivaEspada
                        if (jogador.espada == true)
                        { // condição que verifica se a espada está ativada
                            switch (jogador.textura)
                            {
                            case DIRECAO_DIREITA:
                                DrawTexture(espadaDireita, jogador.posicao.x, jogador.posicao.y, WHITE);
                                break;

                            case DIRECAO_ESQUERDA:
                            {
                                DrawTexture(espadaEsquerda, jogador.posicao.x, jogador.posicao.y, WHITE);
                                break;
                            }
                            case DIRECAO_BAIXO:
                            {
                                DrawTexture(espadaBaixo, jogador.posicao.x, jogador.posicao.y, WHITE);
                                break;
                            }
                            case DIRECAO_CIMA:
                            {
                                DrawTexture(espadaCima, jogador.posicao.x, jogador.posicao.y, WHITE);
                                break;
                            }
                            }
                        }
                    }
                }
                else
                {
                    NivelAtual++; // proximo nivel
                    if (NivelAtual > NUM_NIVEIS)
                    {
                        // O jogador completou todos os níveis, mostrar mensagem de vitória ou encerrar o jogo
                        GAME = VITORIA;
                        AtualizarPontuacoes(pontuacoes, jogador.score);

                        // abre o ranking de score
                        if (GAME == VITORIA)
                        {
                            GAME = SCOREBOARD;
                        }
                    }
                    else
                    {

                        numMonstros = 10;

                        // faz leitura de arquivo nivel2.txt
                        sprintf(ArquivoNivel, "nivel%d.txt", NivelAtual);
                        CarregaNivel(&nivel, ArquivoNivel); // Carrega o arquivo do próximo nível

                        // Reiniciar variáveis para o próximo nível
                        InicializarMonstros(monsters, numMonstros);
                        InicializarJogador(&jogador);
                        PrincesaResgate = false; // Reinicia o estado de resgate da princesa

                        GAME = JOGO_EM_ANDAMENTO; // e retorna para o loop do jogo
                    }
                }
            }
            else
            {
                AtualizarPontuacoes(pontuacoes, jogador.score);
                BeginDrawing();

                // tela de gameover
                ClearBackground(BLACK);

                // Exibir mensagem de game over
                DrawText("Game Over", largura / 2 - MeasureText("Game Over", 40) / 2, altura / 2 - 40, 40, WHITE);

                // Exibir pontuação final
                DrawText(TextFormat("Pontuação Final: %d", jogador.score), largura / 2 - MeasureText("Pontuação Final: ", 20) / 2, altura / 2 + 20, 20, RED);

                GAME = MENU;
            }
        }
        else if (GAME == SCOREBOARD)
        {
            int inicioY = 100;
            int alturaLinha = 40;

            TIPO_SCORE ranking[5];
            CarregarRanking(ranking);

            ClearBackground(BLACK);
            DrawText("Scoreboard", largura / 2 - MeasureText("Scoreboard", 40) / 2, altura / 2 - 100, 40, WHITE);

            // Exibir os scores no ranking
            for (int i = 0; i < 5; i++)
            {
                int posX = largura / 2 - 200; // Posição horizontal para o nome
                DrawText(ranking[i].nome, posX, inicioY + i * alturaLinha, 30, WHITE);

                posX = largura / 2 + 100; // Posição horizontal para o score
                char scoreText[20];
                sprintf(scoreText, "%d", ranking[i].score);
                DrawText(scoreText, posX, inicioY + i * altura, 30, WHITE);
            }
            DrawText("Pressione ENTER para voltar ao Menu", largura / 2 - MeasureText("Pressione ENTER para voltar ao Menu", 20) / 2, altura - 40, 20, GRAY);

            if (IsKeyPressed(KEY_ENTER))
            {
                GAME = MENU;
            }
        }
        else if (GAME == SAIR)
        {
            CloseWindow();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}