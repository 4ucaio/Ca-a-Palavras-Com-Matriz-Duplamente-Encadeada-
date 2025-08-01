#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "resolver.h"
#include "palavra.h"     
#include "ocorrencias.h" 
#include "coordenada.h"
#include "matriz.h"  

/* 'Função: matriz_solucionar' :
 * Objetivo: buscar todas as palavras na matriz.
 * Lógica:
 * Para cada palavra na lista de palavras a serem buscadas :
 * 1. Pede pra 'ocorrencias' a lista de todas as posições da "primeira letra".
 * 2. Para cada uma dessas posiçoes, chama 'palavra_buscar_pos' para verificar se a palavra inteira começa em alguma das 8 direçoes
 * 3. Se 'palavra_buscar_pos' retorna uma coordenada válida, significa que
 * a palavra foi encontrada (return 1)
 */
int matriz_solucionar(TMatriz* matriz, TOcorrencias* ocorr, TPalavra* palavras, int num_palavras) {
    if (!matriz || !palavras || !ocorr) return 0; 

    for (int i = 0; i < num_palavras; i++) {
        TOcorrenciaLetra ocorrs_letra = ocorrencias_buscar_palavra(ocorr, palavras[i]);
        
        for (int j = 0; j < ocorrs_letra.quantidade; j++) {
            TCoordenada inicio = ocorrs_letra.coords[j];
            TCoordenada fim;

            // aqui Tenta buscar a palavra completa a partir deste ponto de início 
            fim = palavra_buscar_pos(palavras[i], matriz, inicio); 
            
            // O if significa que, se a coordenada de 'fim' for válida (diferente de -1)
            if (fim.linha != -1 && fim.coluna != -1) {
                palavra_marcar_encontrada(&palavras[i], inicio, fim);
                break; //Chama 'palavra_marcar_encontrada' para guardar o resultado e interrompe a busca daquela palavra (pelo 'break')
            }
        }
    }
    return 1;
}