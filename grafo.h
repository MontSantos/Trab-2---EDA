#ifndef GRAFO_H
#define GRAFO_H



typedef struct mat_grafo Mat_grafo;

Mat_grafo *cria_grafo(int vrt);
void prt_grafo(Mat_grafo *mat);
void lib_grafo(Mat_grafo *mat);
char *le_arquivo(Mat_grafo *mat);
int conta_visitados(float** matrix);
int fw_percorre(Mat_grafo * mat);

/*DJK*/
float **djk_percorre(Mat_grafo *mat, int i_start, int j_start, float** visitados);
Mat_grafo* cria_visitados(void); //cria lista de visitados
int foi_visitado(float ** visitados, int i, int j); //verifica se um no foi visitado
#endif
