//typedef enum { FALSE, TRUE } bool;
#include "list.h"

typedef struct sgrafo* grafo;

typedef int (*iteratore)(grafo, int, int, list*);
typedef int (*visita)(grafo, int);

int** grafo_NuovaMatrice(int num);
grafo grafo_Nuovo(int nv);
int grafo_AggiungiArco(grafo gra, int start, int ends, int peso);
int grafo_AggiungiNodi(grafo gra, int num);
int grafo_EliminaNodo(grafo gra, int id);
int grafo_StampaMatrice(grafo gra);
