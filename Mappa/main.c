#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"

int main(){
    grafo gra = grafo_Nuovo(11);
    grafo_Stampa(gra);
    printf("\n\n");
    grafo_BFS(gra, 0, NULL, NULL);
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
