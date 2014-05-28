#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>

#include "grafo.h"
#include "list.h"

#define DIM 1000
#define MATR 1

struct sgrafo{
    /*  BASSO LIVELLO   */
    int** matr;
    list* adj;
    int nv;

    /*  ALTO LIVELLO   */
    char* colore;
    int* pred;
    int* dist;
    int* f;
    int* d;
    int tempo;

    int ciclico;
    void* res;
};

struct sarco{
    int start;
    int end;
    int peso;
};

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
            if (rand()%conness == 0 && i!=y) matr[i][y] = rand()%(max)+1;
            else matr[i][y] = 0;
        }
    }
    return matr;
}

list* grafo_NuovoArrayListeRandom(int num, int conness, int max){
    if (!conness) conness = INT_MAX;
    if (!max) max = INT_MAX;
    list* array = (list*)malloc(sizeof(list)*num);
    int i, y;
    arco ed;
    srand(time(NULL));
    for(i=0; i<num; i++){
        list_new(&array[i], sizeof(struct sarco), NULL);
        for(y=0; y<num; y++){
            if (rand()%conness == 0 && i!=y){
                ed = arco_Nuovo(i, y, rand()%(max)+1);
                list_append(&array[i], ed); //matr[i][y] = rand()%(max)+1;
                free(ed);
            }
        }
    }
    return array;
}

list* grafo_NuovoArrayListe(int num){
    list* array = (list*)malloc(sizeof(list)*num);
    int i;
    for(i=0; i<num; i++) list_new(&array[i], sizeof(struct sarco), NULL);
    return array;
}

grafo grafo_Nuovo(int nv){
    grafo gra = (grafo)malloc(sizeof(struct sgrafo));
    //gra->matr = calloc(nv*nv, sizeof(int));
    gra->matr = NULL;
    gra->adj = NULL;
    if(MATR) gra->matr = grafo_NuovaMatrice(nv);
    else gra->adj = grafo_NuovoArrayListe(nv);
    gra->nv = nv;
    gra->colore = NULL;
    gra->pred = NULL;
    gra->dist = NULL;
    gra->f = NULL;
    gra->d = NULL;
    gra->tempo = 0;
    gra->ciclico = 0;
    gra->res = NULL;
    return gra;
}

int grafo_Cancella(grafo *G){
    #define gra (*G)
    if(!G || !gra) return 1;
    int i;
    for (i=0; i<gra->nv; i++){
        if (MATR && gra->matr) free(gra->matr[i]);
        else if(gra->adj) list_destroy(&gra->adj[i]);
    }
    if(gra->matr) free(gra->matr);
    if(gra->adj) free(gra->adj);
    if(gra->colore) free(gra->colore);
    if(gra->pred) free(gra->pred);
    if(gra->dist) free(gra->dist);
    if(gra->f) free(gra->f);
    if(gra->d) free(gra->d);
    if(gra->res) free(gra->res);
    free(gra);
    gra = NULL;
    return 0;
    #undef gra
}

grafo grafo_Random(int nv, int conness, int max){
    grafo gra = (grafo)malloc(sizeof(struct sgrafo));
    if(MATR) gra->matr = grafo_NuovaMatriceRandom(nv, conness, max);
    else gra->adj = grafo_NuovoArrayListeRandom(nv, conness, max);
    gra->nv = nv;
    gra->colore = NULL;
    gra->pred = NULL;
    gra->dist = NULL;
    gra->f = NULL;
    gra->d = NULL;
    gra->tempo = 0;
    gra->ciclico = 0;
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
                iterator(G, u, i, v, coda);
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
            iterator(G, edge->start, edge->end, edge->peso, coda);
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
    if (!G->f) G->f = (int*)malloc(sizeof(int)*num);
    if (!G->d) G->d = (int*)malloc(sizeof(int)*num);
    int i;
    //printf("asfiajfsiu\n");
    for(i=0; i<(G->nv); i++){
        G->pred[i] = -1;
        G->colore[i] = 'b';
        G->dist[i] = INT_MAX;
        G->f[i] = 0;
        G->d[i] = 0;
    }
    G->tempo = 0;
    G->ciclico = 0;
    return 0;
}

visita grafo_visit(grafo G, int v){
    return NULL;
}

visita grafo_visit_print(grafo G, int v){
    if(!G || v >= G->nv) return NULL;
    printf("[%d] ", v);
    return NULL;
}

int grafo_Deinit(grafo G){
    if(!G) return 1;
    free(G->pred);
    free(G->colore);
    free(G->dist);
    free(G->d);
    free(G->f);
    G->pred = NULL;
    G->colore = NULL;
    G->dist = NULL;
    G->d = NULL;
    G->f = NULL;
    return 0;
}

iteratore _grafo_Stampa(grafo G, int u, int v, int peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    //int peso = grafo_getPeso(G, u, v);
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

iteratore grafo_BFSiter(grafo G, int u, int v, int peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    if(G->colore[v] == 'b'){
        G->colore[v] = 'g';
        G->dist[v] = G->dist[u] + 1;
        G->pred[v] = u;
        list_append(coda, &v);
    }
    return NULL;
}

int grafo_BFS(grafo G, int s, iteratore iter, visita visit){
    if(!G || s >= G->nv) return 1;
    if(!iter) iter = (iteratore)grafo_BFSiter;
    if(!visit) visit = (visita)grafo_visit;

    grafo_Init(G);
    G->colore[s] = 'g';
    G->pred[s] = -1;
    G->dist[s] = 0;
    lista coda = lista_interi();
    list_append(coda, &s);
    int u;
    while(list_size(coda)){
        list_head(coda, &u, TRUE);
        grafo_for_each(G, u, iter, coda);
        visit(G, u);
        G->colore[u] = 'n';
    }
    lista_cancella(&coda);
    return 0;
}

iteratore grafo_DFSiter(grafo G, int u, int v, int peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    void** argv = (void**)coda;
    if(G->colore[v] == 'g') G->ciclico = 1;

    if(G->colore[v] == 'b'){
        G->pred[v] = u;
        grafo_DFSvisit(G, v, argv[0], argv[1]);
    }
    return NULL;
}

int grafo_DFSvisit(grafo G, int u, iteratore iter, visita visit){
    if(!G || u >= G->nv) return 1;

    if (!G->colore) grafo_Init(G);
    if(!iter) iter = (iteratore)grafo_DFSiter;
    if(!visit) visit = (visita)grafo_visit;
    void* argv[2] = {*iter, *visit};

    G->colore[u] = 'g';
    G->d[u] = G->tempo;
    G->tempo += 1;
    grafo_for_each(G, u, iter, (lista)argv);
    visit(G, u);
    G->colore[u] = 'n';
    G->f[u] = G->tempo;
    G->tempo += 1;
    return 0;
}

int grafo_DFS(grafo G, iteratore iter, visita visit){
    if(!G) return 1;
    if(!iter) iter = (iteratore)grafo_DFSiter;
    if(!visit) visit = (visita)grafo_visit;

    grafo_Init(G);
    int u;
    for(u=0; u < G->nv; u++)
        if(G->colore[u] == 'b')
            grafo_DFSvisit(G, u, iter, visit);
    return 0;
}

iteratore grafo_DFSciclico(grafo G, int u, int v, int peso, lista coda){
    if(!G || G->ciclico || u >= G->nv || v >= G->nv) return NULL;
    void** argv = (void**)coda;

    if(G->colore[v] == 'g' && !G->ciclico){
        //printf("CICILCO!\n");
        G->ciclico = 1;
    }
    else if(G->colore[v] == 'b' && !G->ciclico){
        G->pred[v] = u;
        grafo_DFSvisit(G, v, argv[0], argv[1]);
    }
    return NULL;
}

visita grafo_visit_OrdTop(grafo G, int v){
    if(!G || v >= G->nv) return NULL;
    list_prepend(G->res, &v);
    return NULL;
}

int grafo_OrdTop(grafo G, lista ord){
    if(!G || !ord) return 1;
    //if(G->ciclico) return 2;
    G->res = lista_interi();
    grafo_DFS(G, (iteratore)grafo_DFSciclico, (visita)grafo_visit_OrdTop);
    if (G->ciclico) return 2;
    else lista_catsx(ord, G->res);
    free(G->res);
    G->res = NULL;
    return 0;
}

int grafo_Ciclico(grafo G){
    if(!G) return 0;
    //if(G->ciclico) return 1;
    //else
    grafo_DFS(G, (iteratore)grafo_DFSciclico, NULL);
    return G->ciclico;
}

/*
int grafo_OrdTop1(grafo G, lista ord){
    if(!G) return 1;
    grafo_DFS(G, NULL, NULL);
    if(G->ciclico) return 2;
    G->res = ord;
    grafo_DFS(G, NULL, (visita)grafo_visit_OrdTop);
    return 0;
}*/


