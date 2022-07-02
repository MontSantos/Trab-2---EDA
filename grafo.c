#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include <limits.h>
#include <float.h>

#define LIN 41 // linhas
#define COL 41 // colunas

/*****************************************
 *
 * TRAB 2
 * Guilherme Santos - 2010617
 * João Victor Godinho - 2011401
 *****************************************/

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

int conta_visitados(float** matrix){
    int nos = 0;

    for(int i = 0; i < 41;i++){
        for(int j = 0; j < 41;j++){
            if(matrix[i][j] != FLT_MAX)
                nos++;
            
        }
    }

    //printf("FIM DO ALGORITMO, QTD DE NOS VISITADOS: %d\n",nos);
    return nos;
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

int foi_visitado(float ** visitados, int i, int j){

    if(visitados[i][j])
        return 1;
    return 0;

}

int encontra_menor(float ** v, int tam){
    
    int menor = INT_MAX;
    int lever = 0;
    for(int i = 0; i<tam; i++){
        for(int j = 0;i<tam;i++){
            if(v[i][j] < menor && v[i][j] != 0){
            menor = v[i][j];
            lever = 1;
        }
        }
    }
    if(lever == 0)
        exit(1); //erro por nao ter encontrado nenhum menor valor; Precaucao por conta do int menor ser INT_MAX por predefinicao

    return menor;
}
float* prox_curr(float **visitados, float** distancias){

    float *menor = (float*) malloc(2* (sizeof(float)));
    float menor_valor = FLT_MAX;

    for(int i = 0; i< LIN; i++){
        for(int j = 0; j<COL; j++){

            if(distancias[i][j] < menor_valor && visitados[i][j] == 0){
                menor[0] = i, menor[1] = j;
                menor_valor = distancias[i][j];
            }
        }
    }
    if(menor_valor == FLT_MAX)
        return NULL;
    return menor;
}



Mat_grafo * cria_visitados(void){

    Mat_grafo *visitados = cria_grafo(41);

    //int **visitados = (int**) malloc(LIN * sizeof(int*));
    /*
    for(int i = 0; i<LIN; i++){
        for(int j = 0; i < COL; j++){
            visitados->mat[i][j] = 0; //quando uma das paradas for visitada, isso aqui é == a 1
        }
    }
    */
    return visitados;
    
}

Mat_grafo * cria_distancias(int i_init, int j_init){

    Mat_grafo* distancias = cria_grafo(41);
    

    for(int i = 0; i<LIN; i++){
        for(int j = 0; j< COL; j++){
            distancias->mat[i][j] = FLT_MAX; // "infinito" segundo o slide do baffa sobre dijkstra
        }
    }
    distancias->mat[i_init][j_init] = 0;

    return distancias;
}



float **djk_percorre(Mat_grafo *mat, int i_start, int j_start, float** visitados){ //faz a primeira leitura do djk


    Mat_grafo *v ,*d;
    float** distancias;
    int nos = 0; //quantidade de nos visitados

    v = cria_visitados();
    d = cria_distancias(i_start,j_start);

    visitados = v->mat;
    distancias = d->mat;

    float curr = 0; //o primeiro no corrente sempre é igual a 0, pois a distancia pra ele mesmo é igual a zero

    int i = i_start;
    int j = j_start;

    while(1){ 

        if( (i-1) >= 0){ //caso exista um no acima

            float cima = mat->mat[i-1][j]; //valor na matriz input
            

            if((cima + curr) < distancias[i-1][j] && !foi_visitado(visitados,i,j)){//verifica se ele esta apto para ser o proximo no a ser percorrido (menor valor e ainda nao foi visitado)
                distancias[i-1][j] = cima + curr;
                
            } 
        }
            
        if( (i+1) < 41){

            float baixo = mat->mat[i+1][j];

            if((baixo + curr) < distancias[i+1][j] && !foi_visitado(visitados,i,j)){
                distancias[i+1][j] = baixo + curr;
            
            }
        }
        if( (j-1) >= 0){
            
            float esq = mat->mat[i][j-1];

            if((esq + curr) < distancias[i][j-1] && !foi_visitado(visitados,i,j)){
                distancias[i][j-1] = esq + curr;
                
            }

        }
        if( (j+1) < 41){
            
            float dir = mat->mat[i][j+1];

            if((dir + curr) < distancias[i][j+1] && !foi_visitado(visitados,i,j)){
                distancias[i][j+1] = dir + curr;
                
            }



        }

        //hora de definir o proximo no corrente
        visitados[i][j] = 1;
        nos++;

        float * temp = prox_curr(visitados,distancias);
        if(temp == NULL) //nao ha mais nos a serem percorridos
            break;
            
        i = (int) temp[0];
        j = (int) temp[1];

        curr = distancias[i][j];
        
        free(temp);

    }

    free(v);
    free(d);
    
    return distancias;
}

/* A* */



/* FLOYD WARSHALL*/


float** fw_percorre(Mat_grafo * mat, int init_i, int init_j, int target_i, int target_j){


    float ***menores_valores = (float***) malloc(sizeof(float**) * (LIN*COL)); //quantidade de matrizes e seus menores valores
    printf("contando matrizes...\n");

    float** visitados = NULL;
    float** ret = NULL;

    int nos = 0; //quantidade de nos 
    int mini_i = 0, mini_j = 0; //indices para percorrer as matrizes

    //printf("algoritmo rodando, aguarde...");
    for(int i = 0; i <(LIN*COL); i++){


        if(mini_j > LIN){
            mini_i++; //avanca uma linha
            mini_j = 0;
        }
        ret = djk_percorre(mat,mini_i,mini_j,visitados);
        visitados = cria_visitados()->mat;
        menores_valores[i] = ret;

        nos += conta_visitados(ret);
       // printf("%d\n",nos);

        mini_j++;
        free(visitados);
    }
    int resposta = (int) menores_valores[(LIN*init_i) + init_j][target_i][target_j + 1];
    //printf("indices : %d %d %d",(LIN*init_i) + init_j,target_i,target_j);

    return menores_valores[(LIN*init_i) + init_j];
}
