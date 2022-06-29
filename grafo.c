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

int foi_visitado(int ** visitados, int i, int j){

    if(visitados[i][j])
        return 1;
    return 0;

}

int encontra_menor(int v[], int tam){
    
    int menor = INT_MAX;
    int lever = 0;
    for(int i = 0; i<tam; i++){
        if(v[i] < menor)
            menor = v[i];
            lever = 1;
    }
    if(lever == 0)
        exit(1); //erro por nao ter encontrado nenhum menor valor; Precaucao por conta do int menor ser INT_MAX por predefinicao

    return menor;
}


void djk_percorre(Mat_grafo *mat, int i_start, int j_start){ //faz a primeira leitura do djk

    /*
    TO DO:
    -   dist = curr + vizinho (atualizar o valor disso no valor da lista de distancias)
    
    */


    int ** visitados, **distancias;
    visitados = cria_visitados();
    distancias = cria_distancias();

    int curr[2]; //no corrente
    curr[0] = -1;
    curr[1] = -1;
    
    int i = i_start;
    int j = j_start;

    float cima, baixo, esq, dir;
    //42 foi um valor absolutamente arbitrario. Trocar ele por outra coisa
    cima = 42;
    baixo = 42;
    esq = 42;
    dir = 42;

    int nextNode[2]; // par ordenado arbitrario ; representa o proximo no corrente na matriz
    nextNode[0] = -1;
    nextNode[1] = -1;

    int t1 = 0;
    int t2 = 0;


    while(1){ //esse while ta zoado ; isso eh so um rascunho ; roda para cada no corrente do grafo
        
        int direction = -1; //qual direcao ele devera mudar depois de tudo
        int menorValor = INT_MAX;
        int dist_atual = distancias[curr[0]][curr[1]];

        //if(dist_atual != INT_MAX){ //se nao houvesse isso, ia estourar o int pelo tamanho dele quando somassemos o vizinho
        //}


        if( (i-1) >= 0){ //caso exista um no acima
            cima = mat->mat[i-1][j];
           
            if(cima < menorValor && !foi_visitado(visitados,i-1,j)){//verifica se ele esta apto para ser o proximo no a ser percorrido (menor valor e ainda nao foi visitado)
                menorValor = cima;
                
                direction = 0;
            } 
        }
            
        if( (i+1) < 41){
            baixo = mat->mat[i+1][j];
            if(baixo < menorValor && !foi_visitado(visitados,i+1,j)){
                menorValor = baixo;

                visitados[i][j] = 1; // seta que ele foi visitado, pois no fim do loop este sera o no corrente
                
                direction = 1
            }
        }
        if( (j-1) >= 0){
            esq = mat->mat[i][j-1];
            if(esq < menorValor && !foi_visitado(visitados,i,j-1)){
                menorValor = esq;
                
                direction = 2;
            }

        }
        if( (j+1) < 41){
            dir = mat->mat[i][j+1];
            if(dir< menorValor && !foi_visitado(visitados,i,j+1)){
                menorValor = dir;
                
                direction = 3;
            }

        }

        switch (direction) //atualiza o no corrente
        {
            visitados[curr[0]][curr[1]] = 1; // seta que ele foi visitado, pois no fim do loop este sera o no corrente

        case 0:
            curr[0] -=1;
            i-=1;
        case 1:
            curr[0] +=1;
            i+=1;
        case 2:
            curr[1] -=1;
            j-=1;
        case 3:
            curr[1] +=1;
            j+=1;
        }
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