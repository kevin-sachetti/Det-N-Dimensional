#include <stdio.h>
#include <stdlib.h>

// Função para obter a dimensão da matriz do usuário.
int dimensao() {
    int x;
    printf("Digite a dimensao da matriz quadrada: \n");
    scanf("%d", &x);
    
    // Verifica se a dimensão é válida.
    if (x < 1) {
        printf("Erro: O valor deve ser 1 ou maior para representar uma matriz quadrada :(\n");
        exit(1);
    }
    
    printf("\nO valor escolhido para dimensao da matriz eh: %d\n", x);
    return x;
}

// Função para preencher a matriz com valores fornecidos pelo usuário.
void preencherMatriz(int dim, double** mat) {
    printf("\nDigite os elementos da matriz %dx%d:\n", dim, dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            scanf("%lf", &mat[i][j]);
        }
    }
}

// Função para trocar duas linhas da matriz.
void trocarlinhas(int dim, double** mat, int linha1, int linha2) {
    for (int j = 0; j < dim; j++) {
        double temp = mat[linha1][j];
        mat[linha1][j] = mat[linha2][j];
        mat[linha2][j] = temp;
    }
}

// Função para imprimir a matriz.
void printmatriz(int dim, double** mat) {
    printf("\nA matriz que voce digitou:\n");
    for (int i = 0; i < dim; i++) {
        printf(" |");
        for (int j = 0; j < dim; j++) {
            printf("%.2f ", mat[i][j]);
        }
        printf("|\n");
    }
}

// Função para calcular o determinante da matriz.
double determinante(int dim, double** mat) {
    // Caso matriz 1x1.
    if (dim == 1) {
        return mat[0][0];
    }
    
    // Caso matriz 2x2.
    if (dim == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
    
    double det = 0.0;
    
    // Aloca memória para a submatriz (dim-1 x dim-1).
    double** submatriz = (double**)malloc((dim-1) * sizeof(double*));
    if (submatriz == NULL) {
        printf("Erro na alocação de memória!\n");
        exit(1);
    }
    for (int i = 0; i < dim-1; i++) {
        submatriz[i] = (double*)malloc((dim-1) * sizeof(double));
        if (submatriz[i] == NULL) {
            printf("Erro na alocação de memória!\n");
            exit(1);
        }
    }
    
    // Calcula o determinante.
    for (int k = 0; k < dim; k++) {
        int sub_i = 0, sub_j = 0;
        
        // Preenche a submatriz excluindo a linha 0 e a coluna k.
        for (int i = 1; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                if (j == k) {
                    continue;
                }
                submatriz[sub_i][sub_j++] = mat[i][j];
                if (sub_j == dim - 1) {
                    sub_i++;
                    sub_j = 0;
                }
            }
        }
        
        // Calcula o determinante da submatriz.
        double sub_det = determinante(dim - 1, submatriz);
        // Calcula o cofator e soma ao determinante total
        det += (k % 2 == 0 ? 1 : -1) * mat[0][k] * sub_det;
    }

    // Libera a memória alocada para a submatriz.
    for (int i = 0; i < dim-1; i++) {
        free(submatriz[i]);
    }
    free(submatriz);

    return det;
}

int main() {
    // Obtem a dimensão da matriz do usuário.
    int dim = dimensao();
    
    // Aloca memória para a matriz.
    double** mat = (double**)malloc(dim * sizeof(double*));
    if (mat == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }
    for (int i = 0; i < dim; i++) {
        mat[i] = (double*)malloc(dim * sizeof(double));
        if (mat[i] == NULL) {
            printf("Erro de alocação de memória!\n");
            exit(1);
        }
    }

    // Preenche a matriz com valores fornecidos pelo usuário.
    preencherMatriz(dim, mat);
    
    // Imprime a matriz.
    printmatriz(dim, mat);
    
    // Calcula e imprime o determinante da matriz.
    double det = determinante(dim, mat);
    printf("\nO determinante da matriz eh: %.2f\n", det);

    // Libera a memória alocada para a matriz.
    for (int i = 0; i < dim; i++) {
        free(mat[i]);
    }
    free(mat);

    return 0;
}