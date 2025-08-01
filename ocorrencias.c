#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "ocorrencias.h"
#include "matriz.h"


 //Função para inicializar a tabela de ocorrências
 //Zera o contador de cada letra do alfabeto
void ocorrencias_inicializar(TOcorrencias* o) {
    if (!o) return;
    for (int i = 0; i < ALF; i++) {
        o->letras[i].quantidade = 0;
    }
}

/* 'ocorrencias_adicionar' :
 * Serve para adicionar uma coordenada ao vetor de ocorrências da letra correspondente
 * Usa matriz_obter_letra para acessar a letra na matriz.
 */
int ocorrencias_adicionar(TOcorrencias* o, TCoordenada c, TMatriz* m) {
    if (!o || !m) return 0;

    // o 'IF' aqui serve para verificar se a coordenada está nos limites da matriz
    if (c.linha < 0 || c.linha >= m->linhas || c.coluna < 0 || c.coluna >= m->colunas) {
        return 0;
    }

    // Com 'letra_na_matriz' é para Obter a letra na posição (linha, coluna)
    char letra_na_matriz = matriz_obter_letra(m, c.linha, c.coluna);
    if (letra_na_matriz == '\0') {
        // nesse 'IF' é como se: Se letra_na_matriz Não há letra nessa posição
        return 1; // retorna 1
    }

    letra_na_matriz = tolower(letra_na_matriz);
    int idx = letra_na_matriz - 'a'; // a variavel 'idx' srve para calcular o indice da letra no vetor de ocorrencias, transformando o caracter da letra em um numero de 0 a 25

    // Nesse 'IF' será para verificar se é uma letra válida
    if (idx < 0 || idx >= ALF) {
        return 0;
    }
    // Aqui verifica se ainda há espaço para adicionar a ocorrência
    if (o->letras[idx].quantidade >= MAX_OCORRENCIAS) {
        return 0;
    }

    // Adiciona a coordenada ao vetor
    o->letras[idx].coords[o->letras[idx].quantidade] = c;
    o->letras[idx].quantidade++;
    return 1;
}

/* 'ocorrencias_calcular' :
 * Serve para  calcular todas as ocorrências de letras na matriz
 * e para cada posição, irá chamar ocorrencias_adicionar
 */
int ocorrencias_calcular(TOcorrencias* o, TMatriz* m) {
    if (!o || !m) return 0;
    ocorrencias_inicializar(o); // Zerar antes de começar
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            TCoordenada c = coordenada_criar(i, j);
            ocorrencias_adicionar(o, c, m);
        }
    }
    return 1;
}

/* 'ocorrencias_buscar_palavra' :
 * Serve para buscar rapidamente todas as posições onde a primeira letra da palavra aparece
 */
TOcorrenciaLetra ocorrencias_buscar_palavra(TOcorrencias* o, TPalavra palavra) {
    TOcorrenciaLetra vazia;
    vazia.quantidade = 0;

    if (!o || !palavra.texto || strlen(palavra.texto) == 0) {
        return vazia;
    }

    char primeira_letra = tolower(palavra.texto[0]);
    int idx = primeira_letra - 'a';

    if (idx < 0 || idx >= ALF) {
        return vazia;
    }
    return o->letras[idx];
}

/* 'ocorrencias_buscar_pos' : é uma função do tipo 'TCoordenada' que busca a posição final
de uma palavra a partir de uma coordenada inicial, testando todas as direções possíveis */
TCoordenada ocorrencias_buscar_pos(TMatriz* matriz, TPalavra palavra, TCoordenada inicio) {
    int len = strlen(palavra.texto);
    int direcoes[8][2] = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
    };
    for (int d = 0; d < 8; d++) {
        int dr = direcoes[d][0], dc = direcoes[d][1];
        int l = inicio.linha, c = inicio.coluna, k;
        for (k = 0; k < len; k++) {
            int nl = l + k * dr, nc = c + k * dc;
            if (nl < 0 || nl >= matriz->linhas || nc < 0 || nc >= matriz->colunas) break;
            if (matriz_obter_letra(matriz, nl, nc) != palavra.texto[k]) break;
        }
        if (k == len) {
            TCoordenada fim = {inicio.linha + (len-1)*dr, inicio.coluna + (len-1)*dc};
            return fim;
        }
    }
    TCoordenada nao_encontrado = {-1, -1};
    return nao_encontrado;
}

/* 'ocorrencias_apagar' :
 * "Apaga" a tabela de ocorrências, zerando todos os dados.
 */
int ocorrencias_apagar(TOcorrencias* ocorrencias) {
    if (!ocorrencias) return 0;
    for (int i = 0; i < ALF; i++) {
        ocorrencias->letras[i].quantidade = 0;
        for (int j = 0; j < MAX_OCORRENCIAS; j++) {
            ocorrencias->letras[i].coords[j].linha = -1;
            ocorrencias->letras[i].coords[j].coluna = -1;
        }
    }
    return 1;
}