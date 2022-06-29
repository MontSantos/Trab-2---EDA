#include <stdio.h>
#include <stdlib.h>
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

void lib_grafo(Mat_grafo *mat) //funciona bem
{
    for (int i = 0; i < mat->vrt; i++) {
        if (mat->mat[i] != NULL)
            free(mat->mat[i]);
    }
    free (mat->mat);
    free (mat);
}
