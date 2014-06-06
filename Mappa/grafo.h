#ifndef __GRAFO_H
#define __GRAFO_H

#include "list.h"

struct sgrafo{
    /*  BASSO LIVELLO   */
    double*** matr;
    list* adj;
    int* ignore;
    int nv;
    int npesi;

    /*  ALTO LIVELLO   */
    double* dist;
    char nome[50];
    char* colore;
    int* pred;
    int* f;
    int* d;
    int tempo;

    struct sgrafo** predG;
    int ciclico;
    void* res;
};

struct sarco{
    int start;
    int end;
    double* peso;
};

typedef struct sgrafo* grafo;
typedef struct sarco* arco;

typedef int (*iteratore)(grafo, int, int, double, lista);
typedef int (*visita)(grafo, int);

/*  BASSO LIVELLO   */ //dipende dall'implementazione

arco arco_Nuovo(int start, int end, int npesi, ... );
//arco arco_NuovoNE(int start, int end, int npesi, va_list listPointer);
arco arco_NuovoRAND(int start, int end, int npesi, int max);

grafo grafo_Nuovo(int nv, int npesi);
grafo grafo_Random(int nv, int npesi, int conness, int max);
grafo grafo_fromString(char* stringa);

double*** grafo_NuovaMatrice(int num, int npesi);
double*** grafo_NuovaMatriceRandom(int num, int npesi, int conness, int max);

list* grafo_NuovoArrayListe(int num);
list* grafo_NuovoArrayListeRandom(int num, int npesi, int conness, int max);

int grafo_CancellaMatrice(double*** matr, int num);
int grafo_Cancella(grafo *G);
int grafo_AggiungiArco(grafo G, int u, int v, int npesi, ... );
int grafo_RimuoviArco(grafo G, int u, int v);
int grafo_AggiungiNodi(grafo gra, int num);
int grafo_RimuoviNodo(grafo gra, int id);
int grafo_getPeso(grafo G, int u, int v);
int grafo_for_each_peso(grafo G, int u, int ipeso, iteratore iterator, list* coda);
int grafo_for_each(grafo G, int u, iteratore iterator, lista coda);

/*  ALTO LIVELLO   */ //Non dipende dall'implementazione

visita grafo_visit(grafo G, int v);
visita grafo_visit_print(grafo G, int v);
visita grafo_visit_OrdTop(grafo G, int v);

iteratore _grafo_Stampa(grafo G, int u, int v, double peso, lista coda);
iteratore grafo_BFSiter(grafo G, int u, int v, double peso, lista coda);
iteratore grafo_DFSiter(grafo G, int u, int v, double peso, lista coda);
iteratore grafo_DFSciclico(grafo G, int u, int v, double peso, lista coda);
iteratore grafo_iterDijkstra(grafo G, int u, int v, double peso, lista coda);
iteratore _grafo_toString(grafo G, int u, int v, double peso, lista coda);

char* grafo_toString(grafo G);
int grafo_Init(grafo G);
int grafo_Deinit(grafo G);
int grafo_Stampa(grafo G);
int grafo_BFS(grafo G, int s, iteratore iter, visita visit);
int grafo_DFS(grafo G, iteratore iter, visita visit);
int grafo_DFSvisit(grafo G, int u, iteratore iter, visita visit);
int grafo_OrdTop(grafo G, lista ord);
int grafo_Ciclico(grafo G);
int grafo_Rinomina(grafo G, char* nome);

int grafo_Dijkstra(grafo G, int s);
int grafo_DijkstraM(lista grafi, int s, int ipeso);

int grafo_getPath(grafo G, int s, int t, lista* path);
int grafo_getPathM(lista grafi, int s, int t, int ipeso, lista* path, lista* mezzi);

int grafo_IgnoreToggle(grafo G, int v);
double grafo_raggiunge(grafo G, int u, int v);

#endif
