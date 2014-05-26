#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main(){
    grafo gra = grafo_Nuovo(10);
    grafo_Stampa(gra);
    printf("\n\n");
    //grafo_BFS(gra,0 ,NULL, NULL);
    list* ord = grafo_OrdTop(gra);
    int num;
    while(list_size(ord)){
        list_head(ord, &num, TRUE);
        if (list_size(ord)) printf("%d >> ", num);
        else  printf("%d ", num);
    }
    printf("\n\n");

    /*
    grafo_EliminaNodo(gra, 2);
    grafo_StampaMatrice(gra);
    printf("\n\n");
    grafo_AggiungiNodi(gra, 1);
    grafo_StampaMatrice(gra);
    printf("\n\n");
    grafo_AggiungiArco(gra, 4, 4, 9);
    grafo_StampaMatrice(gra);
    printf("\n\n");
    */

    return 0;
}
