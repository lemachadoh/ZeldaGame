#ifndef GAMEON_H
#define GAMEON_H

#include "C:/raylib/raylib/src/raylib.h" 
#include "constants.h"

void InicializarMonstros(Monstros *monsters, int numMonstros);

void InicializarJogador(Jogador *jogador);

void MoverJogador(Jogador *jogador, Nivel nivel);

void MoverMonstros(Monstros *monsters, int numMonstros, Nivel nivel);

void VerificarColisaoMonstros(Jogador *jogador, Monstros *monsters, int numMonstros, bool *gameOver);

bool IsCollision(Vector2 position, Nivel nivel);

void AtivaEspada(Jogador *jogador, Monstros *monstros, int *numMonstros);

#endif
