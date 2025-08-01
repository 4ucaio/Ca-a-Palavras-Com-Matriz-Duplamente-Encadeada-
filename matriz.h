#ifndef MATRIZ_H
#define MATRIZ_H

/* Estrutura da célula:
 * Cada célula representa uma letra e está conectada nas direções:
 *  direita/esquerda: elementos que pertencem a mesma linha
 *  acima/abaixo: elementos que pertencem a mesma coluna
 * As células cabeça possuem linha e coluna = (-1,-1)
 */
typedef struct TCelula {
    struct TCelula* direita;
    struct TCelula* esquerda;
    struct TCelula* abaixo;
    struct TCelula* acima;
    int linha, coluna; // índice da linha e coluna 
    char letra; // letra armazenada (apenas células de dados)
} TCelula;

/* Estrutura da matriz do caça palavras
 * possui  um ponteiro para a célula cabeça principal
 */
typedef struct TMatriz {
    TCelula* cabeca_principal; // ponteiro para a célula cabeça principal (-1,-1)
    int linhas;                // numero de linhas da matriz
    int colunas;               // numero de colunas da matriz
} TMatriz;


// Funções do TAD matriz:

// Inicializa um caça-palavras vazio de dimensões L x C, criando todas as células cabeça (L=linhas C=colunas)
TMatriz* matriz_criar(int linhas, int colunas);

// Função que preenche o caça-palavras a partir da entrada, inserindo letras nas células corretas
int matriz_preencher(TMatriz* matriz);

// Imprime o caça palavras na tela
void matriz_imprimir(TMatriz* matriz);

// Desaloca toda a memória da matriz caça palavras, liberando todas as células
int matriz_apagar(TMatriz* matriz);


// Funções auxiliares para manipulação da matriz:
// Insere uma letra na posição (linha, coluna) da matriz, criando uma célula de dados
int matriz_inserir_letra(TMatriz* matriz, int linha, int coluna, char letra);

// Obtém a letra armazenada na posição (linha, coluna) da matriz
char matriz_obter_letra(TMatriz* matriz, int linha, int coluna);

#endif