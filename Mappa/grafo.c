#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <float.h>

#include "list.h"
#include "grafo.h"

#define MATR 0

/*  BASSO LIVELLO   */ //dipende dall'implementazione

void _arco_Free(void* arc){
    arco ed = (arco)arc;
    if(!ed) return;
    free(ed->peso);
    //free(ed);
    return;
}

arco arco_NuovoNE(int start, int end, int npesi, va_list listPointer){
    arco ed = (arco)malloc(sizeof(struct sarco));
    ed->start = start;
    ed->end = end;
    if(npesi){
        ed->peso = (double*)malloc(sizeof(double)*npesi);
        int i;
        for(i=0; i<npesi; i++) ed->peso[i] =  (double)va_arg( listPointer, double );
    }
    else ed->peso = NULL;
    return ed;
}

arco arco_Nuovo(int start, int end, int npesi, ... ){
    va_list listPointer;
    va_start( listPointer, npesi );
    arco ret = arco_NuovoNE(start, end, npesi, listPointer);
    va_end( listPointer );
    return ret;
}

arco arco_NuovoRAND(int start, int end, int npesi, int max){

    arco ed = (arco)malloc(sizeof(struct sarco));
    ed->start = start;
    ed->end = end;
    if(npesi){
        ed->peso = (double*)malloc(sizeof(double)*npesi);
        int i;
        for(i=0; i<npesi; i++) ed->peso[i] = (double)(rand()%(max)+1);
    }
    else ed->peso = NULL;
    return ed;
}

int arco_Cancella(arco edg){ //INUSATA
    if(!edg) return 1;
    free(edg->peso);
    free(edg);
    edg = NULL;
    return 1;
}

double*** grafo_NuovaMatrice(int num, int npesi){
    if(npesi <= 0) npesi = 1;
    double*** matr = (double***)malloc(sizeof(double**)*num);
    int i, y, j;
    for(i=0; i<num; i++){
        matr[i] = (double**)malloc(sizeof(double*)*num);
        for(y=0; y<num; y++){
            matr[i][y] = (double*)malloc(sizeof(double)*npesi);
            for(j=0; j<npesi; j++) matr[i][y][j] = 0;
        }
    }
    return matr;
}

int grafo_CancellaMatrice(double*** matr, int num){
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

double*** grafo_NuovaMatriceRandom(int num, int npesi, int conness, int max){
    if(npesi <= 0) npesi = 1;
    if (!conness) conness = INT_MAX;
    if (!max) max = INT_MAX;
    double*** matr = (double***)malloc(sizeof(double**)*num);
    int i, y, j;
    for(i=0; i<num; i++){
        matr[i] = (double**)malloc(sizeof(double*)*num);
        for(y=0; y<num; y++){
            matr[i][y] = (double*)malloc(sizeof(double)*npesi);
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
    for(i=0; i<num; i++){
        list_new(&array[i], sizeof(struct sarco), (freeFunction)_arco_Free);
        for(y=0; y<num; y++){
            if (rand()%conness == 0 && i!=y){
                ed = arco_NuovoRAND(i, y, npesi, max);
                list_append(&array[i], ed);
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

int grafo_Cancella(grafo gra){
    if(!gra) return 1;
    int i;
    if (MATR && gra->matr) grafo_CancellaMatrice(gra->matr, gra->nv);
    else if(gra->adj) for (i=0; i<gra->nv; i++){
        if(&gra->adj[i]) list_destroy(&gra->adj[i]);
    }
    if(gra->ignore) free(gra->ignore);
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
}

grafo grafo_Random(int nv, int npesi, int conness, int max){
    if(npesi <= 0) npesi = 1;
    grafo gra = (grafo)malloc(sizeof(struct sgrafo));
    gra->matr = NULL;
    gra->adj = NULL;
    if(MATR) gra->matr = grafo_NuovaMatriceRandom(nv, npesi, conness, max);
    else gra->adj = grafo_NuovoArrayListeRandom(nv, npesi, conness, max);
    strcpy(gra->nome, "hello");
    gra->nv = nv;
    gra->npesi = npesi;
    gra->colore = NULL;
    gra->pred = NULL;
    gra->predG = NULL;
    gra->dist = NULL;
    gra->f = NULL;
    gra->d = NULL;
    gra->ignore = (int*)calloc(nv, sizeof(int));
    gra->tempo = 0;
    gra->ciclico = 0;
    gra->res = NULL;
    return gra;
}

grafo grafo_fromString(char* stringa){
    if(!stringa) return NULL;
    int nv = 0, np = 0;
    int fd=0;
    int inc;
    char nome[100];
    sscanf(stringa, "%[^#]# %d %d %n", nome, &nv, &np, &inc);
    fd += inc;
    grafo res = grafo_Nuovo(nv, np);
    grafo_Rinomina(res, nome);
    int i, j, k, flag;
    float peso = 0;
    list* array = res->adj;
    arco ed;
    for(i=0; i<nv; i++){
        for(j=0; j<nv; j++){
            flag = 0;
            if(!MATR) ed = arco_Nuovo(i, j, np);
            for(k=0; k<np; k++){
                sscanf(stringa+fd, "%f %n", &peso, &inc);
                fd += inc;
                if(MATR) res->matr[i][j][k] = (double)peso;
                else ed->peso[k] = (double)peso;
                if (peso) flag = 1;
            }
            if(!MATR){
                if(flag){
                    list_append(&array[i], ed);
                    free(ed);
                }
                else arco_Cancella(ed);
                ed = NULL;
            }
        }
    }
    return res;
}

int grafo_AggiungiArco(grafo G, int u, int v, int npesi, ... ){
    if(!G) return 1;
    if (u >= G->nv || v >= G->nv || npesi > G->npesi) return 1;
    va_list listPointer;
    va_start( listPointer, npesi );
    int i;
    if (MATR){
        if(npesi == 0) G->matr[u][v][0] = 1;
        else for(i=0;i<npesi;i++) G->matr[u][v][i] = (double)va_arg( listPointer, double );
    }
    else{
        arco edge;
        list* list = &(G->adj[u]);
        listNode *node = list->head;
        while(node != NULL) {
            edge = (arco)node->data;
            if (edge->start == u && edge->end == v){
                if(npesi == 0) edge->peso[0] = 1;
                else for(i=0; i<npesi ;i++) edge->peso[i] = (double)va_arg( listPointer, double );
                va_end( listPointer );
                return 1;
                }
            node = node->next;
        }
        if(npesi == 0) edge = arco_Nuovo(u, v, G->npesi, 1);
        else{
            edge = arco_NuovoNE(u, v, G->npesi, listPointer);
        }
        list_append(list, edge);
        free (edge);
    }
    va_end( listPointer );
    return 0;
}

int grafo_RimuoviArco(grafo G, int u, int v){
    if(!G) return 1;
    if (u >= G->nv || v >= G->nv) return 1;
    int npesi = G->npesi;
    int i;
    if (MATR){
        if(npesi == 0) G->matr[u][v][0] = 0;
        else for(i=0;i<npesi;i++) G->matr[u][v][i] = 0;
    }
    else{
        arco edge = (arco)malloc(sizeof(struct sarco));
        lista adj = &(G->adj[u]);
        for(i=0; i<list_size(adj); i++){
            list_head(adj, edge, TRUE);
            if (edge->start == u && edge->end == v){
                arco_Cancella(edge);
                return 0;
            }
            list_append(adj, edge);
        }
        free(edge);
    }
    return 1;
}

int grafo_AggiungiNodi(grafo gra, int num){
    if(!gra) return 1;
    if(MATR){
        double*** nmatr = grafo_NuovaMatrice( gra->nv + num, gra->npesi);
        int i, y, j;
        for(i = 0; i < gra->nv; i++){
            for(y = 0; y < gra->nv; y++){
                for(j = 0; j < gra->npesi; j++) nmatr[i][y][j] = gra->matr[i][y][j];
            }
        }
        double*** del = gra->matr;
        gra->matr = nmatr;
        grafo_CancellaMatrice(del, gra->nv);
        gra->nv += num;
    } else {
        gra->nv += num;
        int app = num;
        gra->adj = realloc(gra->adj, sizeof(list)*(gra->nv));
        while(app){
            list_new(&(gra->adj[gra->nv - num]), sizeof(struct sarco), NULL);
            app--;
        }
    }
    gra->ignore = realloc(gra->ignore, sizeof(int)*(gra->nv));
    while(num){
        gra->ignore[gra->nv - num] = 0;
        num--;
    }
    grafo_Deinit(gra);
    return 0;
}

int grafo_RimuoviNodo(grafo gra, int id){
    if(!gra) return 1;
    if (id >= gra->nv || id < 0) return 1;
    int i;
    if(MATR){
        double*** nmatr = grafo_NuovaMatrice(gra->nv - 1, gra->npesi);
        int y, x, m, k, j;
        m = 0;
        for(i = 0; i < (gra->nv - 1) ; i++){
            if (m == id) m++;
            k = 0;
            for(y = 0; y < (gra->nv - 1); y++){
                if (k == id) k++;
                j = 0;
                for(x = 0; x < gra->npesi; x++){
                    nmatr[i][y][x] = gra->matr[m][k][j];
                    j++;
                }
                k++;
            }
            m++;
        }
        double*** del = gra->matr;
        gra->matr = nmatr;
        grafo_CancellaMatrice(del, gra->nv);
    }
    else{

        lista adj;
        arco edge = (arco)malloc(sizeof(struct sarco));
        int l, siz;
        for(i = 0; i < gra->nv ; i++){
            adj = &(gra->adj[i]);
            siz = list_size(adj);
            for(l = 0; l < siz; l++){
                list_head(adj, edge, TRUE);
                if(edge->end != id){
                    if(edge->end > id) edge->end -= 1;
                    if(edge->start > id) edge->start -= 1;
                    list_append(adj, edge);
                }
                else free(edge->peso);
            }
        }
        free(edge);

        for(i = id; i < gra->nv - 1 ; i++) gra->adj[i] = gra->adj[i+1];
        gra->adj = realloc(gra->adj, sizeof(list)*(gra->nv-1));

    }
    for(i = id; i < gra->nv - 1 ; i++) gra->ignore[i] = gra->ignore[i+1];
    gra->ignore = realloc(gra->ignore, sizeof(int)*(gra->nv-1));

    gra->nv -= 1;
    grafo_Deinit(gra);
    return 0;
}

int grafo_for_each(grafo G, int u, iteratore iterator, list* coda){
    assert(iterator != NULL);
    if(!G || u >= G->nv) return 1;
    if (MATR){
        int i;
        double v;
        for(i=0; i<G->nv; i++){
            v = G->matr[u][i][0];
            if (v>0) {
                if(!G->ignore[i]) iterator(G, u, i, v, coda);
            }
        }
    }
    else{
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
        int i;
        double v;
        for(i=0; i<G->nv; i++){
            v = G->matr[u][i][ipeso];
            if (v > 0) {
                if(!G->ignore[i]) iterator(G, u, i, v, coda);
            }
        }
    }
    else{
        arco edge;
        list* list = &(G->adj[u]);
        listNode* node = list->head;
        while(node != NULL) {
            edge = (arco)node->data;
            if(!G->ignore[edge->end]) iterator(G, edge->start, edge->end, edge->peso[ipeso], coda);
            node = node->next;
        }
    }
    return 0;
}

int grafo_for_each_pesi(grafo G, int u, iteratoreM iterator, list* coda){
    assert(iterator != NULL);
    if(!G || u >= G->nv) return 1;
    double* pesi = calloc(G->npesi, sizeof(double));
    if (MATR){
        int i, y;
        double v;
        for(i=0; i<G->nv; i++){
            for(y=0; y<G->npesi; y++) pesi[y] = G->matr[u][i][y];
            if (v > 0) {
                if(!G->ignore[i]) iterator(G, u, i, pesi, coda);
            }
        }
    }
    else{
        int y;
        arco edge;
        list* list = &(G->adj[u]);
        listNode* node = list->head;
        while(node != NULL) {
            edge = (arco)node->data;
            for(y=0; y<G->npesi; y++) pesi[y] = edge->peso[y];
            if(!G->ignore[edge->end]) iterator(G, edge->start, edge->end, pesi, coda);
            node = node->next;
        }
    }
    free(pesi);
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
    int i , j;
    if (!G->colore) G->colore = (char*)malloc(sizeof(char)*num);
    if (!G->pred) G->pred = (int*)malloc(sizeof(int)*num);
    if (!G->dist) {
        G->dist = (double**)malloc(sizeof(double*)*num);
        for(i=0; i < num; i++) G->dist[i] = (double*)malloc(sizeof(double)*(G->npesi));
    }
    if (!G->f) G->f = (int*)malloc(sizeof(int)*num);
    if (!G->d) G->d = (int*)malloc(sizeof(int)*num);
    if (!G->predG) G->predG = (grafo*)malloc(sizeof(grafo)*num);
    //printf("asfiajfsiu\n");
    for(i=0; i<(G->nv); i++){
        G->pred[i] = -1;
        G->predG[i] = NULL;
        G->colore[i] = 'b';
        for(j=0; j<(G->npesi); j++) G->dist[i][j] = DBL_MAX;
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
    int i;
    if(G->pred) free(G->pred);
    if(G->predG) free(G->predG);
    if(G->colore) free(G->colore);
    if(G->dist){
        for(i=0; i < G->nv; i++) if(G->dist[i]) free(G->dist[i]);
        free(G->dist);
    }
    if(G->d) free(G->d);
    if(G->f) free(G->f);
    G->pred = NULL;
    G->predG = NULL;
    G->colore = NULL;
    G->dist = NULL;
    G->d = NULL;
    G->f = NULL;
    return 0;
}

iteratore _grafo_Stampa(grafo G, int u, int v, double peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    if (peso) printf("%d(%.1f) ", v, peso);
    else printf("!!%d(%.1f) ", v, peso);
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

iteratore grafo_BFSiter(grafo G, int u, int v, double peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    if(G->colore[v] == 'b'){
        G->colore[v] = 'g';
        G->dist[v][0] = G->dist[u][0] + 1;
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
    G->dist[s][0] = 0;
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

iteratore grafo_DFSiter(grafo G, int u, int v, double peso, lista coda){
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

iteratore grafo_DFSciclico(grafo G, int u, int v, double peso, lista coda){
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
    grafo_DFS(G, (iteratore)grafo_DFSciclico, NULL);
    return G->ciclico;
}

iteratore grafo_iterDijkstra(grafo G, int u, int v, double peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    double alt = G->dist[u][0] + peso;
    if(alt < G->dist[v][0] && G->dist[u][0] != DBL_MAX){
        G->dist[v][0] = alt; //G->dist[u] +
        G->pred[v] = u;
        G->predG[v] = G;
        list_update_prior(coda, &v, alt);
    }
    return NULL;
}

iteratoreM grafo_iterDijkstraM(grafo G, int u, int v, double* peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    int ip = G->tempo, i;
    double alt = G->dist[u][ip] + peso[ip];
    if(alt < G->dist[v][ip] && G->dist[u][ip] != DBL_MAX){
        for(i=0; i<G->npesi; i++) G->dist[v][i] = G->dist[u][i] + peso[i];
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
    G->dist[s][0] = 0;
    lista coda = lista_double();
    int i;
    for(i=0; i<G->nv; i++) list_insert_prior(coda, &i, G->dist[i][0]);
    int u;
    while(list_size(coda)){
        list_head(coda, &u, TRUE);
        grafo_for_each(G, u, (iteratore)grafo_iterDijkstra, coda);
    }
    lista_cancella(&coda);
    return 0;
}

int grafo_DijkstraT(grafo G, int s, int t){
    if(!G || s >= G->nv) return 1;

    grafo_Init(G);
    G->pred[s] = -1;
    G->dist[s][0] = 0;
    lista coda = lista_interi();
    int i;
    for(i=0; i<G->nv; i++) list_insert_prior(coda, &i, G->dist[i][0]);
    int u;
    while(list_size(coda)){
        list_head(coda, &u, TRUE);
        if (u == t) break;
        grafo_for_each(G, u, (iteratore)grafo_iterDijkstra, coda);
    }
    lista_cancella(&coda);
    return 0;
}

int grafo_getPath(grafo G, int s, int t, lista* path){
    #define lis (*path)
    assert(lis->elementSize == sizeof(int));
    if(!G || !path || !lis || s >= G->nv || t >= G->nv) return 1;
    grafo_Dijkstra(G, s);
    if(t!=s && G->pred[t] == -1) return 1;
    int curr = t;
    list_prepend(lis, &curr);
    while(curr != s && curr >= 0){
        curr = G->pred[curr];
        list_prepend(lis, &curr);
    }
    if(curr < 0) list_destroy(lis);
    return 1;
    #undef lis
}

int grafo_DijkstraM(lista grafi, int s, int ipeso){
    if(!grafi) return 1;
    grafo G, G1, G2;
    int i;
    list_head(grafi, &G, TRUE);
    if(!G || s >= G->nv) return 1;
    grafo_Init(G);
    G->pred[s] = -1;
    G->predG[s] = NULL;
    for(i=0; i<G->npesi; i++) G->dist[s][i] = 0;
    lista coda = lista_interi();
    for(i=0; i<G->nv; i++) list_insert_prior(coda, &i, G->dist[i][ipeso]);
    int u;
    int num = list_size(grafi);
    for(i=0; i<num; i++){
        list_head(grafi, &G2, TRUE);
        grafo_Deinit(G2);
        list_append(grafi, &G2);
    }
    while(list_size(coda)){
        list_head(coda, &u, TRUE);
        G->tempo = ipeso;
        grafo_for_each_pesi(G, u, (iteratoreM)grafo_iterDijkstraM, coda);
        G1 = G;
        for(i=0; i<num; i++){
            list_head(grafi, &G2, TRUE);
            G2->pred = G1->pred;
            G2->dist = G1->dist;
            G2->predG = G1->predG;
            G2->tempo = ipeso;
            grafo_for_each_pesi(G2, u, (iteratoreM)grafo_iterDijkstraM, coda);
            G1 = G2;
            list_append(grafi, &G2);
        }
    }
    for(i=0; i<num; i++){
        list_head(grafi, &G2, TRUE);
        G2->pred = NULL;
        G2->dist = NULL;
        G2->predG = NULL;
        G2->tempo = 0;
        list_append(grafi, &G2);
    }
    G->tempo = 0;
    list_prepend(grafi, &G);
    lista_cancella(&coda);
    return 0;
}

int grafo_getPathM(lista grafi, int s, int t, int ipeso, lista* path, lista* mezzi){
    #define lis (*path)
    #define way (*mezzi)
    if(!grafi || !path || !lis || !mezzi || !way) return 1;
    assert(lis->elementSize == sizeof(int));
    grafo G;
    list_head(grafi, &G, FALSE);
    if(!G || s >= G->nv || t >= G->nv) return 1;
    grafo_DijkstraM(grafi, s, ipeso);
    if(t!=s && G->pred[t] == -1) return 1;
    int curr = t;
    list_prepend(lis, &curr);
    if (G->predG[curr]) list_prepend(*mezzi, &((G->predG[curr])->nome));
    while(curr != s && curr >= 0){
        curr = G->pred[curr];
        list_prepend(lis, &curr);
        if (G->predG[curr] && curr >= 0) list_prepend(*mezzi, &((G->predG[curr])->nome));
    }
    return 0;
    #undef way
    #undef lis
}

int grafo_Rinomina(grafo G, char* nome){
    if(!G) return 1;
    strcpy(G->nome, nome);
    return 1;
}

int grafo_IgnoreToggle(grafo G, int v){
    if(!G || v >= G->nv) return 1;
    if(!G->ignore[v]) G->ignore[v] = 1;
    else G->ignore[v] = 1;
    return 0;
}

iteratore _grafo_toString(grafo G, int u, int v, double peso, lista coda){
    if(!G || u >= G->nv || v >= G->nv) return NULL;
    int i = *((int*)coda);
    if(G->matr) G->matr[u][v][i] = peso;
    return NULL;
}

char* grafo_toString(grafo G){
    if(!G) return NULL;
    int nv = G->nv;
    int np = G->npesi;
    char* res = calloc((nv*nv*np)*10, sizeof(char));
    int fd=0;
    fd += sprintf(res, "%s# %d %d ", G->nome, nv, np);

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
                fd += sprintf(res+fd, "%.2f ", G->matr[i][j][k]);
            }
        }
    }
    if(!MATR){
        grafo_CancellaMatrice(G->matr, nv);
        G->matr = NULL;
    }
    return res;
}

double grafo_raggiunge(grafo G, int u, int v){
    if(!G || u >= G->nv || v >= G->nv) return 0;
    grafo_DijkstraT(G, u, v);
    return G->dist[v][0];
}




