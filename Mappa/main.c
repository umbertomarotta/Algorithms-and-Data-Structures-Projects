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
    grafo gra = grafo_Random(10, 5, 1);

//    while(0 && grafo_Ciclico(gra)){
//        grafo_Cancella(&gra);
//        gra = grafo_Random(10, 10, 1);
//    }
    grafo_Stampa(gra);
    printf("\n\n");

    lista ord = grafo_getPath(gra, 9, 1);
    printf("Path: %d\n\n", list_size(ord));
    lista_StampaInteri(ord);
    //lista ord = lista_interi();
    //if(grafo_OrdTop(gra, ord)) printf("CICICLO! ");
    //else lista_StampaInteri(ord);
    printf("\n\n");

    int i, app;
//    for(i=0; i<10; i++){
//        app = rand()%10;
//        list_insert_prior(ord, &app, app);
//    }
    list_sort_interi(ord);
    printf("Ordinato: %d\n\n", list_size(ord));
    lista_StampaInteri(ord);
    printf("\n\n");
    for(i=0; i<5; i++){
        list_updateall_prior(ord, &i, i+100);
    }
    printf("Scazzo: %d\n\n", list_size(ord));
    lista_StampaInteri(ord);
    printf("\n\n");

    lista_cancella(&ord);
    return 0;
}
