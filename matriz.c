#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

/*
 * Essa funçao cria uma matriz duplamente encadeada de dimensões 'linhas' x 'colunas' que:
 * Aloca a célula cabeça principal, as cabeças de linha e coluna, e conecta todas.
 */
TMatriz* matriz_criar(int linhas, int colunas) {
    TMatriz* matriz = (TMatriz*)malloc(sizeof(TMatriz));
    if (!matriz) return NULL;

    matriz->linhas = linhas;
    matriz->colunas = colunas;

    // aloca a célula cabeça principal (-1, -1)
    TCelula* cabeca_principal = (TCelula*)malloc(sizeof(TCelula));
    cabeca_principal->linha = -1;
    cabeca_principal->coluna = -1;
    cabeca_principal->direita = cabeca_principal;
    cabeca_principal->esquerda = cabeca_principal;
    cabeca_principal->abaixo = cabeca_principal;
    cabeca_principal->acima = cabeca_principal;

    matriz->cabeca_principal = cabeca_principal;

    // Cria cabeças das colunas e conecta elas horizontalmente
    TCelula* ultimo_col = cabeca_principal;
    for (int j = 0; j < colunas; j++) {
        TCelula* nova_cabeca = (TCelula*)malloc(sizeof(TCelula));
        nova_cabeca->linha = -1;
        nova_cabeca->coluna = j;
        nova_cabeca->abaixo = nova_cabeca; // Inicialmente ela irá aponta para si mesma
        nova_cabeca->acima = nova_cabeca;
        // Conecta horizontalmente
        ultimo_col->direita = nova_cabeca;
        nova_cabeca->esquerda = ultimo_col;
        ultimo_col = nova_cabeca;
    }
    // Assim fecha o ciclo horizontal
    ultimo_col->direita = cabeca_principal;
    cabeca_principal->esquerda = ultimo_col;

    // Cria as cabeças das linhas e conecta elas verticalmente
    TCelula* ultimo_lin = cabeca_principal;
    for (int i = 0; i < linhas; i++) {
        TCelula* nova_cabeca = (TCelula*)malloc(sizeof(TCelula));
        nova_cabeca->linha = i;
        nova_cabeca->coluna = -1;
        nova_cabeca->direita = nova_cabeca; // Inicialmente ela irá aponta para si mesma
        nova_cabeca->esquerda = nova_cabeca;
        // Conecta verticalmente
        ultimo_lin->abaixo = nova_cabeca;
        nova_cabeca->acima = ultimo_lin;
        ultimo_lin = nova_cabeca;
    }
    // Assim fecha o ciclo vertical
    ultimo_lin->abaixo = cabeca_principal;
    cabeca_principal->acima = ultimo_lin;

    return matriz;
}

/*
 * A função 'matriz_inserir_letra: Insere uma letra na posição (linha, coluna) da matriz e:
 * Cria uma célula de dados. E depois conecta nas listas da linha e da coluna.
 */
int matriz_inserir_letra(TMatriz* matriz, int linha, int coluna, char letra) {
    if (!matriz || linha < 0 || linha >= matriz->linhas || coluna < 0 || coluna >= matriz->colunas) {
        return 0;
    }

    // TCelula* pLinha é um ponteiro que navega até a cabeça da linha 'linha'
    TCelula* pLinha = matriz->cabeca_principal->abaixo;
    for (int i = 0; i < linha; i++) pLinha = pLinha->abaixo;

    // Com o laço While irá Navegar na linha até a posição de inserção (na ordem crescente de coluna)
    while (pLinha->direita != pLinha && pLinha->direita->coluna != -1 && pLinha->direita->coluna < coluna) {
        pLinha = pLinha->direita;
    }

    // O pomteiro pColuna irá navegar até a cabeça da coluna 'coluna'
    TCelula* pColuna = matriz->cabeca_principal->direita;
    for (int j = 0; j < coluna; j++) pColuna = pColuna->direita;

    // Com o laço While irá navegar na coluna até a posição de inserção (na ordem crescente de linha)
    while (pColuna->abaixo != pColuna && pColuna->abaixo->linha != -1 && pColuna->abaixo->linha < linha) {
        pColuna = pColuna->abaixo;
    }

    // O ponteiro 'nova' aloca e preenche nova célula de dados
    TCelula* nova = (TCelula*) malloc(sizeof(TCelula));
    nova->linha = linha;
    nova->coluna = coluna;
    nova->letra = letra;

    // irá Conectar horizontalmente na linha
    nova->direita = pLinha->direita;
    nova->esquerda = pLinha;
    pLinha->direita->esquerda = nova;
    pLinha->direita = nova;

    // e agora Conecta verticalmente na coluna
    nova->abaixo = pColuna->abaixo;
    nova->acima = pColuna;
    pColuna->abaixo->acima = nova;
    pColuna->abaixo = nova;

    return 1;
}

/* 'matriz_preencher' :
 * Serve para Preencher a matriz lendo as letras da entrada.
 * e para cada linha, ela insere as letras nas posições corretas.
 */
int matriz_preencher(TMatriz* matriz) {
    if (!matriz) return 0;
    char* buffer = (char*)malloc((matriz->colunas + 2) * sizeof(char)); // Buffer para leitura

    for (int i = 0; i < matriz->linhas; i++) {
        printf("Linha %d: ", i + 1);
        if (scanf("%s", buffer) != 1) {
            free(buffer);
            return 0;
        }
        for (int j = 0; j < matriz->colunas; j++) {
            if (buffer[j] == '\0') break;
            matriz_inserir_letra(matriz, i, j, buffer[j]);
        }
    }
    free(buffer);
    return 1;
}

/* 'matriz_imprimir' :
 * Imprime a matriz navegando o ponteiro pelas listas encadeadas.
 * Para cada celula de dados encontrada, imprime a letra, se caso contrário, irá imprimir: '.'.
 */
void matriz_imprimir(TMatriz* matriz) {
    if (!matriz) return;
    TCelula* pLinha = matriz->cabeca_principal->abaixo;

    for (int i = 0; i < matriz->linhas; i++) {
        TCelula* pCelula = pLinha->direita;
        for (int j = 0; j < matriz->colunas; j++) {
            if (pCelula != pLinha && pCelula->coluna == j) {
                printf("%c ", pCelula->letra) ;
                pCelula = pCelula->direita ;
            } else {
                printf(". ") ;
            }
        }
        printf("\n");
        pLinha = pLinha->abaixo;
    }
}

/* Matriz_apagar': 
 * Serve para liberar toda a memória alocada para a matriz, incluindo células de dados e cabeças.
 */
int matriz_apagar(TMatriz* matriz) {
    if (matriz == NULL) return 1;

    // Apaga todas as linhas (células de dados e cabeças de linha:
    TCelula* pLinha = matriz->cabeca_principal->abaixo;
    while (pLinha != matriz->cabeca_principal) {
        TCelula* pCelula = pLinha->direita;
        while (pCelula != pLinha) {
            TCelula* proxima = pCelula->direita;
            free(pCelula);
            pCelula = proxima;
        }
        TCelula* proximaLinha = pLinha->abaixo;
        free(pLinha);
        pLinha = proximaLinha;
    }

    // Apaga todas as cabeças de coluna:
    TCelula* pColuna = matriz->cabeca_principal->direita;
    while (pColuna != matriz->cabeca_principal) {
        TCelula* proximo = pColuna->direita;
        free(pColuna);
        pColuna = proximo;
    }

    // Apaga a cabeça principal e a estrutura da matriz:
    free(matriz->cabeca_principal);
    free(matriz);
    return 1;
}

/* 'matriz_obter_letra' :
 * a função Retorna a letra armazenada na posição (linha, coluna).
 *  e navega pela lista da linha até encontrar a célula de dados correspondente.
 */
char matriz_obter_letra(TMatriz* matriz, int linha, int coluna) {
    if (!matriz || linha < 0 || linha >= matriz->linhas || coluna < 0 || coluna >= matriz->colunas) {
        return '\0';
    }
    TCelula* pLinha = matriz->cabeca_principal->abaixo;
    for (int i = 0; i < linha; i++) pLinha = pLinha->abaixo;

    TCelula* pCelula = pLinha->direita;
    while (pCelula != pLinha) {
        if (pCelula->coluna == coluna) {
            return pCelula->letra;
        }
        if (pCelula->coluna > coluna) break;
        pCelula = pCelula->direita;
    }
    return '\0';
}