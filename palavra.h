#ifndef PALAVRA_H
#define PALAVRA_H

#include "coordenada.h"
#include "matriz.h"

// declaração para uso cruzado
struct TOcorrencias_s; 
typedef struct TOcorrencias_s TOcorrencias;

 // É essa Estrutura que representa uma palavra a ser buscada na matriz
typedef struct TPalavra_s { 
    char* texto; // (ex: "uva")
    TCoordenada inicio; //coordenada de início caso encontrada
    TCoordenada fim; // coordenada de fim caso encontrada
    int foi_encontrada; // 1 se encontrada, 0 caso contrário
} TPalavra; 

/* 'palavra_criar' :
 * Cria uma nova estrutura de palavra, alocando memória para o texto
 * Parâmetro usado é 'texto_original' - (uma string da palavra)
 * Retorno: A estrutura 'TPalavra' inicializada
 */
TPalavra palavra_criar(const char* texto_original);

/* 'palavra_marcar_encontrada' :
 * Atualiza uma palavra encontrada, marcando ela como encontrada e guardando suas coordenadas
 * Parâmetros: um ponteiro 'TPalavra* p', 'TCoordenada inicio, TCoordenada fim' - coordenadas
 */
void palavra_marcar_encontrada(TPalavra* p, TCoordenada inicio, TCoordenada fim);

/* 'palavra_buscar_pos' :
 * Serve para buscar a palavra em uma coordenada específica do caça palavras
 * Parâmetros: 'TPalavra palavra' , 'TMatriz* matriz' - um ponteiro, 'TCoordenada pos' - coordenada inicial
 * Retorno: irá retornar a coordenada final da palavra ou (-1,-1) se não encontrada
 */
TCoordenada palavra_buscar_pos(TPalavra palavra, TMatriz* matriz, TCoordenada pos); 

/* 'palavra_buscar' :
 * Essa função irá buscar a palavra no caça palavras usando a "tabela de ocorrências"
 * Retorno: coordenada final da palavra ou (-1,-1) se não encontrada
 */
TCoordenada palavra_buscar(TPalavra palavra, TMatriz* matriz, TOcorrencias* ocorr);

/* 'palavras_add' :
 * adiciona uma palavra ao vetor de 'palavras'
 * Parâmetros: palavras_vet - vetor de TPalavra, contador - ponteiro para quantidade atual,
 * capacidade - tamanho máximo, palavra_nova - palavra a adicionar
 * Retorno: novo tamanho do vetor ou -1 em caso de erro
 */
int palavras_add(TPalavra* palavras_vet, int* contador, int capacidade, TPalavra palavra_nova);

/* 'palavras_preencher' :
 * Preenche o vetor de palavras a partir da entrada
 * Retorno: 1 se deu sucesso, 0 se deu erro
 */
int palavras_preencher(TPalavra* palavras, int num_palavras);

/*
 * Imprime somente os dados de uma palavra
 */
void palavra_imprimir(TPalavra p);

/* 'palavras_imprimir_solucao' :
 * Serve para imprimir a solução do caça palavras, mostrando todas as palavras e suas posições
 */
void palavras_imprimir_solucao(TPalavra* palavras, int num_palavras);

/*
 * Libera a memória alocada para o texto da palavra.
 */
void palavra_apagar(TPalavra* p);

/* 'palavras_apagar_todas' :
 * Libera a memória alocada para o texto de todas as palavras do vetor
 * Retorno: 1 se deu sucesso, 0 se deu erro
 */
int palavras_apagar_todas(TPalavra* palavras, int num_palavras);

#endif