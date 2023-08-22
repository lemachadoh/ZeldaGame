#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "C:/raylib/raylib/src/raylib.h" 
#include "constants.h"

void CarregaNivel(Nivel *nivel, const char *arquivo_nivel);

void CarregarPontuacoes(TIPO_SCORE pontuacoes[5]);

void AtualizarPontuacoes(TIPO_SCORE pontuacoes[5], int scoreJogador);

#endif
