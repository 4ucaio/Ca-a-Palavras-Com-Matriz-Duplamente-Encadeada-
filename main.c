#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"
#include "palavra.h"
#include "ocorrencias.h"
#include "resolver.h"
#include "coordenada.h" 

int main() {
    int linhas, colunas;

//ENTRADA DE DADOS 
    printf("********** CACA PALAVRAS **********\n");
    printf("Digite as dimensoes da matriz (ex: 5 6): "); // e pedido e lido as dimensoes da matriz
    if (scanf("%d %d", &linhas, &colunas) != 2 || linhas <= 0 || colunas <= 0) {
        fprintf(stderr, "Dimensoes invalidas.\n"); // caso as dimensões colocadas seja diferente de 2 ou menor que 0
        return 1;
    }
 
    // cria a matriz dinamicamente
    TMatriz* matriz = matriz_criar(linhas, colunas);
    if (!matriz) {
        fprintf(stderr, "Erro ao criar matriz.\n");
        return 1;
    }

// Pede ao usuario para preencher a matriz
    printf("Digite as letras da matriz (%d linhas, %d caracteres por linha):\n", linhas, colunas);
    if (!matriz_preencher(matriz)) { 
        fprintf(stderr, "Erro ao preencher matriz.\n");
        matriz_apagar(matriz); 
        return 1;
    }

// Imprime a matriz digitada (funcao extra colocada para ajudar a visualizacao da matriz que o usuario está digitando)
    printf("\n--- Matriz Digitada ---\n");
    matriz_imprimir(matriz); 
    printf("-----------------------\n\n");

     // Cria a tabela de ocorrencias para otimizar a busca
    TOcorrencias ocorrencias; 

    if (!ocorrencias_calcular(&ocorrencias, matriz)) { 
        fprintf(stderr, "Erro ao calcular ocorrencias.\n");
        matriz_apagar(matriz);
        
        return 1;
    }

    // variavel para armazenar a quantidade de palavras que o usuario queira buscar
    int num_palavras;

    printf("Digite a quantidade de palavras a serem buscadas: ");
    if (scanf("%d", &num_palavras) != 1 || num_palavras < 0) { 
        // Verifica se a entrada foi valida (positiva) caso contrario encerra o programa com mensagem de erro
        fprintf(stderr, "Numero de palavras invalido.\n");
        matriz_apagar(matriz);
        return 1;
    }
    
    if (num_palavras == 0) {
        // Caso o usuário não queira buscar nenhuma palavra, encerra o programa
        printf("Nenhuma palavra para buscar. \n Encerrando.\n");
        matriz_apagar(matriz);
        return 0;
    }

    // 'TPalavra* palavras' aloca dinamicamente o vetor de palavras que serão buscadas
    TPalavra* palavras = (TPalavra*)malloc(num_palavras * sizeof(TPalavra));
    if (!palavras) {
        // se a alocaçao falhar, ira exibir mensagem de erro e encerrar o programa
        fprintf(stderr, "Erro ao alocar memoria para palavras.\n");
        matriz_apagar(matriz);

        return 1;
    }

    // Preenche o vetor de palavras com os dados fornecidos pelo usuário
    if (!palavras_preencher(palavras, num_palavras)) {
        // Se ocorrer erro ao preencher, libera memória e encerra o programa
        fprintf(stderr, "Erro ao preencher palavras.\n");
        free(palavras); 
        matriz_apagar(matriz);
        return 1;
    }

    // se matriz_solucionar retornar 0 (falha), imprime mensagem de erro.
    if (!matriz_solucionar(matriz, &ocorrencias, palavras, num_palavras)) {
        fprintf(stderr, "Processo de soluçao do caca palavras concluido.\n");
    }

    printf("\n********** RESULTADO **********\n");
    // imprime as palavras e suas posiçoes na matriz
    palavras_imprimir_solucao(palavras, num_palavras);


    // Verifica se houve erro ao liberar a memória dos textos das palavras e exibe um aviso caso a operação falhe
    if (!palavras_apagar_todas(palavras, num_palavras)) { 
        fprintf(stderr, "Aviso: Problema ao desalocar textos das palavras individuais.\n");
    }
    // Libera o vetor de palavras
    free(palavras); 

    // esse if verifica se houve erro ao liberar a memória das ocorrências e exibe um aviso caso a operação falhe
    if (!ocorrencias_apagar(&ocorrencias)) { 
        fprintf(stderr, "Aviso: 'apagar' ocorrencias não teve efeito ou falhou.\n");
    }

    // o if verifica se ocorreu erro ao liberar a memória da matriz e exibe um aviso caso a operação falhe
    if (!matriz_apagar(matriz)) { 
        fprintf(stderr, "Aviso: Problema ao apagar matriz.\n");
    }

    // Mensagem final indicando término do programa
    printf("\nCaca palavras finalizado.\n");
    return 0;
}