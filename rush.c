#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include <limits.h>

#define LIN 41 // linhas
#define COL 41 // colunas

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
            if (c == 'X') 
                mat->mat[i][j] = 100;
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


/* DIJKSTRA */



void djk(Mat_grafo* matrix,int i_ini, int j_ini){ //faz a matriz de caminho mais curto

    int **visitados = cria_visitados(); //matriz para ver se aquele no ja foi visitado
    int **distancia = cria_distancias(); //matriz que diz a distancia daquele ponto ate o ponto inicial

    int i = i_ini;
    int j = j_ini;

    while(1){
        

    }

}


int ** cria_visitados(void){

    int **visitados = (int**) malloc(LIN * sizeof(int*));
    
    for(int i = 0; i<LIN; i++){
        visitados[i] = (int*) malloc( COL * sizeof(int));
        for(int j = 0; i < COL; j++){
            visitados[i][j] = 0; //quando uma das paradas for visitada, isso aqui é == a 1
        }
    }

    return visitados;
}

int ** cria_distancias(void){

    int** distancias = (int**) malloc(LIN*sizeof(int*));

    for(int i = 0; i<LIN; i++){
        distancias[i] = (int*) malloc(COL* sizeof(int));
        for(int j = 0; j< COL; j++){
            distancias[i][j] = INT_MAX; // "infinito" segundo o slide do baffa sobre dijkstra
        }
    }

    return distancias;
}