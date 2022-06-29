#ifndef GRAFO_H
#define GRAFO_H

typedef struct mat_grafo Mat_grafo;

Mat_grafo *cria_grafo(int vrt);
void prt_grafo(Mat_grafo *mat);
void lib_grafo(Mat_grafo *mat);
char *le_arquivo(Mat_grafo *mat);
#endif
