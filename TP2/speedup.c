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
    /* função útil para verificar se os cálculos estão corretos */
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}
void mat_mul_sequential(int **X, int **Y, int **Z, int N)
{
    int a = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                a = a + X[i][k] * Y[k][j];
            }
            Z[i][j] = a;
            a = 0;
        }
        /* escrever o código de multiplicação sequencial de matrizes (sem paralelização) */
    }
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
    /* o tamanho da matriz é passado como argumento na hora de executar */
    if (argc != 2)
    {
        printf("unexpected number of arguments\n");
        return -1;
    }

    int N = atoi(argv[1]); // quantidade de linhas e colunas da matriz
    printf("Tamanho da matriz: %d\n", N);
    /* informações sobre a varíavel do ambiente export OMP_NUM_THREADS=8 */

    int thread_num = atoi(getenv("OMP_NUM_THREADS")); // função do OpenMP que retorna o número maximo de threads
    printf("Quantidade de threads disponíveis: %d\n", thread_num);
    /* informações sobre a arquitetura */

    int procs_num = omp_get_num_procs(); // função do OpenMP que retorna o número cores da arquitetura
    printf("Quantidade de processadores disponíveis: %d\n", procs_num);

    int **X = create_matrix(N);
    int **Y = create_matrix(N);
    int **Z = create_matrix(N);
    init_matriz(X, 2, N);
    init_matriz(Y, 1, N);

    // função que retorna o tempo decorrido em segundos.
    double media1 = 0.0;
    double media2 = 0.0;
    for (int x = 0; x < 10; x++)
    {
        int **X = create_matrix(N);
        int **Y = create_matrix(N);
        int **Z = create_matrix(N);

        init_matriz(X, 2, N);
        init_matriz(Y, 1, N);

        double wtime = omp_get_wtime();
        mat_mul_sequential(X, Y, Z, N);
        wtime = omp_get_wtime() - wtime;
        media1 += wtime;
        printf("Tempo sequencial: %g\n", wtime);
        //printf("\n");

        wtime = omp_get_wtime();
        mat_mul_dist(X, Y, Z, N);
        wtime = omp_get_wtime() - wtime;
        media2 += wtime;
        printf("Tempo distribuido: %g\n", wtime);
        //printf("\n");

        free(X);
        free(Y);
        free(Z);
        // print_matriz(Z, N);
    }
    media1 = media1 / 10;
    printf("\nMedia Tempo sequencial: %g\n\n", media1);

    // print_matriz(Z);
    media2 = media2 / 10;
    printf("Media Tempo distribuido: %g\n\n", media2);

    return 0;
}