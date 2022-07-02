/*****************************************
 *
 * TRAB 2
 * Guilherme Santos - 2010617
 * João Victor Godinho - 2011401
 *****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>
#include "grafo.h"
#include <float.h>

void print_djk(float **djk){

    for(int i = 0; i< 41; i++){
        printf("\n");
        for(int j = 0; j<41; j++){
            printf("%d ",(int) djk[i][j]);
        }
    }
}

void libera_matriz(float ** m,int lin, int col){
    for(int i = 0; i< lin; i++){
        free(m[i]);
    }
    free(m);
}


int main(void)
{
    printf("=======\n");
    Mat_grafo *mat = cria_grafo(41);
    char *mapa = le_arquivo(mat);
    
    clock_t t, t2, t3;
    t = clock();

    float** visitados = NULL;
    float** djk = djk_percorre(mat,39,1,visitados);
    //print_djk(djk);
    t = clock() - t;


    int i_target = 1, j_target = 39; //localizacao da letra F no grafo

    conta_visitados(djk);
    printf("Dijkstra: A menor distancia (ate chegar no alvo) é de %.1f\n",djk[i_target][j_target]);
    printf("TEMPO EM %f SEGUNDOS\n=======\n",((double)t)/CLOCKS_PER_SEC);
    free(visitados);

    t2 = clock();
    float** fw = fw_percorre(mat,1,39,39,1);
    printf("Floyd-Warshall: Quantidade de nos visitados: %d\n",conta_visitados(fw)*(41*41));
    printf("menor distancia: %.1f\n", fw[39][1]);
    t2 = clock() - t2;
    printf("TEMPO EM %f SEGUNDOS\n=======\n",((double)t2)/CLOCKS_PER_SEC);


    //prt_grafo(mat);
    lib_grafo(mat);
    libera_matriz(djk,41,41);
    //printf("%s", mapa);
    free(mapa);
    
}
