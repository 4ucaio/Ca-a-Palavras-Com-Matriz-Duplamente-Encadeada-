#ifndef OCORRENCIAS_H
#define OCORRENCIAS_H

#include "coordenada.h"
#include "matriz.h"
#include "palavra.h"

// usamos o "#Define" Define o tamanho do alfabeto e o máximo de ocorrências por letra
#define ALF 26
#define MAX_OCORRENCIAS 500

/*
 * 'TOcorrenciaLetra' é uma estrutura que armazena todas as coordenadas onde uma letra aparece na matriz.
 * O campo 'quantidade' indica quantas vezes a letra aparece na matriz.
 */
typedef struct {
    TCoordenada coords[MAX_OCORRENCIAS]; // Vetor de coordenadas da letra
    int quantidade;                      // Quantidade de ocorrências daquela letra
} TOcorrenciaLetra;

/*
 * 'TOcorrencias_s' é a estrutura principal da tabela de ocorrências.
 * Para cada letra do alfabeto, guarda um 'TOcorrenciaLetra'
 */
typedef struct TOcorrencias_s {
    TOcorrenciaLetra letras[ALF]; // Vetor para cada letra do alfabeto
} TOcorrencias;

// Serve para inicializar a tabela de ocorrências, zerando os contadores
void ocorrencias_inicializar(TOcorrencias* o);

// A função: 'ocorrencias_adicionar' adiciona uma nova coordenada no vetor de ocorrências daquela letra que corresponde
int ocorrencias_adicionar(TOcorrencias* o, TCoordenada c, TMatriz* m);

// 'ocorrencias_calcular' calcula todas as ocorrências de letras na matriz e preenche a tabela
int ocorrencias_calcular(TOcorrencias* o, TMatriz* m);

// 'TOcorrenciaLetra ocorrencias_buscar_palavra' irá retornar o vetor de ocorrências da primeira letra de uma palavra
TOcorrenciaLetra ocorrencias_buscar_palavra(TOcorrencias* o, TPalavra palavra);

// 'ocorrencias_apagar' serve para liberar recursos da tabela de ocorrências
int ocorrencias_apagar(TOcorrencias* ocorrencias);

// 'ocorrencias_buscar_pos' é para buscar a posição final de uma palavra, a partir de uma coordenada inicial ('TCoordenada inicio')
TCoordenada ocorrencias_buscar_pos(TMatriz* matriz, TPalavra palavra, TCoordenada inicio);

#endif