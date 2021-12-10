#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int **create_matrix(int rows)
{
    /* retorna ponteiro para vetor de ponteiros
	utilizar dois mallocs para alocar uma matriz quadrada*/
    int **mat = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        mat[i] = (int *)malloc(rows * sizeof(int *));
    }
    return mat;
}
void init_matriz(int **M, int v, int N)
{
    //o mesmo
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            M[i][j] = v;
        }
    }
    /* inicializa os valores da matriz com um número inteiro v */
}
void print_matriz(int **M)
{
    // o mesmo
    /* função útil para verificar se os cálculos estão corretos */
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}
int soma_acumulada(int **Z, int N)
{
    int soma = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            soma = soma + Z[i][j];
        }
        //soma = soma + Z[i][j+1]
    }
    //soma de todos os elementos da matriz resultante
    /* função que soma todos os valores da matriz e atualiza a variável soma */
    return soma;
}
void mat_mul_dist(int **X, int **Y, int **Z, int N)
{
    int i, j, k; // contadores dos loops
// inserir aqui q diretiva do OpenMP com as variáveis compartilhadas (X,Y,Z,N) e variáveis particulares(i, j, k)
#pragma omp parallel shared(X, Y, Z, N) private(i, j, k)
    {
#pragma omp for schedule(static)
        /* inserir aqui o código para multiplicar matrizes */

        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                int a = 0;
                for (k = 0; k < N; k++)
                {
                    a = a + X[i][k] * Y[k][j];
                }
                Z[i][j] = a;
                a = 0;
            }
        }
    }
}
int main(int argc, char **argv)

{
    int N = 1000; // deixar fixo respeitando o valor do enunciado da atividade
    //int thread_num = omp_get_max_threads();
    //printf("Quantidade de processadores disponíveis: %d\n", omp_get_num_procs());

    //printf("%d\n", thread_num);
    int **X = create_matrix(N);
    int **Y = create_matrix(N);
    int **Z = create_matrix(N);
    init_matriz(X, 2, N);
    init_matriz(Y, 1, N);

    //(argv[1]);
    char *a = (argv[1]);
    int thread_num = atoi(a);
    printf("%d,", thread_num);

    double wtime1 = omp_get_wtime();
    // Multiplicação distribuída
    wtime1 = omp_get_wtime() - wtime1;
    printf("%g,", wtime1);
    double wtime2 = omp_get_wtime();

    // soma acumulada
    soma_acumulada(Z, N);
    wtime2 = omp_get_wtime() - wtime2;
    printf("%g,", wtime2);
    double temp_Total = wtime1 + wtime2;
    printf("%g", temp_Total); // tempo total (dist + soma));
    printf("\n");
    return 0;
}
