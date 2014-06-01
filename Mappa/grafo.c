#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

#include "grafo.h"
#include "list.h"

#define DIM 1000
#define MATR 0

struct sgrafo{
    /*  BASSO LIVELLO   */
    int*** matr;
    list* adj;
    int nv;
    int npesi;

    /*  ALTO LIVELLO   */
    char nome[50];
    char* colore;
    int* pred;
    int* dist;
    int* f;
    int* d;
    int* ignore;
    int tempo;

    grafo* predG;
    int ciclico;
    void* res;
};

struct sarco{
    int start;
    int end;
    int* peso;
};

/*  BASSO LIVELLO   */ //dipende dall'implementazione

void _arco_Free(void* arc){
    arco ed = (arco)arc;
    if(ed) return;
    free(ed->peso);
    return;
}

arco arco_Nuovo(int start, int end, int npesi, ... ){
    arco ed = (arco)malloc(sizeof(struct sarco));
    ed->start = start;
    ed->end = end;
    if(npesi){
        va_list listPointer;
        va_start( listPointer, npesi );
        ed->peso = (int*)malloc(sizeof(int)*npesi);
        int i;
        for(i=0; i<npesi; i++) ed->peso[i] =  (unsigned int)va_arg( listPointer, int );
        va_end( listPointer );
    }
    else ed->peso = NULL;
    return ed;
}

int arco_Cancella(arco* ed){ //INUSATA
    #define edg (*ed)
    if(!ed || !edg) return 1;
    free(edg->peso);
    free(edg);
    edg = NULL;
    return 1;
    #undef edg
}

int*** grafo_NuovaMatrice(int num, int npesi){
    if(npesi <= 0) npesi = 1;
    int*** matr = (int***)malloc(sizeof(int**)*num);
    int i, y, j;
    for(i=0; i<num; i++){
        //matr[i] = (int*)calloc(num, sizeof(int));
        matr[i] = (int**)malloc(sizeof(int*)*num);
        for(y=0; y<num; y++){
            matr[i][y] = (int*)malloc(sizeof(int)*npesi);
            for(j=0; j<npesi; j++) matr[i][y][j] = 0;
            //printf("%d ", matr[i][y]);
        }
        //printf("\n");
    }
    return matr;
}

int grafo_CancellaMatrice(int*** matr, int num){
    if(!matr) return 1;
    int i, y;
    for(i=0; i<num; i++){
        for(y=0; y<num; y++){
            free(matr[i][y]);
        }
        free(matr[i]);
    }
    free(matr);
    return 0;
}

int*** grafo_NuovaMatriceRandom(int num, int npesi, int conness, int max){
    if(npesi <= 0) npesi = 1;
    if (!conness) conness = INT_MAX;
    if (!max) max = INT_MAX;
    int*** matr = (int***)malloc(sizeof(int**)*num);
    int i, y, j;
    for(i=0; i<num; i++){
        matr[i] = (int**)malloc(sizeof(int*)*num);
        for(y=0; y<num; y++){
            matr[i][y] = (int*)malloc(sizeof(int)*npesi);
            if (rand()%conness == 0 && i!=y){
                for(j=0; j<npesi; j++) matr[i][y][j] = rand()%(max)+1;
            }
            else for(j=0; j<npesi; j++) matr[i][y][j] = 0;
        }
    }
    return matr;
}

list* grafo_NuovoArrayListeRandom(int num, int npesi, int conness, int max){
    if(npesi <= 0) npesi = 1;
    if (!conness) conness = INT_MAX;
    if (!max) max = INT_MAX;
    list* array = (list*)malloc(sizeof(list)*num);
    int i, y;
    arco ed;
    //srand(time(NULL));
    for(i=0; i<num; i++){
        list_new(&array[i], sizeof(struct sarco), (freeFunction)_arco_Free);
        for(y=0; y<num; y++){
            if (rand()%conness == 0 && i!=y){
                ed = arco_Nuovo(i, y, npesi, rand()%(max)+1);
                list_append(&array[i], ed); //matr[i][y] = rand()%(max)+1;
                free(ed);
            }
        }
    }
    return array;
}

list* grafo_NuovoArrayListe(int num){ //WARN
    list* array = (list*)malloc(sizeof(list)*num);
    int i;
    for(i=0; i<num; i++) list_new(&array[i], sizeof(struct sarco), (freeFunction)_arco_Free);
    return array;
}

grafo grafo_Nuovo(int nv, int npesi){
    if(npesi <= 0) npesi = 1;
    if(nv <= 0) nv = 1;
    grafo gra = (grafo)malloc(sizeof(struct sgrafo));
    //gra->matr = calloc(nv*nv, sizeof(int));
    gra->matr = NULL;
    gra->adj = NULL;
    if(MATR) gra->matr = grafo_NuovaMatrice(nv, npesi);
    else gra->adj = grafo_NuovoArrayListe(nv);
    strcpy(gra->nome, "hello");
    gra->nv = nv;
    gra->npesi = npesi;
    gra->colore = NULL;
    gra->pred = NULL;
    gra->predG = NULL;
    gra->dist = NULL;
    gra->f = NULL;
    gra->d = NULL;
    gra->ignore = calloc(nv, sizeof(int));
    gra->tempo = 0;
    gra->ciclico = 0;
    gra->res = NULL;
    return gra;
}

int grafo_Cancella(grafo *G){
    #define gra (*G)
    if(!G || !gra) return 1;
    int i;
    if (MATR && gra->matr) grafo_CancellaMatrice(gra->matr, gra->nv);
    else if(gra->adj) for (i=0; i<gra->nv; i++){
        list_destroy(&gra->adj[i]);
    }
    if(gra->matr) free(gra->matr);
    if(gra->adj) free(gra->adj);
    if(gra->colore) free(gra->colore);
    if(gra->pred) free(gra->pred);
    if(gra->predG) free(gra->predG);
    if(gra->dist) free(gra->dist);
    if(gra->f) free(gra->f);
    if(gra->d) free(gra->d);
    if(gra->res) free(gra->res);
    free(gra);
    gra = NULL;
    return 0;
    #undef gra
}

grafo grafo_Random(int nv, int npesi, int conness, int max){
    if(npesi <= 0) npesi = 1;
    grafo gra = (grafo)malloc(sizeof(struct sgrafo));
    if(MATR) gra->matr = grafo_NuovaMatriceRandom(nv, npesi, conness, max);
    else gra->adj = grafo_NuovoArrayListeRandom(nv, npesi, conness, max);
    strcpy(gra->nome, "hello");
    //gra->nome[] = "hello";
    gra->nv = nv;
    gra->npesi = npesi;
    gra->colore = NULL;
    gra->pred = NULL;
    gra->predG = NULL;
    gra->dist = NULL;
    gra->f = NULL;
    gra->d = NULL;
    gra->ignore = calloc(nv, sizeof(int));
    gra->tempo = 0;
    gra->ciclico = 0;
    gra->res = NULL;
    return gra;
}

grafo grafo_fromString(char* stringa){
    if(!stringa) return NULL;
    int nv = 0, np = 0;
    //sscanf(stringa, "%d %d ", &nv, &np);
    //size_t size = (sizeof(char)*nv*nv*np)*5;
    int fd=0;
    int inc;
    sscanf(stringa, "%d %d %n", &nv, &np, &inc);
    fd += inc;
    grafo res = grafo_Nuovo(nv, np);
    int i, j, k, peso = 0;
    list* array = res->adj;
    arco ed;
    for(i=0; i<nv; i++){
        for(j=0; j<nv; j++){
            if(!MATR) ed = arco_Nuovo(i, j, np);
            for(k=0; k<np; k++){
                sscanf(stringa+fd, "%d %n", &peso, &inc);
                //printf("%d ", inc);
                fd += inc;
                if(MATR) res->matr[i][j][k] = peso;
                else ed->peso[k] = peso;
                //printf("%d %d %d\n", i, j, k);
            }
            if(!MATR){
                list_append(&array[i], ed); //matr[i][y] = rand()%(max)+1;
                free(ed);
            }
        }
    }
    //printf("\n\n", inc);
    return res;
}

int grafo_AggiungiArcoEx(grafo G, int u, int v, int npesi, ... ){
    va_list listPointer;
    va_start( listPointer, npesi );
    if(!G) return 1;
    if (u >= G->nv || v >= G->nv || npesi > G->npesi) return 1;
    int i;
    if (MATR){
        if(npesi == 0) G->matr[u][v][0] = 1;
        else for(i=0;i<npesi;i++) G->matr[u][v][i] = (unsigned int)va_arg( listPointer, int );
    }
    else{
        arco edge;
        list* list = &(G->adj[u]);
        listNode *node = list->head;
        while(node != NULL) {
            edge = (arco)node->data;
            if (edge->start == u && edge->end == v){
                if(npesi == 0) edge->peso[0] = 1;
                else for(i=0;i<npesi;i++) edge->peso[i] = (unsigned int)va_arg( listPointer, int );
                return 1;
                }
            node = node->next;
        }
        if(npesi == 0) edge = arco_Nuovo(u, v, G->npesi, 1);
        else edge = arco_Nuovo(u, v, G->npesi, listPointer);
        list_append(list, edge);
        free (edge);
    }
    va_end( listPointer );
    return 0;
}

int grafo_AggiungiNodi(grafo gra, int num){ //LEAK MATR!
    if(!gra) return 1;
    if(MATR){
        //int** nmatr = calloc(((gra->nv)+num)*((gra->nv)+num), sizeof(int));
        int*** nmatr = grafo_NuovaMatrice( gra->nv + num, gra->npesi);
        int i, y, j;
        for(i = 0; i < gra->nv; i++){
            for(y = 0; y < gra->nv; y++){
                for(j = 0; j < gra->npesi; j++) nmatr[i][y][j] = gra->matr[i][y][j];
            }
        }
        int*** del = gra->matr;
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
    int*** nmatr = grafo_NuovaMatrice(gra->nv - 1, gra->npesi);
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
    int*** del = gra->matr;
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
            v = G->matr[u][i][0];
            if (v>0) {
                if(!G->ignore[i]) iterator(G, u, i, v, coda);
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
            if(!G->ignore[edge->end]) iterator(G, edge->start, edge->end, edge->peso[0], coda);
            node = node->next;
        }
    }
    return 0;
}

int grafo_for_each_peso(grafo G, int u, int ipeso, iteratore iterator, list* coda){
    assert(iterator != NULL);
    if(!G || u >= G->nv || ipeso >= G->npesi) return 1;
    if (MATR){
        int i, v;
        for(i=0; i<G->nv; i++){
            v = G->matr[u][i][ipeso];
            if (v>0) {
                if(!G->ignore[i]) iterator(G, u, i, v, coda);
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
            if(!G->ignore[edge->end]) iterator(G, edge->start, edge->end, edge->peso[ipeso], coda);
            node = node->next;
        }
    }
    return 0;
}

int grafo_getPeso(grafo G, int u, int v){ //INUSATA
    if(!G || u >= G->nv || v >= G->nv) return 0;
    if(MATR) return G->matr[u][v][0];
    arco edge;
    list *list = &(G->adj[u]);
    listNode *node = list->head;
    while(node != NULL) {
        edge = (arco)node->data;
        if (edge->start == u && edge->end == v)
            return edge->peso[0];
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
    if (!G->predG) G->predG = (grafo*)malloc(sizeof(grafo)*num);
    int i;
    //printf("asfiajfsiu\n");
    for(i=0; i<(G->nv); i++){
        G->pred[i] = -1;
        G->predG[i] = NULL;
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
    free(G->predG);
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
    int i, j;
    printf("%s\n", G->nome);
    for(i=0; i<G->nv; i++){
        printf("%02d -> ", i);
        for(j=0; j<G->npesi; j++){
            if(j>0){
                printf("\n   -> ");
            }
            grafo_for_each_peso(G, i, j, (iteratore)_grafo_Stampa, NULL);
        }
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

iteratore grafo_iterDijkstra(grafo G, int u, int v, int peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    int alt = G->dist[u] + peso;
    if(alt < G->dist[v] && G->dist[u] != INT_MAX){
        G->dist[v] = alt; //G->dist[u] +
        G->pred[v] = u;
        G->predG[v] = G;
        list_update_prior(coda, &v, alt);
    }
    return NULL;
}

int grafo_Dijkstra(grafo G, int s){
    if(!G || s >= G->nv) return 1;

    grafo_Init(G);
    G->pred[s] = -1;
    G->dist[s] = 0;
    lista coda = lista_interi();
    int i;
    for(i=0; i<G->nv; i++) list_insert_prior(coda, &i, G->dist[i]);
    int u;
    while(list_size(coda)){
        list_head(coda, &u, TRUE);
        grafo_for_each(G, u, (iteratore)grafo_iterDijkstra, coda);
    }
    lista_cancella(&coda);
    return 0;
}

lista grafo_getPath(grafo G, int s, int t){
    lista lis = lista_interi();
    if(!G || s >= G->nv || t >= G->nv) return lis;
    grafo_Dijkstra(G, s);
    int curr = t;
    //printf("[%d]\n",G->dist[curr]);
    list_prepend(lis, &curr);
    int num = G->nv +1;
    while(curr != s && curr >= 0 && num){
        curr = G->pred[curr];
        list_prepend(lis, &curr);
        //printf("azz: %d\n", list_size(lis));
        num--;
    }
    if(curr < 0) list_destroy(lis);
    return lis;
}

int grafo_DijkstraM(lista grafi, int s, int ipeso){
    if(!grafi) return 1;
    grafo G, G1, G2;
    list_head(grafi, &G, TRUE);
    if(!G || s >= G->nv) return 1;
    grafo_Init(G);
    G->pred[s] = -1;
    G->predG[s] = NULL;
    G->dist[s] = 0;
    lista coda = lista_interi();
    int i;
    for(i=0; i<G->nv; i++) list_insert_prior(coda, &i, G->dist[i]);
    int u;
    int num = list_size(grafi);
    while(list_size(coda)){
        list_head(coda, &u, TRUE);
        grafo_for_each_peso(G, u, ipeso, (iteratore)grafo_iterDijkstra, coda);
        G1 = G;
        for(i=0; i<num; i++){
            list_head(grafi, &G2, TRUE);
            G2->pred = G1->pred; //memcpy(G1->pred, G->pred, sizeof(int)*G->nv);
            G2->dist = G1->dist; //memcpy(G1->dist, G->dist, sizeof(int)*G->nv);
            G2->predG = G1->predG; //memcpy(G1->pred, G->pred, sizeof(int)*G->nv);
            //printf("[azz]\n");
            grafo_for_each(G2, u, (iteratore)grafo_iterDijkstra, coda);
            list_append(grafi, &G2);
            G1 = G2;
        }
    }
    list_prepend(grafi, &G);
    lista_cancella(&coda);
    return 0;
}

int grafo_getPathM(lista grafi, int s, int t, int ipeso, lista* path, lista* mezzi){
    if(!grafi || !path || !mezzi) return 1;
    grafo G;
    list_head(grafi, &G, FALSE);
    if(!G || s >= G->nv || t >= G->nv) return 1;
    grafo_DijkstraM(grafi, s, ipeso);
    int curr = t;
    list_prepend(*path, &curr);
    if (G->predG[curr]) list_prepend(*mezzi, &((G->predG[curr])->nome));
    while(curr != s && curr >= 0 && curr != s){
        curr = G->pred[curr];
        list_prepend(*path, &curr);
        if (G->predG[curr] && curr >= 0) list_prepend(*mezzi, &((G->predG[curr])->nome));
    }
    if(curr < 0) list_destroy(*path);
    return 0;
}

int grafo_Rinomina(grafo G, char* nome){
    if(!G) return 1;
    strcpy(G->nome, nome);
    return 1;
}

int grafo_Ignore(grafo G, int v){
    if(!G || v >= G->nv) return 1;
    G->ignore[v] = 1;
    return 0;
}

iteratore _grafo_toString(grafo G, int u, int v, int peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    int i = *((int*)coda);
    if(G->matr) G->matr[u][v][i] = peso;
    //if (u!=v && peso) printf("%d(%d) ", v, peso);
    return NULL;
}

char* grafo_toString(grafo G){
    if(!G) return NULL;
    int nv = G->nv;
    int np = G->npesi;
    char* res = calloc((nv*nv*np)*6, sizeof(char));
    int fd=0;
    fd += sprintf(res, "%d %d ", nv, np);

    int i, j, k;
    if(!MATR){
        G->matr = grafo_NuovaMatrice(nv, np);
        for(i=0; i<nv; i++){
            for(j=0; j<np; j++){
                grafo_for_each_peso(G, i, j , (iteratore)_grafo_toString, (lista)&j);
            }
        }
    }
    for(i=0; i<nv; i++){
        for(j=0; j<nv; j++){
            for(k=0; k<np; k++){
                fd += sprintf(res+fd, "%d ", G->matr[i][j][k]);
            }
        }
    }
    if(!MATR){
        //grafo_CancellaMatrice(G->matr, nv);
        //G->matr = NULL;
    }
    return res;
}




