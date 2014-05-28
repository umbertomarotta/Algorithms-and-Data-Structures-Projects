#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "grafo.h"
#include "mappa.h"
#include "citta.h"

int main(){
    srand(time(NULL));
    citta c1 = citta_Random();
    citta c2 = citta_Random();
    printf("distanza: %d", citta_Distanza(c1,c2));
    printf("\n\n");
    grafo gra = grafo_Random(10, 10, 1);

    while(0 && grafo_Ciclico(gra)){
        grafo_Cancella(&gra);
        gra = grafo_Random(10, 10, 1);
    }
    grafo_Stampa(gra);
    printf("\n\n");

    lista ord = lista_interi();
    if(grafo_OrdTop(gra, ord)) printf("CICICLO! ");
    else lista_StampaInteri(ord);
    lista_cancella(&ord);
    printf("\n\n");

    return 0;
}
