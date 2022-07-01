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

void print_djk(float **djk){

    for(int i = 0; i< 41; i++){
        printf("\n");
        for(int j = 0; j<41; j++){
            printf("%d ",(int) djk[i][j]);
        }
    }
}


int main(void)
{
    Mat_grafo *mat = cria_grafo(41);
    char *mapa = le_arquivo(mat);
    float** djk = djk_percorre(mat,39,1);
    print_djk(djk);

    //prt_grafo(mat);
    lib_grafo(mat);
    //printf("%s", mapa);
    free(mapa);
}
