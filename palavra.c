#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>  
#include "palavra.h"
#include "coordenada.h" 
#include "matriz.h"
#include "ocorrencias.h" 

// É uma "declaração antecipada" para que funções como 'palavra_buscar_pos' possam chamá-la antes mesmo de sua definição completa aparecer no código 
int verificar_palavra_em_direcao(TMatriz* matriz, const char* texto_palavra, TCoordenada inicio, int dr, int dc, TCoordenada* p_fim);

/* 'palavra_criar' :
 * Objetivo:    Funciona como um "construtor" para a estrutura 'TPalavra'

 * Ela inicializa todos os campos de uma nova palavra
 
 * Lógica:      Define valores padrão para os campos (como -1 para coordenadas e 0 para 'foi_encontrada'). E aloca memória dinamicamente para o texto da palavra e o converte para minúsculas, facilitando as comparações futuras
 
 * Parâmetros:
  - texto_original: A string (char*) da palavra a ser criada
 
 * Retorno:
  - Uma estrutura 'TPalavra' 
 */
TPalavra palavra_criar(const char* texto_original) {
    TPalavra p;
    // Inicializa os campos com valores padrões
    p.texto = NULL;
    p.foi_encontrada = 0;
    p.inicio = coordenada_criar(-1, -1);
    p.fim = coordenada_criar(-1, -1);

    if (texto_original == NULL) return p;

    // Aloca memória para a string da palavra
    int len = strlen(texto_original);
    p.texto = (char*)malloc(len + 1); // +1 para o caractere nulo '\0'

    if (p.texto != NULL) { //Copia a palavra, convertendo a letra para minúsculo
        for (int i = 0; i < len; i++) p.texto[i] = tolower(texto_original[i]);
        p.texto[len] = '\0'; // Adiciona o terminador nulo ao final
    } else {
        fprintf(stderr, "Erro: Falha ao alocar memoria para o texto da palavra.\n");
    }
    return p;
}

/* 'palavra_marcar_encontrada' :
 * Objetivo: Atualizar o estado de uma palavra quando é encontrada na matriz 

 * Lógica: Recebe um ponteiro (p) para uma 'TPalavra' e modifica seus campos internos para mostrar que ela foi encotrada, salvando sua coordenada de inicio e fim
 
 * Parâmetros:
 * - p: Ponteiro para a 'TPalavra' que será modificada
 * - inicio: A coordenada onde começa
 * - fim: A coordenada onde termina
 */
void palavra_marcar_encontrada(TPalavra* p, TCoordenada inicio, TCoordenada fim) {
    // Usamos um ponteiro para modificar a palavra original
    if (p != NULL) {
        p->inicio = inicio;
        p->fim = fim;
        p->foi_encontrada = 1; // 1 = busca realizada com sucesso
    }
}

/* 'verificar_palavra_em_direcao' :  uma "Função Auxiliar"
 * Com o Objetivo de verificar se uma palavra existe na matriz a partir de um ponto inicial e em uma única direção específica

 * a Logica é Usar um loop para percorrer os caracteres da palavra. A cada passo, calcula a próxima coordenada na matriz com base na direção (dr, dc) e compara a letra 
 * Parâmetros:
 * - matriz é o pponteiro para a nossa matriz 
 * - texto_palavra: A string da palavra que estamos procurando.
 * - inicio: A coordenada (l,c) de onde a verificação deve começar.
 * - dr, dc: O vetor de direção ("delta linha, delta coluna"). Ex: (1,0) = para baixo 
 * - p_fim: Ponteiro para uma 'TCoordenada' onde o fim da palavra será salvo 
 * Retorno:
  - 1 se a palavra foi encontrada ou 0 caso não
 */
int verificar_palavra_em_direcao(TMatriz* matriz, const char* texto_palavra, TCoordenada inicio, int dr, int dc, TCoordenada* p_fim) {
    if (!matriz || !texto_palavra || !p_fim) return 0;
    int len = strlen(texto_palavra);
    if (len == 0) return 0;
    // Loop que "caminha" pela matriz na direção especificada
    for (int i = 0; i < len; i++) {
        // Agora Calcula a próxima coordenada a ser verificada
        int l = inicio.linha + i * dr;
        int c = inicio.coluna + i * dc;
        TCoordenada atual = coordenada_criar(l, c);

        // Verificar se a coordenada calculada ainda está dentro da matriz
        if (!coordenada_verificar(atual, matriz)) return 0;

        //Buscar a letra na estrutura da matriz encadeada
        char letra_na_matriz = matriz_obter_letra(matriz, l, c);

        // Comparar a letra da matriz com a letra esperada da palavra
        if (tolower(letra_na_matriz) != texto_palavra[i]) return 0;
    }
    // quando o loop terminar, a palavra inteira foi encontrada
    // e então salva a coordenada final.
    p_fim->linha = inicio.linha + (len - 1) * dr;
    p_fim->coluna = inicio.coluna + (len - 1) * dc;
    return 1; // 1 = executou correto
}

TCoordenada palavra_buscar_pos(TPalavra palavra, TMatriz* matriz, TCoordenada pos) {
    TCoordenada coord_final_encontrada = coordenada_criar(-1, -1);
    if (!matriz || !palavra.texto) return coord_final_encontrada;
    // Vetores que representam as 8 direções: N, NE, L, SE, S, SO, O, NO
    int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
    // Aqui testa cada uma das 8 direções
    for (int i = 0; i < 8; i++) {
        TCoordenada fim_temp;
        if (verificar_palavra_em_direcao(matriz, palavra.texto, pos, dr[i], dc[i], &fim_temp)) {
            return fim_temp; // Encontrou, então retorna a coordenada final e para de executar 
        }
    }
    // Se o loop terminar sem achar, retorna a coordenada inválida
    return coord_final_encontrada;
}

TCoordenada palavra_buscar(TPalavra palavra, TMatriz* matriz, TOcorrencias* ocorr) {
    TCoordenada coord_final_encontrada = coordenada_criar(-1, -1);

    // Aqui ele pega a lista de possíveis pontos de partida da "tabela de ocorrências"
    if (!matriz || !palavra.texto || strlen(palavra.texto) == 0 || !ocorr) return coord_final_encontrada;
    TOcorrenciaLetra ocorrs_letra = ocorrencias_buscar_palavra(ocorr, palavra);

    // Itera apenas sobre os pontos de partida promissores
    for (int i = 0; i < ocorrs_letra.quantidade; i++) {
        TCoordenada pos_inicial = ocorrs_letra.coords[i];
        // Tenta encontrar a palavra completa a partir deste ponto
        TCoordenada fim = palavra_buscar_pos(palavra, matriz, pos_inicial);
        if (fim.linha != -1) return fim; // se 'return fim', quer dizer que achou
    }
    return coord_final_encontrada;
}

//Serve para adicionar uma nova palavra a um vetor de palavras
int palavras_add(TPalavra* palavras_vet, int* contador, int capacidade, TPalavra palavra_nova) {
    if (*contador < capacidade) {
        palavras_vet[*contador] = palavra_nova;
        (*contador)++; // Incrementa o contador de palavras no vetor
        return *contador;
    }
    fprintf(stderr, "Erro: Capacidade do vetor de palavras excedida.\n");
    return -1;
}

// 'palavras_preencher' : Preencher um vetor de palavras lendo da entrada
int palavras_preencher(TPalavra* palavras_vet, int num_palavras) {
    if (!palavras_vet || num_palavras <= 0) return 0;
    printf("Digite as %d palavras (uma por linha):\n", num_palavras);
    for (int i = 0; i < num_palavras; i++) {
        char buffer[100];
        if (scanf("%99s", buffer) != 1) {
            fprintf(stderr, "Erro ao ler palavra %d.\n", i + 1);
            for(int k=0; k<i; ++k) palavra_apagar(&palavras_vet[k]);
            return 0;
        }
        palavras_vet[i] = palavra_criar(buffer);
        if(palavras_vet[i].texto == NULL){
             fprintf(stderr, "Erro ao criar palavra %d ('%s') com palavra_criar.\n", i + 1, buffer);
             for(int k=0; k<i; ++k) palavra_apagar(&palavras_vet[k]);
             return 0;
        }
    }
    return 1;
}

//função de imprimir os dados de uma única palavra no formato da solução
void palavra_imprimir(TPalavra p) {
    if (p.foi_encontrada) {
        printf("%d %d %d %d %s\n", p.inicio.linha, p.inicio.coluna, p.fim.linha, p.fim.coluna, p.texto ? p.texto : "(null)");
    } else {
        printf("0 0 0 0 %s\n", p.texto ? p.texto : "(null)");
    }
}

// Imprime a solução final, iterando sobre todas as palavras
void palavras_imprimir_solucao(TPalavra* palavras, int num_palavras) {
    if (!palavras) return;
    for (int i = 0; i < num_palavras; i++) palavra_imprimir(palavras[i]);
}
// Libera a memória alocada para uma palavra (o 'texto')
void palavra_apagar(TPalavra* p) {
    if (p != NULL && p->texto != NULL) {
        free(p->texto);
        p->texto = NULL; 
    }
}

// Função que libera a memória de todas as palavras em um vetor
int palavras_apagar_todas(TPalavra* palavras_vet, int num_palavras) {
    if (!palavras_vet) return 0;
    for (int i = 0; i < num_palavras; i++) palavra_apagar(&palavras_vet[i]);
    return 1;
}