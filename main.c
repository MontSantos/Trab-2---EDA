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

int main(void)
{
    Mat_grafo *mat = cria_grafo(41);
    char *mapa = le_arquivo(mat);
    prt_grafo(mat);
    lib_grafo(mat);
    printf("%s", mapa);
    free(mapa);
}
