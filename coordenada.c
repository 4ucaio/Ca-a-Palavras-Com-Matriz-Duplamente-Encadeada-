#include <stdio.h>
#include "coordenada.h"
#include "matriz.h" 

// Criar uma nova coordenada
TCoordenada coordenada_criar(int i, int j) {
    TCoordenada c; // cria uma variavel do "tipo" 'TCoordenada'
    c.linha = i; // o campo 'linha' recebe valor do parametro 'i'
    c.coluna = j; // o campo 'coluna' recebe valor do parametro 'j'
    return c;  // retorna a estrutura 'c' preenchida
}

// Verificar se coordenada está dentro dos limites da matriz, retornando 1 em caso positivo e 0 caso contrario.
int coordenada_verificar(TCoordenada coordenada, TMatriz* matriz) {
    if (!matriz) return 0; // verifica se a matriz é nula sendo 0 = False | 1 = True
    return (coordenada.linha >= 0 && coordenada.linha < matriz->linhas &&
            coordenada.coluna >= 0 && coordenada.coluna < matriz->colunas);
}
