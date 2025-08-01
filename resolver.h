#ifndef RESOLVER_H
#define RESOLVER_H
#include "matriz.h" 

// Declaração antecipada das estruturas usadas
struct TPalavra_s; 
typedef struct TPalavra_s TPalavra;  
struct TOcorrencias_s;
typedef struct TOcorrencias_s TOcorrencias;

/* 'matriz_solucionar' :
 * Função  que "resolve" o caça-palavras por completo
 * Ele procura todas as palavras do vetor na matriz e logo apôs marca as que forem encontradas
 * Parâmetros :
 * 
 *   - matriz: ponteiro para a matriz duplamente encadeada (TMatriz* matriz)
 * 
 *   - ocorr: tabela de ocorrências já preenchida (TOcorrencias* ocorr)
 * 
 *   - palavras: vetor de palavras a serem buscadas (TPalavra* palavras)
 * 
 *   - num_palavras: Cria uma variavel em "INT" paraguardar a quantidade de palavras no vetor (int num_palavras)
 * 
 * Retorno da função :
 *   - '1' se todas as buscas foram realizadas (mesmo encontrando todas ou não)
 * 
 *   - '0' se algum ponteiro for inválido
 */
int matriz_solucionar(TMatriz* matriz, TOcorrencias* ocorr, TPalavra* palavras, int num_palavras);

#endif