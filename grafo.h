#ifndef GRAFO_H
#define GRAFO_H

typedef struct mat_grafo Mat_grafo;

Mat_grafo *cria_grafo(int vrt);
void cria_aresta(Mat_grafo *mat, int v1, int v2, int peso);
void lib_grafo(Mat_grafo *mat);
#endif
