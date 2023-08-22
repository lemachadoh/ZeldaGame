#include <constants.h>
#include <functions.h>
#include "C:/raylib/raylib/src/raylib.h"
#include <stdio.h>

void CarregaNivel(Nivel *nivel, const char *arquivo_nivel)
{
    int i, j;
    FILE *arquivo = fopen(arquivo_nivel, "r");

    if (arquivo == NULL)
    {
        printf("Erro ao iniciar o arquivo %s\n", arquivo_nivel);
        return;
    }
    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 24; j++)
        {
            fscanf(arquivo, " %c", &nivel->layout[i][j]);
        }
    }
    fclose(arquivo);
}

void CarregarPontuacoes(TIPO_SCORE *pontuacoes[5]) {
    FILE *arquivo = fopen("ranking.bin", "rb");
    if (arquivo != NULL) {
        fread(pontuacoes, sizeof(TIPO_SCORE), 5, arquivo);
        fclose(arquivo);
    }
}

void AtualizarPontuacoes(TIPO_SCORE *pontuacoes[5], int scoreJogador){    // Verifique se a nova pontuação é maior do que alguma das pontuações existentes
    // Verifique se a nova pontuação é maior do que alguma das pontuações existentes
    int indiceInsercao = -1;
    for (int i = 0; i < 5; i++)
    {
        if (scoreJogador > pontuacoes[i].score)
        {
            indiceInsercao = i;
            break;
        }
    }

    // Se houver uma pontuação maior, insira a nova pontuação na posição correta e atualize as demais pontuações
    if (indiceInsercao != -1)
    {
        const char *nomeJogador = GetInputBoxText("Digite seu nome:", "Nome do Jogador", "");
        
        if (nomeJogador != NULL && nomeJogador[0] != '\0'){

            for (int i = 4; i > indiceInsercao; i--)
            {
                pontuacoes[i] = pontuacoes[i - 1];
            }
            strcpy(*pontuacoes[indiceInsercao].nome, nomeJogador);
            *pontuacoes[indiceInsercao].score = scoreJogador;
        }
    }

    // Salvar as pontuações atualizadas no arquivo
    FILE *arquivo = fopen("ranking.bin", "wb");
    if (arquivo != NULL) {
        fwrite(pontuacoes, sizeof(TIPO_SCORE), 5, arquivo);
        fclose(arquivo);
    }
}