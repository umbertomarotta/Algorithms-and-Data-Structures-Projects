#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>

#include "grafo.h"
#include "list.h"

#define DIM 1000
#define MATR 0

struct sgrafo{
    /*  BASSO LIVELLO   */
    int** matr;
    list* adj;
    int nv;

    /*  ALTO LIVELLO   */
    char* colore;
    int* pred;
    int* dist;
    int* temp;
};

struct sarco{
    int start;
    int end;
    int peso;
};
typedef struct sarco* arco;

/*  BASSO LIVELLO   */ //dipende dall'implementazione

arco arco_Nuovo(int start, int end, int peso){
    arco ed = (arco)malloc(sizeof(struct sarco));
    ed->start = start;
    ed->end = end;
    ed->peso = peso;
    return ed;
}

int** grafo_NuovaMatrice(int num){
    int** matr = (int**)malloc(sizeof(int*)*num);
    int i, y;
    for(i=0; i<num; i++){
        //matr[i] = (int*)calloc(num, sizeof(int));
        matr[i] = (int*)malloc(sizeof(int)*num);
        for(y=0; y<num; y++){
            matr[i][y] = 0;
            //printf("%d ", matr[i][y]);
        }
        //printf("\n");
    }
    return matr;
}

int** grafo_NuovaMatriceRandom(int num, int conness, int max){
    if (!conness) conness = INT_MAX;
    if (!max) max = INT_MAX;
    int** matr = (int**)malloc(sizeof(int*)*num);
    int i, y;
    srand(time(NULL));
    for(i=0; i<num; i++){
        matr[i] = (int*)malloc(sizeof(int)*num);
        for(y=0; y<num; y++){
            if (rand()%conness == 0) matr[i][y] = rand()%(max)+1;
            else matr[i][y] = 0;
        }
    }
    return matr;
}

list* grafo_NuovoArrayListeRandom(int num, int conness, int max){
    if (!conness) conness = INT_MAX;
    if (!max) max = INT_MAX;
    list* array = (list*)malloc(sizeof(list)*num);
    int i, y; arco ed;
    srand(time(NULL));
    for(i=0; i<num; i++){
        list_new(&array[i], sizeof(struct sarco), NULL);
        for(y=0; y<num; y++){
            if (rand()%conness == 0){
                ed = arco_Nuovo(i, y, rand()%(max)+1);
                list_append(&array[i], ed); //matr[i][y] = rand()%(max)+1;
                free(ed);
            }
        }
    }
    return array;
}

grafo grafo_Nuovo(int nv){
    grafo gra = (grafo)malloc(sizeof(struct sgrafo));
    //gra->matr = calloc(nv*nv, sizeof(int));
    if(MATR) gra->matr = grafo_NuovaMatriceRandom(nv, 10, 1);
    else gra->adj = grafo_NuovoArrayListeRandom(nv, 10, 2);
    gra->nv = nv;
    gra->colore = NULL;
    gra->pred = NULL;
    gra->dist = NULL;
    gra->temp = NULL;
    return gra;
}

int grafo_AggiungiArco(grafo G, int u, int v, int peso){
    if(!G) return 1;
    if (u >= G->nv || v >= G->nv || peso < 1) return 1;
    if (MATR) G->matr[u][v] = peso;
    else{
        arco edge;
        list* list = &(G->adj[u]);
        listNode *node = list->head;
        while(node != NULL) {
            edge = (arco)node->data;
            if (edge->start == u && edge->end == v)
                return 1;
            node = node->next;
        }
        edge = arco_Nuovo(u, v, peso);
        list_append(list, edge);
        free (edge);
    }
    return 0;
}

int grafo_AggiungiNodi(grafo gra, int num){
    if(!gra) return 1;
    if(MATR){
        //int** nmatr = calloc(((gra->nv)+num)*((gra->nv)+num), sizeof(int));
        int** nmatr = grafo_NuovaMatrice( gra->nv + num);
        int i, y;
        for(i = 0; i < gra->nv; i++){
            for(y = 0; y < gra->nv; y++){
                nmatr[i][y] = gra->matr[i][y];
            }
        }
        int** del = gra->matr;
        gra->matr = nmatr;
        gra->nv += num;
        free(del);
    } else {
        gra->nv += num;
        gra->adj = realloc(gra->adj, sizeof(list)*(gra->nv));
        while(num){
            list_new(&(gra->adj[gra->nv - num]), sizeof(struct sarco), NULL);
            num--;
        }
    }
    grafo_Deinit(gra);
    return grafo_Init(gra);
}

//SOLO MATR
int grafo_EliminaNodo(grafo gra, int id){
    if(!gra) return 1;
    if (id >= gra->nv) return 1;
    //int** nmatr = calloc(((gra->nv)-1)*((gra->nv)-1), sizeof(int));
    int** nmatr = grafo_NuovaMatrice(gra->nv - 1);
    int i, y, m, k;
    m = 0;
    for(i = 0; i < (gra->nv - 1) ; i++){
        if (m == id) m++;
        k = 0;
        for(y = 0; y < (gra->nv - 1); y++){
            if (k == id) k++;
            nmatr[i][y] = gra->matr[m][k];
            k++;
        }
        m++;
    }
    int** del = gra->matr;
    gra->matr = nmatr;
    gra->nv -= 1;
    free(del);
    grafo_Deinit(gra);
    return grafo_Init(gra);
}

int grafo_for_each(grafo G, int u, iteratore iterator, list* coda){
    assert(iterator != NULL);
    if(!G || u >= G->nv) return 1;
    if (MATR){
        int i, v;
        for(i=0; i<G->nv; i++){
            v = G->matr[u][i];
            if (v>0) {
                iterator(G, u, i, coda);
            }
        }
    }
    else{
         //list_for_each(&(G->adj[u]), listIterator iterator)
        arco edge;
        list *list = &(G->adj[u]);
        listNode *node = list->head;
        while(node != NULL) {
            edge = (arco)node->data;
            iterator(G, edge->start, edge->end, coda);
            node = node->next;
        }
    }
    return 0;
}

int grafo_getPeso(grafo G, int u, int v){
    if(!G || u >= G->nv || v >= G->nv) return 0;
    if(MATR) return G->matr[u][v];
    arco edge;
    list *list = &(G->adj[u]);
    listNode *node = list->head;
    while(node != NULL) {
        edge = (arco)node->data;
        if (edge->start == u && edge->end == v)
            return edge->peso;
        node = node->next;
    }
    return 0;
}

/*  ALTO LIVELLO   */ //Non dipende dall'implementazione

int grafo_Init(grafo G){
    if(!G) return 1;
    int num = G->nv;
    if (!G->colore) G->colore = (char*)malloc(sizeof(char)*num);
    if (!G->pred) G->pred = (int*)malloc(sizeof(int)*num);
    if (!G->dist) G->dist = (int*)malloc(sizeof(int)*num);
    if (!G->temp) G->temp = (int*)malloc(sizeof(int)*num);
    int i;
    //printf("asfiajfsiu\n");
    for(i=0; i<(G->nv); i++){
        G->pred[i] = -1;
        G->colore[i] = 'b';
        G->dist[i] = INT_MAX;
        G->temp[i] = 0;
    }
    return 0;
}

int grafo_Deinit(grafo G){
    if(!G) return 1;
    free(G->pred);
    free(G->colore);
    free(G->dist);
    free(G->temp);
    G->pred = NULL;
    G->colore = NULL;
    G->dist = NULL;
    G->temp = NULL;
    return 0;
}

iteratore _grafo_Stampa(grafo G, int u, int v, list* coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    int peso = grafo_getPeso(G, u, v);
    if (u!=v && peso) printf("%d(%d) ", v, peso);
    return NULL;
}

int grafo_Stampa(grafo G){
    if(!G) return 1;
    int i;
    for(i=0; i<G->nv; i++){
        printf("%d -> ", i);
        grafo_for_each(G, i, (iteratore)_grafo_Stampa, NULL);
        printf("\n");
    }
    return 0;
}

iteratore grafo_BFSiter(grafo G, int u, int v, list* coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    if(G->colore[v] == 'b'){
        G->colore[v] = 'g';
        G->dist[v] = G->dist[u] + 1;
        G->pred[v] = u;
        list_append(coda, &v);
    }
    return NULL;
}

visita grafo_BFSvisit(grafo G, int v){
    if(!G || v >= G->nv) return NULL;
    printf("[%d] ", v);
    return NULL;
}

int grafo_BFS(grafo G, int s, iteratore iter, visita visit){

//int grafo_BFS(grafo G, int s, int num, ... ){
    /*
    va_list listPointer;
    va_start( listPointer, num);
    visita visit = va_arg( listPointer, visita );
    iteratore iter = va_arg( listPointer, iteratore );
    va_end( listPointer );
    */

    //printf("BFS:\n");
    if(!G || s >= G->nv) return 1;
    if(!iter) iter = (iteratore)grafo_BFSiter;
    if(!visit) visit = (visita)grafo_BFSvisit;
    grafo_Init(G);
    G->colore[s] = 'g';
    G->pred[s] = -1;
    G->dist[s] = 0;
    list coda;
    list_new(&coda, sizeof(int), NULL);
    list_prepend(&coda, &s);
    int u;
    while(list_size(&coda)){
        list_head(&coda, &u, TRUE);
        grafo_for_each(G, u, iter, &coda);
        visit(G, u);
        G->colore[u] = 'n';
    }
    return 0;
}

