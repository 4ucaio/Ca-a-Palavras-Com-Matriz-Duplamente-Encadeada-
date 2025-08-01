#ifndef COORDENADA_H
#define COORDENADA_H
#include "matriz.h"

// indica onde começa ou termina uma palavra
typedef struct {
    int linha; 
    int coluna; 
} TCoordenada;

// Criar uma nova coordenada
TCoordenada coordenada_criar(int i, int j);

// Verificar se coordenada está dentro dos limites da matriz, retornando 1 em caso positivo e 0 caso contrário
int coordenada_verificar(TCoordenada coordenada, TMatriz* matriz);

#endif