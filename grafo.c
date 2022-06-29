#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

struct mat_grafo
{
    int vrt; //total vertice
    float **mat; //matriz
};

Mat_grafo *cria_grafo(int vrt) //funciona bem
{
    Mat_grafo *mat_vet = (Mat_grafo *) malloc(sizeof(Mat_grafo));
    if (mat_vet == NULL) {
        fprintf(stderr, "Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    mat_vet->vrt = vrt;
    mat_vet->mat = (float **) calloc(vrt, sizeof(float *));
    if (mat_vet->mat == NULL) {
        fprintf(stderr, "Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < vrt; i++)
        mat_vet->mat[i] = (float *) calloc(vrt, sizeof(float));

    return mat_vet;
}

void prt_grafo(Mat_grafo *mat)
{
    for (int i = 0; i < mat->vrt; i++) {
        for (int j = 0; j < mat->vrt; j++) {
            printf("%.f i = %d  j = %d\n", mat->mat[i][j], i, j);
        }
    }

}

void lib_grafo(Mat_grafo *mat) //funciona bem
{
    for (int i = 0; i < mat->vrt; i++) {
        if (mat->mat[i] != NULL)
            free(mat->mat[i]);
    }
    free (mat->mat);
    free (mat);
}

char *le_arquivo(Mat_grafo *mat) //le o arquivo, cria uma sting contendo todos os caracteres, preenche a matriz principal com o peso do caracter dela
{
    char c;
    char *str;
    FILE *arq;
    int i = 0, j = 0, k = 0;

    arq = fopen("mapa.txt", "r");
    if(arq == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    str = (char *) calloc(mat->vrt * mat->vrt, sizeof(char));
    while (!feof(arq)) {
        c = getc(arq);
        if (c != EOF) {
            if (c == 'X') {
                mat->mat[i][j] = 100;
            }
            else if (c == '.')
                mat->mat[i][j] = 1;
            else if (c == 'I')
                mat->mat[i][j] = 0;
            else if (c == 'F')
                mat->mat[i][j] = 0;
            else
                continue;
            str[k] = c;
            j++;
            k++;
            if (j > 40) {
                j = 0;
                i++;
            }
        }
    }
    fclose(arq);

    return str;
}
