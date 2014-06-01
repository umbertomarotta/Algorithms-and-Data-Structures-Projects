//typedef enum { FALSE, TRUE } bool;
#include "list.h"

typedef struct sgrafo* grafo;
typedef struct sarco* arco;
//typedef char* String;

typedef int (*iteratore)(grafo, int, int, int, lista);
typedef int (*visita)(grafo, int);

/*  BASSO LIVELLO   */ //dipende dall'implementazione

arco arco_Nuovo(int start, int end, int npesi, ... );
grafo grafo_Nuovo(int nv, int npesi);
grafo grafo_Random(int nv, int npesi, int conness, int max);
grafo grafo_fromString(char* stringa);
int grafo_CancellaMatrice(int*** matr, int num);
int grafo_Cancella(grafo *G);

int*** grafo_NuovaMatrice(int num, int npesi);
int*** grafo_NuovaMatriceRandom(int num, int npesi, int conness, int max);

list* grafo_NuovoArrayListe(int num);
list* grafo_NuovoArrayListeRandom(int num, int npesi, int conness, int max);

int grafo_AggiungiArcoEx(grafo G, int u, int v, int npesi, ... );
int grafo_AggiungiNodi(grafo gra, int num);
int grafo_EliminaNodo(grafo gra, int id); //SOLO MATR
int grafo_getPeso(grafo G, int u, int v);

int grafo_for_each(grafo G, int u, iteratore iterator, lista coda);

/*  ALTO LIVELLO   */ //Non dipende dall'implementazione

visita grafo_visit(grafo G, int v);
visita grafo_visit_print(grafo G, int v);
visita grafo_visit_OrdTop(grafo G, int v);

iteratore _grafo_Stampa(grafo G, int u, int v, int peso, lista coda);
iteratore grafo_BFSiter(grafo G, int u, int v, int peso, lista coda);
iteratore grafo_DFSiter(grafo G, int u, int v, int peso, lista coda);
iteratore grafo_DFSciclico(grafo G, int u, int v, int peso, lista coda);
iteratore grafo_iterDijkstra(grafo G, int u, int v, int peso, lista coda);
iteratore _grafo_toString(grafo G, int u, int v, int peso, lista coda);

int grafo_Init(grafo G);
int grafo_Deinit(grafo G);
int grafo_Stampa(grafo G);
int grafo_BFS(grafo G, int s, iteratore iter, visita visit);
int grafo_DFSvisit(grafo G, int u, iteratore iter, visita visit);
int grafo_DFS(grafo G, iteratore iter, visita visit);
int grafo_OrdTop(grafo G, lista ord);
int grafo_Ciclico(grafo G);
int grafo_Rinomina(grafo G, char* nome);
char* grafo_toString(grafo G);

int grafo_Dijkstra(grafo G, int s);
int grafo_DijkstraM(lista grafi, int s, int ipeso);

lista grafo_getPath(grafo G, int s, int t);
int grafo_getPathM(lista grafi, int s, int t, int ipeso, lista* path, lista* mezzi);


